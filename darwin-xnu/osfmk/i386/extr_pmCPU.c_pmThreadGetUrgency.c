#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_2__ {int /*<<< orphan*/  next_thread; } ;

/* Variables and functions */
 int THREAD_URGENCY_REAL_TIME ; 
 TYPE_1__* current_processor () ; 
 int thread_get_urgency (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
pmThreadGetUrgency(uint64_t *rt_period, uint64_t *rt_deadline)
{
	int             urgency;
	uint64_t        arg1, arg2;

	urgency = thread_get_urgency(current_processor()->next_thread, &arg1, &arg2);

	if (urgency == THREAD_URGENCY_REAL_TIME) {
		if (rt_period != NULL)
			*rt_period = arg1;
		
		if (rt_deadline != NULL)
			*rt_deadline = arg2;
	}

	return(urgency);
}