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
struct cx231xx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLEEP_S5H1432 ; 
 int /*<<< orphan*/  cx231xx_set_gpio_value (struct cx231xx*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void cx231xx_sleep_s5h1432(struct cx231xx *dev)
{
	cx231xx_set_gpio_value(dev, SLEEP_S5H1432, 0);
}