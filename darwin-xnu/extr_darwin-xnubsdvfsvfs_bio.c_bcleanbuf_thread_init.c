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
typedef  int /*<<< orphan*/  thread_continue_t ;

/* Variables and functions */
 int /*<<< orphan*/  THREAD_NULL ; 
 scalar_t__ bcleanbuf_thread ; 
 int /*<<< orphan*/  kernel_thread_start (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bcleanbuf_thread_init(void)
{
	thread_t	thread = THREAD_NULL;

	/* create worker thread */
	kernel_thread_start((thread_continue_t)bcleanbuf_thread, NULL, &thread);
	thread_deallocate(thread);
}