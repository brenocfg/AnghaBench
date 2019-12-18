#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* thread_t ;
struct TYPE_3__ {int /*<<< orphan*/  at_safe_point; int /*<<< orphan*/  wait_event; int /*<<< orphan*/ * waitq; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  NO_EVENT64 ; 

__attribute__((used)) static inline void thread_clear_waitq_state(thread_t thread)
{
	thread->waitq = NULL;
	thread->wait_event = NO_EVENT64;
	thread->at_safe_point = FALSE;
}