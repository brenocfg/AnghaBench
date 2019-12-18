#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sh_mobile_ceu_dev {TYPE_1__* pdata; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int SH_CEU_FLAG_USE_16BIT_BUS ; 
 int SH_CEU_FLAG_USE_8BIT_BUS ; 
 unsigned long SOCAM_DATAWIDTH_16 ; 
 unsigned long SOCAM_DATAWIDTH_8 ; 
 unsigned long SOCAM_DATAWIDTH_MASK ; 
 unsigned long SOCAM_DATA_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_HSYNC_ACTIVE_LOW ; 
 unsigned long SOCAM_MASTER ; 
 unsigned long SOCAM_PCLK_SAMPLE_RISING ; 
 unsigned long SOCAM_VSYNC_ACTIVE_HIGH ; 
 unsigned long SOCAM_VSYNC_ACTIVE_LOW ; 

__attribute__((used)) static unsigned long make_bus_param(struct sh_mobile_ceu_dev *pcdev)
{
	unsigned long flags;

	flags = SOCAM_MASTER |
		SOCAM_PCLK_SAMPLE_RISING |
		SOCAM_HSYNC_ACTIVE_HIGH |
		SOCAM_HSYNC_ACTIVE_LOW |
		SOCAM_VSYNC_ACTIVE_HIGH |
		SOCAM_VSYNC_ACTIVE_LOW |
		SOCAM_DATA_ACTIVE_HIGH;

	if (pcdev->pdata->flags & SH_CEU_FLAG_USE_8BIT_BUS)
		flags |= SOCAM_DATAWIDTH_8;

	if (pcdev->pdata->flags & SH_CEU_FLAG_USE_16BIT_BUS)
		flags |= SOCAM_DATAWIDTH_16;

	if (flags & SOCAM_DATAWIDTH_MASK)
		return flags;

	return 0;
}