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
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  kasan_lock_holder ; 
 int /*<<< orphan*/  kasan_vm_lock ; 
 int /*<<< orphan*/  ml_set_interrupts_enabled (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  simple_unlock (int /*<<< orphan*/ *) ; 

void
kasan_unlock(boolean_t b)
{
	kasan_lock_holder = THREAD_NULL;
	simple_unlock(&kasan_vm_lock);
	ml_set_interrupts_enabled(b);
}