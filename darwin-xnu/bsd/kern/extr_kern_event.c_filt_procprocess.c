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
struct kevent_internal_s {int dummy; } ;
struct knote {scalar_t__ kn_fflags; scalar_t__ kn_data; int /*<<< orphan*/  kn_flags; struct kevent_internal_s kn_kevent; } ;
struct filt_process_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_CLEAR ; 
 int /*<<< orphan*/  proc_klist_lock () ; 
 int /*<<< orphan*/  proc_klist_unlock () ; 

__attribute__((used)) static int
filt_procprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev)
{
#pragma unused(data)
	int res;

	proc_klist_lock();
	res = (kn->kn_fflags != 0);
	if (res) {
		*kev = kn->kn_kevent;
		kn->kn_flags |= EV_CLEAR;	/* automatically set */
		kn->kn_fflags = 0;
		kn->kn_data = 0;
	}
	proc_klist_unlock();
	return res;
}