#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ mpc_uint32_t ;
typedef  scalar_t__ mpc_int32_t ;
struct TYPE_6__ {int count; scalar_t__ buff; } ;
struct TYPE_7__ {scalar_t__ bytes_total; scalar_t__ buffer; TYPE_3__* r; TYPE_1__ bits_reader; } ;
typedef  TYPE_2__ mpc_demux ;
struct TYPE_8__ {scalar_t__ (* read ) (TYPE_3__*,scalar_t__,scalar_t__) ;} ;

/* Variables and functions */
 scalar_t__ DEMUX_BUFFER_SIZE ; 
 int MPC_BUFFER_FULL ; 
 int MPC_BUFFER_SWAP ; 
 int /*<<< orphan*/  memmove (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,scalar_t__) ; 
 unsigned int mpc_swap32 (unsigned int) ; 
 int /*<<< orphan*/  mpc_unread_bytes_unchecked (TYPE_2__*) ; 
 scalar_t__ stub1 (TYPE_3__*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static mpc_uint32_t
mpc_demux_fill(mpc_demux * d, mpc_uint32_t min_bytes, int flags)
{
	mpc_uint32_t unread_bytes = (mpc_uint32_t) mpc_unread_bytes_unchecked(d);
	int offset = 0;

	if ((mpc_int32_t) unread_bytes < 0)
		return 0; // Error - we've been reading past the end of the buffer - abort

	if (min_bytes == 0 || min_bytes > DEMUX_BUFFER_SIZE ||
		    (unread_bytes < min_bytes && (flags & MPC_BUFFER_FULL) != 0 ))
		min_bytes = DEMUX_BUFFER_SIZE;

	if (unread_bytes < min_bytes) {
		mpc_uint32_t bytes2read = min_bytes - unread_bytes;
		mpc_uint32_t bytes_free = DEMUX_BUFFER_SIZE - d->bytes_total;
		mpc_uint32_t bytesread;

		if (flags & MPC_BUFFER_SWAP) {
			bytes2read &= -1 << 2;
			offset = (unread_bytes + 3) & ( -1 << 2);
			offset -= unread_bytes;
		}

		if (bytes2read > bytes_free) {
			if (d->bits_reader.count == 0) {
				d->bits_reader.count = 8;
				d->bits_reader.buff++;
			}
			memmove(d->buffer + offset, d->bits_reader.buff, unread_bytes);
			d->bits_reader.buff = d->buffer + offset;
			d->bytes_total = unread_bytes + offset;
		}
		bytesread = d->r->read(d->r, d->buffer + d->bytes_total, bytes2read);
		if (bytesread < bytes2read) {
			memset(d->buffer + d->bytes_total + bytesread, 0, bytes2read - bytesread); // FIXME : why ?
		}
		if (flags & MPC_BUFFER_SWAP) {
			unsigned int i, * tmp = (unsigned int *) (d->buffer + d->bytes_total);
			for(i = 0 ;i < (bytes2read >> 2); i++)
				tmp[i] = mpc_swap32(tmp[i]);
		}
		d->bytes_total += bytesread;
		unread_bytes += bytesread;
	}

	return unread_bytes;
}