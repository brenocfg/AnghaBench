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

/* Variables and functions */
#define  MMC_POWER_OFF 130 
#define  MMC_POWER_ON 129 
#define  MMC_POWER_UP 128 

__attribute__((used)) static char *mmc_powerstring(u8 power_mode)
{
	switch (power_mode) {
	case MMC_POWER_OFF: return "off";
	case MMC_POWER_UP:  return "up";
	case MMC_POWER_ON:  return "on";
	}
	return "?";
}