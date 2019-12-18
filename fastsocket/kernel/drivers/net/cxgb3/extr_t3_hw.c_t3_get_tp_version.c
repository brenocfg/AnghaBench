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
typedef  int /*<<< orphan*/  u32 ;
struct adapter {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD0 ; 
 int /*<<< orphan*/  A_TP_EMBED_OP_FIELD1 ; 
 int /*<<< orphan*/  t3_read_reg (struct adapter*,int /*<<< orphan*/ ) ; 
 int t3_wait_op_done (struct adapter*,int /*<<< orphan*/ ,int,int,int,int) ; 
 int /*<<< orphan*/  t3_write_reg (struct adapter*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int t3_get_tp_version(struct adapter *adapter, u32 *vers)
{
	int ret;

	/* Get version loaded in SRAM */
	t3_write_reg(adapter, A_TP_EMBED_OP_FIELD0, 0);
	ret = t3_wait_op_done(adapter, A_TP_EMBED_OP_FIELD0,
			      1, 1, 5, 1);
	if (ret)
		return ret;

	*vers = t3_read_reg(adapter, A_TP_EMBED_OP_FIELD1);

	return 0;
}