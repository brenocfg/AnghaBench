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
 int /*<<< orphan*/  hw_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic_hooks ; 
 int /*<<< orphan*/  panic_hooks_lock ; 
 int /*<<< orphan*/  queue_init (int /*<<< orphan*/ *) ; 

void panic_hooks_init(void)
{
	hw_lock_init(&panic_hooks_lock);
	queue_init(&panic_hooks);
}