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
 int /*<<< orphan*/  kprintf_lock ; 
 int /*<<< orphan*/  simple_lock_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
kprintf_break_lock(void)
{
	simple_lock_init(&kprintf_lock, 0);
}