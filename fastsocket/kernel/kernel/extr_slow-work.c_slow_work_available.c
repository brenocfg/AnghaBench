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
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  slow_work_queue ; 
 int /*<<< orphan*/  vslow_work_executing_count ; 
 int /*<<< orphan*/  vslow_work_queue ; 

__attribute__((used)) static inline bool slow_work_available(int vsmax)
{
	return !list_empty(&slow_work_queue) ||
		(!list_empty(&vslow_work_queue) &&
		 atomic_read(&vslow_work_executing_count) < vsmax);
}