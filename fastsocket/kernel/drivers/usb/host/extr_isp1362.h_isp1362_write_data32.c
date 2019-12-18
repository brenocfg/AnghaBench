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
typedef  int u16 ;
struct isp1362_hcd {int /*<<< orphan*/  data_reg; } ;

/* Variables and functions */
 int /*<<< orphan*/  DUMMY_DELAY_ACCESS ; 
 int /*<<< orphan*/  _BUG_ON (int) ; 
 int /*<<< orphan*/  irqs_disabled () ; 
 int /*<<< orphan*/  writel (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writew (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void isp1362_write_data32(struct isp1362_hcd *isp1362_hcd, u32 val)
{
	_BUG_ON(!irqs_disabled());
#if USE_32BIT
	DUMMY_DELAY_ACCESS;
	writel(val, isp1362_hcd->data_reg);
#else
	DUMMY_DELAY_ACCESS;
	writew((u16)val, isp1362_hcd->data_reg);
	DUMMY_DELAY_ACCESS;
	writew(val >> 16, isp1362_hcd->data_reg);
#endif
}