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
struct TYPE_2__ {scalar_t__ device; } ;

/* Variables and functions */
 int CPLD_SPIC ; 
 int CPLD_SPIC_CS_CODEC ; 
 int CPLD_SPIC_CS_TOUCH ; 
 scalar_t__ DEVICE_CODEC ; 
 scalar_t__ DEVICE_TOUCH ; 
 TYPE_1__ ssp_configuration ; 

__attribute__((used)) static void ssp_chip_select (int enable)
{
#if defined (CONFIG_MACH_LPD7A400)
	int select;

	if (ssp_configuration.device == DEVICE_CODEC)
		select = CPLD_SPIC_CS_CODEC;
	else if (ssp_configuration.device == DEVICE_TOUCH)
		select = CPLD_SPIC_CS_TOUCH;
	else
		return;

	if (enable)
		CPLD_SPIC = select;
	else
		CPLD_SPIC = 0;
#endif
}