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
typedef  unsigned int u32 ;

/* Variables and functions */
 int MPC8XXX_GPIO_PINS ; 

__attribute__((used)) static inline u32 mpc8xxx_gpio2mask(unsigned int gpio)
{
	return 1u << (MPC8XXX_GPIO_PINS - 1 - gpio);
}