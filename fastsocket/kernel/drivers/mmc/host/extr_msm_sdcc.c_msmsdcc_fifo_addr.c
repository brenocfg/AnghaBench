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
typedef  scalar_t__ uint32_t ;
struct msmsdcc_host {int pdev_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ MMCIFIFO ; 
 scalar_t__ MSM_SDC1_PHYS ; 
 scalar_t__ MSM_SDC2_PHYS ; 
 scalar_t__ MSM_SDC3_PHYS ; 
 scalar_t__ MSM_SDC4_PHYS ; 

uint32_t msmsdcc_fifo_addr(struct msmsdcc_host *host)
{
	switch (host->pdev_id) {
	case 1:
		return MSM_SDC1_PHYS + MMCIFIFO;
	case 2:
		return MSM_SDC2_PHYS + MMCIFIFO;
	case 3:
		return MSM_SDC3_PHYS + MMCIFIFO;
	case 4:
		return MSM_SDC4_PHYS + MMCIFIFO;
	}
	BUG();
	return 0;
}