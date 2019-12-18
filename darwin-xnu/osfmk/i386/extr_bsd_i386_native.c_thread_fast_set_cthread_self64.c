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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  kern_return_t ;

/* Variables and functions */
 int /*<<< orphan*/  USER_CTHREAD ; 
 int /*<<< orphan*/  current_thread () ; 
 int /*<<< orphan*/  machine_thread_set_tsd_base (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

kern_return_t
thread_fast_set_cthread_self64(uint64_t self)
{
	machine_thread_set_tsd_base(current_thread(), self);
	return (USER_CTHREAD); /* N.B.: not a kern_return_t! */
}