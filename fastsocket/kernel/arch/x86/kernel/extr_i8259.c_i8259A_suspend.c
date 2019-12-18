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
struct sys_device {int dummy; } ;
typedef  int /*<<< orphan*/  pm_message_t ;

/* Variables and functions */
 int /*<<< orphan*/  irq_trigger ; 
 int /*<<< orphan*/  save_ELCR (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int i8259A_suspend(struct sys_device *dev, pm_message_t state)
{
	save_ELCR(irq_trigger);
	return 0;
}