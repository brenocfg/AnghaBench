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
 int /*<<< orphan*/  KEY_GC_KEY_EXPIRED ; 
 int /*<<< orphan*/  LONG_MAX ; 
 int /*<<< orphan*/  kenter (char*) ; 
 int /*<<< orphan*/  key_gc_flags ; 
 int /*<<< orphan*/  key_gc_next_run ; 
 int /*<<< orphan*/  key_schedule_gc_work () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void key_gc_timer_func(unsigned long data)
{
	kenter("");
	key_gc_next_run = LONG_MAX;
	set_bit(KEY_GC_KEY_EXPIRED, &key_gc_flags);
	key_schedule_gc_work();
}