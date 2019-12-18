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
struct ql_adapter {int dummy; } ;

/* Variables and functions */
 int PROC_ADDR_R ; 
 int XG_SERDES_ADDR ; 
 int /*<<< orphan*/  XG_SERDES_ADDR_RDY ; 
 int XG_SERDES_DATA ; 
 int ql_read_other_func_reg (struct ql_adapter*,int) ; 
 int ql_wait_other_func_reg_rdy (struct ql_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write_other_func_reg (struct ql_adapter*,int,int) ; 

__attribute__((used)) static int ql_read_other_func_serdes_reg(struct ql_adapter *qdev, u32 reg,
							u32 *data)
{
	int status;

	/* wait for reg to come ready */
	status = ql_wait_other_func_reg_rdy(qdev, XG_SERDES_ADDR / 4,
						XG_SERDES_ADDR_RDY, 0);
	if (status)
		goto exit;

	/* set up for reg read */
	ql_write_other_func_reg(qdev, XG_SERDES_ADDR/4, reg | PROC_ADDR_R);

	/* wait for reg to come ready */
	status = ql_wait_other_func_reg_rdy(qdev, XG_SERDES_ADDR / 4,
						XG_SERDES_ADDR_RDY, 0);
	if (status)
		goto exit;

	/* get the data */
	*data = ql_read_other_func_reg(qdev, (XG_SERDES_DATA / 4));
exit:
	return status;
}