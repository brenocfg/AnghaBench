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

/* Variables and functions */
 int chipcHw_GPIO_COUNT ; 
 size_t chipcHw_getGpioPinFunction (int) ; 
 char const** gMuxStr ; 

const char *chipcHw_getGpioPinFunctionStr(int pin)
{
	if ((pin < 0) || (pin >= chipcHw_GPIO_COUNT)) {
		return "";
	}

	return gMuxStr[chipcHw_getGpioPinFunction(pin)];
}