#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint32_t ;
typedef  int /*<<< orphan*/  mpc_status ;
typedef  int mpc_seek_t ;
typedef  int mpc_int_t ;
typedef  int /*<<< orphan*/  mpc_int32_t ;
struct TYPE_10__ {int count; scalar_t__ buff; } ;
struct TYPE_9__ {int stream_version; int header_position; } ;
struct TYPE_11__ {int bytes_total; TYPE_2__ bits_reader; TYPE_1__ si; TYPE_4__* r; scalar_t__ block_frames; scalar_t__ block_bits; scalar_t__ buffer; } ;
typedef  TYPE_3__ mpc_demux ;
struct TYPE_12__ {int /*<<< orphan*/  (* seek ) (TYPE_4__*,int /*<<< orphan*/ ) ;scalar_t__ (* tell ) (TYPE_4__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_BUFFER_SWAP ; 
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 
 int /*<<< orphan*/  mpc_demux_clear_buff (TYPE_3__*) ; 
 int /*<<< orphan*/  mpc_demux_fill (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ stub1 (TYPE_4__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_4__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static mpc_status
mpc_demux_seek(mpc_demux * d, mpc_seek_t fpos, mpc_uint32_t min_bytes) {
	mpc_seek_t start_pos, end_pos;
	mpc_int_t bit_offset;

	// get current buffer position
	end_pos = ((mpc_seek_t)(d->r->tell(d->r))) << 3;
	start_pos =	end_pos - (d->bytes_total << 3);

	if (fpos >= start_pos && fpos < end_pos) {
		d->bits_reader.buff = d->buffer + ((fpos - start_pos) >> 3);
		bit_offset = fpos & 7;
		d->block_bits = 0;
		d->block_frames = 0;
	} else {
		mpc_seek_t next_pos = fpos >> 3;
		if (d->si.stream_version == 7)
			next_pos = ((next_pos - d->si.header_position) & (-1 << 2)) + d->si.header_position;
		bit_offset = (int) (fpos - (next_pos << 3));

		mpc_demux_clear_buff(d);
		if (!d->r->seek(d->r, (mpc_int32_t) next_pos))
			return MPC_STATUS_FAIL;
	}

	if (d->si.stream_version == 7)
		mpc_demux_fill(d, (min_bytes + ((bit_offset + 7) >> 3) + 3) & (~3), MPC_BUFFER_SWAP);
	else
		mpc_demux_fill(d, min_bytes + ((bit_offset + 7) >> 3), 0);
	d->bits_reader.buff += bit_offset >> 3;
	d->bits_reader.count = 8 - (bit_offset & 7);

	return MPC_STATUS_OK;
}