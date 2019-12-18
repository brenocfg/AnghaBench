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
typedef  int u8 ;
typedef  int u32 ;
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_ODMR_CLR ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pm80xx_chip_intx_interrupt_enable (struct pm8001_hba_info*) ; 

__attribute__((used)) static void
pm80xx_chip_interrupt_enable(struct pm8001_hba_info *pm8001_ha, u8 vec)
{
#ifdef PM8001_USE_MSIX
	u32 mask;
	mask = (u32)(1 << vec);

	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR_CLR, (u32)(mask & 0xFFFFFFFF));
	return;
#endif
	pm80xx_chip_intx_interrupt_enable(pm8001_ha);

}