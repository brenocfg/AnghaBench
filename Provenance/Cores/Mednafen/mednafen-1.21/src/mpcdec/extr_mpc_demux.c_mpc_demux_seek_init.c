#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  mpc_status ;
typedef  scalar_t__ mpc_seek_t ;
struct TYPE_5__ {int block_pwr; int samples; } ;
struct TYPE_6__ {int seek_pwr; int seek_table_size; scalar_t__* seek_table; TYPE_1__ si; } ;
typedef  TYPE_2__ mpc_demux ;

/* Variables and functions */
 size_t MAX_SEEK_TABLE_SIZE ; 
 int MPC_FRAME_LENGTH ; 
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 
 scalar_t__* malloc (size_t) ; 
 int /*<<< orphan*/  mpc_demux_pos (TYPE_2__*) ; 

__attribute__((used)) static mpc_status mpc_demux_seek_init(mpc_demux * d)
{
	size_t seek_table_size;
	if (d->seek_table != 0)
		return MPC_STATUS_OK;

	d->seek_pwr = 6;
	if (d->si.block_pwr > d->seek_pwr)
		d->seek_pwr = d->si.block_pwr;
	seek_table_size = (2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr));
	while (seek_table_size > MAX_SEEK_TABLE_SIZE) {
		d->seek_pwr++;
		seek_table_size = (2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr));
	}
	d->seek_table = malloc((size_t)(seek_table_size * sizeof(mpc_seek_t)));
	if (d->seek_table == 0)
		return MPC_STATUS_FAIL;
	d->seek_table[0] = (mpc_seek_t)mpc_demux_pos(d);
	d->seek_table_size = 1;

	return MPC_STATUS_OK;
}