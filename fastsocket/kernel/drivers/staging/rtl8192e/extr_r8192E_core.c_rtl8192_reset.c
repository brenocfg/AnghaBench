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
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  printk (char*) ; 
 int /*<<< orphan*/  rtl8192_irq_disable (struct net_device*) ; 

__attribute__((used)) static void rtl8192_reset(struct net_device *dev)
{
    rtl8192_irq_disable(dev);
    printk("This is RTL819xP Reset procedure\n");
}