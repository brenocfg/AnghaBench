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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  err_printk (struct device*,int /*<<< orphan*/ *,char*,void*) ; 
 scalar_t__ object_is_on_stack (void*) ; 

__attribute__((used)) static void check_for_stack(struct device *dev, void *addr)
{
	if (object_is_on_stack(addr))
		err_printk(dev, NULL, "DMA-API: device driver maps memory from"
				"stack [addr=%p]\n", addr);
}