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
typedef  int /*<<< orphan*/  thread_t ;
typedef  int /*<<< orphan*/  processor_set_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
 int /*<<< orphan*/  pset_unlock (int /*<<< orphan*/ ) ; 

__attribute__((used)) static thread_t
sched_multiq_steal_thread(processor_set_t pset)
{
	pset_unlock(pset);
	return (THREAD_NULL);
}