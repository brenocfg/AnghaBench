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
typedef  int /*<<< orphan*/  u32 ;
struct cx23885_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cx23885_gpio_clear (struct cx23885_dev*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cx23885_gpio_enable (struct cx23885_dev*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cx23885_gpio_set (struct cx23885_dev*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void f300_set_line(struct cx23885_dev *dev, u32 line, u8 lvl)
{
	cx23885_gpio_enable(dev, line, 1);
	if (lvl == 1)
		cx23885_gpio_set(dev, line);
	else
		cx23885_gpio_clear(dev, line);
}