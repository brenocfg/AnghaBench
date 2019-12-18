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
struct pm8001_hba_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSGU_ODMR_CLR ; 
 int /*<<< orphan*/  ODMR_MASK_ALL ; 
 int /*<<< orphan*/  pm8001_cw32 (struct pm8001_hba_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pm80xx_chip_intx_interrupt_disable(struct pm8001_hba_info *pm8001_ha)
{
	pm8001_cw32(pm8001_ha, 0, MSGU_ODMR_CLR, ODMR_MASK_ALL);
}