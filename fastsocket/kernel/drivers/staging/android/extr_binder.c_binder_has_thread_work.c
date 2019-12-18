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
struct binder_thread {scalar_t__ return_error; int looper; int /*<<< orphan*/  todo; } ;

/* Variables and functions */
 int BINDER_LOOPER_STATE_NEED_RETURN ; 
 scalar_t__ BR_OK ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int binder_has_thread_work(struct binder_thread *thread)
{
	return !list_empty(&thread->todo) || thread->return_error != BR_OK ||
		(thread->looper & BINDER_LOOPER_STATE_NEED_RETURN);
}