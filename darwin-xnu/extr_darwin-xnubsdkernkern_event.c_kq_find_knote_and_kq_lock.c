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
struct proc {int dummy; } ;
struct kqueue {int dummy; } ;
struct knote {int dummy; } ;
struct kevent_internal_s {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  knhash_lock (struct proc*) ; 
 int /*<<< orphan*/  knhash_unlock (struct proc*) ; 
 struct knote* knote_fdfind (struct kqueue*,struct kevent_internal_s*,int,struct proc*) ; 
 int /*<<< orphan*/  kqlock (struct kqueue*) ; 
 int /*<<< orphan*/  proc_fdlock (struct proc*) ; 
 int /*<<< orphan*/  proc_fdunlock (struct proc*) ; 

__attribute__((used)) static struct knote *
kq_find_knote_and_kq_lock(struct kqueue *kq, struct kevent_internal_s *kev,
		bool is_fd, struct proc *p)
{
	struct knote * ret;

	if (is_fd)
		proc_fdlock(p);
	else
		knhash_lock(p);

	ret = knote_fdfind(kq, kev, is_fd, p);

	if (ret) {
		kqlock(kq);
	}

	if (is_fd)
		proc_fdunlock(p);
	else
		knhash_unlock(p);

	return ret;
}