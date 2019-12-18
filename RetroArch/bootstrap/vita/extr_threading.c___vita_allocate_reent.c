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
struct reent_for_thread {scalar_t__ thread_id; } ;

/* Variables and functions */
 int MAX_THREADS ; 
 struct reent_for_thread* reent_list ; 

__attribute__((used)) static inline struct reent_for_thread *__vita_allocate_reent(void)
{
	int i;
	struct reent_for_thread *free_reent = 0;

	for (i = 0; i < MAX_THREADS; ++i)
		if (reent_list[i].thread_id == 0) {
			free_reent = &reent_list[i];
			break;
		}

	return free_reent;
}