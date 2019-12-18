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
 int PAUSE_SRC_LO ; 
 int XGMAC_REGISTER_END ; 
 int ql_read_other_func_xgmac_reg (struct ql_adapter*,int,int*) ; 
 int ql_read_xgmac_reg (struct ql_adapter*,int,int*) ; 

__attribute__((used)) static int ql_get_xgmac_regs(struct ql_adapter *qdev, u32 *buf,
					unsigned int other_function)
{
	int status = 0;
	int i;

	for (i = PAUSE_SRC_LO; i < XGMAC_REGISTER_END; i += 4, buf++) {
		/* We're reading 400 xgmac registers, but we filter out
		 * serveral locations that are non-responsive to reads.
		 */
		if ((i == 0x00000114) ||
			(i == 0x00000118) ||
			(i == 0x0000013c) ||
			(i == 0x00000140) ||
			(i > 0x00000150 && i < 0x000001fc) ||
			(i > 0x00000278 && i < 0x000002a0) ||
			(i > 0x000002c0 && i < 0x000002cf) ||
			(i > 0x000002dc && i < 0x000002f0) ||
			(i > 0x000003c8 && i < 0x00000400) ||
			(i > 0x00000400 && i < 0x00000410) ||
			(i > 0x00000410 && i < 0x00000420) ||
			(i > 0x00000420 && i < 0x00000430) ||
			(i > 0x00000430 && i < 0x00000440) ||
			(i > 0x00000440 && i < 0x00000450) ||
			(i > 0x00000450 && i < 0x00000500) ||
			(i > 0x0000054c && i < 0x00000568) ||
			(i > 0x000005c8 && i < 0x00000600)) {
			if (other_function)
				status =
				ql_read_other_func_xgmac_reg(qdev, i, buf);
			else
				status = ql_read_xgmac_reg(qdev, i, buf);

			if (status)
				*buf = 0xdeadbeef;
			break;
		}
	}
	return status;
}