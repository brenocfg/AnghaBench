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
typedef  int /*<<< orphan*/  uint32_t ;
struct sh_flctl {int dummy; } ;
struct mtd_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 int /*<<< orphan*/  CE0_ENABLE ; 
 int /*<<< orphan*/  FLCMNCR (struct sh_flctl*) ; 
 struct sh_flctl* mtd_to_flctl (struct mtd_info*) ; 
 int /*<<< orphan*/  readl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writel (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void flctl_select_chip(struct mtd_info *mtd, int chipnr)
{
	struct sh_flctl *flctl = mtd_to_flctl(mtd);
	uint32_t flcmncr_val = readl(FLCMNCR(flctl));

	switch (chipnr) {
	case -1:
		flcmncr_val &= ~CE0_ENABLE;
		writel(flcmncr_val, FLCMNCR(flctl));
		break;
	case 0:
		flcmncr_val |= CE0_ENABLE;
		writel(flcmncr_val, FLCMNCR(flctl));
		break;
	default:
		BUG();
	}
}