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
typedef  int /*<<< orphan*/  ucontext_t ;
typedef  scalar_t__ cothread_t ;

/* Variables and functions */
 int /*<<< orphan*/ * co_running ; 
 int /*<<< orphan*/  swapcontext (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void co_switch(cothread_t cothread)
{
   ucontext_t *old_thread = co_running;

   co_running = (ucontext_t*)cothread;
   swapcontext(old_thread, co_running);
}