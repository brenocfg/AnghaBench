#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint_t ;
typedef  int mpc_uint64_t ;
typedef  int mpc_uint32_t ;
typedef  int /*<<< orphan*/  mpc_status ;
typedef  int mpc_seek_t ;
struct TYPE_4__ {int block_pwr; int samples; scalar_t__ header_position; } ;
struct TYPE_5__ {int* seek_table; int seek_pwr; int seek_table_size; TYPE_1__ si; int /*<<< orphan*/  bits_reader; } ;
typedef  TYPE_2__ mpc_demux ;
typedef  int /*<<< orphan*/  mpc_bits_reader ;

/* Variables and functions */
 int MAX_SEEK_TABLE_SIZE ; 
 int MPC_FRAME_LENGTH ; 
 int /*<<< orphan*/  MPC_STATUS_OK ; 
 int* malloc (size_t) ; 
 int /*<<< orphan*/  mpc_bits_get_size (int /*<<< orphan*/ *,int*) ; 
 int mpc_bits_golomb_dec (int /*<<< orphan*/ *,int) ; 
 int mpc_bits_read (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static mpc_status mpc_demux_ST(mpc_demux * d)
{
	mpc_uint64_t tmp;
	mpc_seek_t * table, last[2];
	mpc_bits_reader r = d->bits_reader;
	mpc_uint_t i, diff_pwr = 0, mask;
	mpc_uint32_t file_table_size;

	if (d->seek_table != 0)
		return MPC_STATUS_OK;

	mpc_bits_get_size(&r, &tmp);
	file_table_size = (mpc_seek_t) tmp;
	d->seek_pwr = d->si.block_pwr + mpc_bits_read(&r, 4);

	tmp = 2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr);
	while (tmp > MAX_SEEK_TABLE_SIZE) {
		d->seek_pwr++;
		diff_pwr++;
		tmp = 2 + d->si.samples / (MPC_FRAME_LENGTH << d->seek_pwr);
	}
	if ((file_table_size >> diff_pwr) > tmp)
		file_table_size = tmp << diff_pwr;
	d->seek_table = malloc((size_t) (tmp * sizeof(mpc_seek_t)));
	d->seek_table_size = (file_table_size + ((1 << diff_pwr) - 1)) >> diff_pwr;

	table = d->seek_table;
	mpc_bits_get_size(&r, &tmp);
	table[0] = last[0] = (mpc_seek_t) (tmp + d->si.header_position) * 8;

	if (d->seek_table_size == 1)
		return MPC_STATUS_OK;

	mpc_bits_get_size(&r, &tmp);
	last[1] = (mpc_seek_t) (tmp + d->si.header_position) * 8;
	if (diff_pwr == 0) table[1] = last[1];

	mask = (1 << diff_pwr) - 1;
	for (i = 2; i < file_table_size; i++) {
		int code = mpc_bits_golomb_dec(&r, 12);
		if (code & 1)
			code = -(code & (-1 << 1));
		code <<= 2;
		last[i & 1] = code + 2 * last[(i-1) & 1] - last[i & 1];
		if ((i & mask) == 0)
			table[i >> diff_pwr] = last[i & 1];
	}
	return MPC_STATUS_OK;
}