#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int BUSY ; 
 int BYTECNT (unsigned int) ; 
 int EBUSY ; 
 int EINVAL ; 
 int OP_WR ; 
 int /*<<< orphan*/  SF_ATTEMPTS ; 
 int SF_CONT ; 
 int /*<<< orphan*/  SF_DATA ; 
 int SF_LOCK ; 
 int /*<<< orphan*/  SF_OP ; 
 int t4_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t4_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  t4_write_reg (struct adapter*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sf1_write(struct adapter *adapter, unsigned int byte_cnt, int cont,
		     int lock, u32 val)
{
	if (!byte_cnt || byte_cnt > 4)
		return -EINVAL;
	if (t4_read_reg(adapter, SF_OP) & BUSY)
		return -EBUSY;
	cont = cont ? SF_CONT : 0;
	lock = lock ? SF_LOCK : 0;
	t4_write_reg(adapter, SF_DATA, val);
	t4_write_reg(adapter, SF_OP, lock |
		     cont | BYTECNT(byte_cnt - 1) | OP_WR);
	return t4_wait_op_done(adapter, SF_OP, BUSY, 0, SF_ATTEMPTS, 5);
}