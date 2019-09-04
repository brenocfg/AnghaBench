#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ thread_t ;
struct TYPE_4__ {struct knote* knote; } ;
struct TYPE_5__ {TYPE_1__ uus_kevent_register; } ;
struct uthread {TYPE_2__ uu_save; } ;
struct knote {scalar_t__ kn_hook; } ;
struct kevent_internal_s {int /*<<< orphan*/  data; int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int /*<<< orphan*/  f_extended_codes; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_ERROR ; 
 int /*<<< orphan*/  EXDEV ; 
 int FILTER_REGISTER_WAIT ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ current_thread () ; 
 struct uthread* get_bsdthread_info (scalar_t__) ; 
 TYPE_3__* knote_fops (struct knote*) ; 
 int /*<<< orphan*/  thread_reference (scalar_t__) ; 

__attribute__((used)) static int
kevent_register_wait_prepare(struct knote *kn, struct kevent_internal_s *kev)
{
	thread_t thread = current_thread();
	struct uthread *uth = get_bsdthread_info(thread);

	assert(knote_fops(kn)->f_extended_codes);

	if (kn->kn_hook == NULL) {
		thread_reference(thread);
		kn->kn_hook = thread;
	} else if (kn->kn_hook != thread) {
		/*
		 * kn_hook may be set from a previous aborted wait
		 * However, it has to be from the same thread.
		 */
		kev->flags |= EV_ERROR;
		kev->data = EXDEV;
		return 0;
	}

	uth->uu_save.uus_kevent_register.knote = kn;
	return FILTER_REGISTER_WAIT;
}