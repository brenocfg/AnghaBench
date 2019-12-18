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
 int XGMAC_ADDR ; 
 int XGMAC_ADDR_R ; 
 int /*<<< orphan*/  XGMAC_ADDR_RDY ; 
 int /*<<< orphan*/  XGMAC_ADDR_XME ; 
 int XGMAC_DATA ; 
 int ql_read_other_func_reg (struct ql_adapter*,int) ; 
 int ql_wait_other_func_reg_rdy (struct ql_adapter*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ql_write_other_func_reg (struct ql_adapter*,int,int) ; 

__attribute__((used)) static int ql_read_other_func_xgmac_reg(struct ql_adapter *qdev, u32 reg,
							u32 *data)
{
	int status = 0;

	/* wait for reg to come ready */
	status = ql_wait_other_func_reg_rdy(qdev, XGMAC_ADDR / 4,
						XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	if (status)
		goto exit;

	/* set up for reg read */
	ql_write_other_func_reg(qdev, XGMAC_ADDR / 4, reg | XGMAC_ADDR_R);

	/* wait for reg to come ready */
	status = ql_wait_other_func_reg_rdy(qdev, XGMAC_ADDR / 4,
						XGMAC_ADDR_RDY, XGMAC_ADDR_XME);
	if (status)
		goto exit;

	/* get the data */
	*data = ql_read_other_func_reg(qdev, XGMAC_DATA / 4);
exit:
	return status;
}