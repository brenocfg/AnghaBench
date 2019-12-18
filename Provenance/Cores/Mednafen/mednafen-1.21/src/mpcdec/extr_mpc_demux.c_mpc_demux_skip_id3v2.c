#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_6__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint8_t ;
typedef  int mpc_int32_t ;
struct TYPE_9__ {int /*<<< orphan*/  buff; } ;
struct TYPE_7__ {TYPE_2__* r; TYPE_6__ bits_reader; } ;
typedef  TYPE_1__ mpc_demux ;
typedef  int mpc_bool_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* seek ) (TYPE_2__*,int) ;} ;

/* Variables and functions */
 int MPC_STATUS_FAIL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int mpc_bits_read (TYPE_6__*,int) ; 
 int /*<<< orphan*/  mpc_demux_clear_buff (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_demux_fill (TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int) ; 

__attribute__((used)) static mpc_int32_t mpc_demux_skip_id3v2(mpc_demux * d)
{
	mpc_uint8_t  tmp [4];
	mpc_bool_t footerPresent;     // ID3v2.4-flag
	mpc_int32_t size;

    // we must be at the beginning of the stream
	mpc_demux_fill(d, 3, 0);

    // check id3-tag
	if ( 0 != memcmp( d->bits_reader.buff, "ID3", 3 ) )
		return 0;

	mpc_demux_fill(d, 10, 0);

	mpc_bits_read(&d->bits_reader, 24); // read ID3
	mpc_bits_read(&d->bits_reader, 16); // read tag version

	tmp[0] = mpc_bits_read(&d->bits_reader, 8); // read flags
	footerPresent = tmp[0] & 0x10;
	if ( tmp[0] & 0x0F )
		return MPC_STATUS_FAIL; // not (yet???) allowed

	tmp[0] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[1] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[2] = mpc_bits_read(&d->bits_reader, 8); // read size
	tmp[3] = mpc_bits_read(&d->bits_reader, 8); // read size

	if ( (tmp[0] | tmp[1] | tmp[2] | tmp[3]) & 0x80 )
		return MPC_STATUS_FAIL; // not allowed

    // read headerSize (syncsave: 4 * $0xxxxxxx = 28 significant bits)
	size = tmp[0] << 21;
	size |= tmp[1] << 14;
	size |= tmp[2] << 7;
	size |= tmp[3];

	size += 10; //header

	if ( footerPresent ) size += 10;

	// This is called before file headers get read, streamversion etc isn't yet known, demuxing isn't properly initialized and we can't call mpc_demux_seek() from here.
	mpc_demux_clear_buff(d);
	if (!d->r->seek(d->r, size))
		return MPC_STATUS_FAIL;

	return size;
}