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
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  IRQ_AMIGA_VERTB ; 
 int /*<<< orphan*/  amijoy_interrupt ; 
 int /*<<< orphan*/  amijoy_mutex ; 
 int /*<<< orphan*/  amijoy_used ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void amijoy_close(struct input_dev *dev)
{
	mutex_lock(&amijoy_mutex);
	if (!--amijoy_used)
		free_irq(IRQ_AMIGA_VERTB, amijoy_interrupt);
	mutex_unlock(&amijoy_mutex);
}