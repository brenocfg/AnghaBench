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
 int GPIO18_RDY_MD ; 
 int GPIO_IN ; 
 int /*<<< orphan*/  pxa_gpio_mode (int) ; 

__attribute__((used)) static void spitz_postsuspend(void)
{
	pxa_gpio_mode(GPIO18_RDY_MD);
	pxa_gpio_mode(10 | GPIO_IN);
}