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
typedef  int /*<<< orphan*/ * thread_t ;
struct knote {int /*<<< orphan*/ * kn_hook; } ;

/* Variables and functions */
 int /*<<< orphan*/  thread_deallocate (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
kevent_register_wait_cleanup(struct knote *kn)
{
	thread_t thread = kn->kn_hook;
	kn->kn_hook = NULL;
	thread_deallocate(thread);
}