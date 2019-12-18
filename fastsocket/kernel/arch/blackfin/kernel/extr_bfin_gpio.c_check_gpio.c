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
 int EINVAL ; 
 unsigned int GPIO_PB15 ; 
 unsigned int GPIO_PC14 ; 
 unsigned int GPIO_PC15 ; 
 unsigned int GPIO_PH14 ; 
 unsigned int GPIO_PH15 ; 
 unsigned int GPIO_PJ14 ; 
 unsigned int GPIO_PJ15 ; 
 unsigned int MAX_BLACKFIN_GPIOS ; 

inline int check_gpio(unsigned gpio)
{
#if defined(CONFIG_BF54x)
	if (gpio == GPIO_PB15 || gpio == GPIO_PC14 || gpio == GPIO_PC15
	    || gpio == GPIO_PH14 || gpio == GPIO_PH15
	    || gpio == GPIO_PJ14 || gpio == GPIO_PJ15)
		return -EINVAL;
#endif
	if (gpio >= MAX_BLACKFIN_GPIOS)
		return -EINVAL;
	return 0;
}