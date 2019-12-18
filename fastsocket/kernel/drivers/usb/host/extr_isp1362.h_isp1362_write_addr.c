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
struct isp1362_hcd {int /*<<< orphan*/  addr_reg; } ;
typedef  int /*<<< orphan*/  isp1362_reg_t ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_DELAY_ACCESS ; 
 int /*<<< orphan*/  ISP1362_REG_NO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_ACCESS_TEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _BUG_ON (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  isp1362_delay (struct isp1362_hcd*,int) ; 
 int /*<<< orphan*/  writew (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp1362_write_addr(struct isp1362_hcd *isp1362_hcd, isp1362_reg_t reg)
{
	/*_BUG_ON((reg & ISP1362_REG_WRITE_OFFSET) && !(reg & REG_ACCESS_W));*/
	REG_ACCESS_TEST(reg);
	_BUG_ON(!irqs_disabled());
	DUMMY_DELAY_ACCESS;
	writew(ISP1362_REG_NO(reg), isp1362_hcd->addr_reg);
	DUMMY_DELAY_ACCESS;
	isp1362_delay(isp1362_hcd, 1);
}