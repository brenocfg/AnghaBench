#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int mpc_uint64_t ;
typedef  int /*<<< orphan*/  mpc_uint32_t ;
typedef  int /*<<< orphan*/  mpc_status ;
typedef  scalar_t__ mpc_seek_t ;
struct TYPE_9__ {int chap_nb; scalar_t__ chap_pos; int /*<<< orphan*/  bits_reader; } ;
typedef  TYPE_1__ mpc_demux ;
struct TYPE_10__ {int size; int /*<<< orphan*/  key; } ;
typedef  TYPE_2__ mpc_block ;

/* Variables and functions */
 int /*<<< orphan*/  MPC_AUTO_FAIL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MPC_STATUS_FAIL ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int mpc_bits_get_block (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mpc_bits_get_size (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  mpc_demux_ST (TYPE_1__*) ; 
 int mpc_demux_fill (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mpc_demux_pos (TYPE_1__*) ; 
 int /*<<< orphan*/  mpc_demux_seek (TYPE_1__*,scalar_t__,int) ; 

__attribute__((used)) static mpc_status mpc_demux_SP(mpc_demux * d, int size, int block_size)
{
	mpc_seek_t cur;
	mpc_uint64_t ptr;
	mpc_block b;
	int st_head_size;

	cur = mpc_demux_pos(d);
	mpc_bits_get_size(&d->bits_reader, &ptr);
	MPC_AUTO_FAIL( mpc_demux_seek(d, (ptr - size) * 8 + cur, 11) );
	st_head_size = mpc_bits_get_block(&d->bits_reader, &b);
	if (memcmp(b.key, "ST", 2) == 0) {
		d->chap_pos = (ptr - size + b.size + st_head_size) * 8 + cur;
		d->chap_nb = -1;
		if (mpc_demux_fill(d, (mpc_uint32_t) b.size, 0) < b.size)
			return MPC_STATUS_FAIL;
		MPC_AUTO_FAIL( mpc_demux_ST(d) );
	}
	return mpc_demux_seek(d, cur, 11 + block_size);
}