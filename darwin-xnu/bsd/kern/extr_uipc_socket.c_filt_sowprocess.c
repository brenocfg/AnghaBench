#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct socket {int dummy; } ;
struct kevent_internal_s {int dummy; } ;
struct knote {int kn_flags; scalar_t__ kn_data; scalar_t__ kn_fflags; struct kevent_internal_s kn_kevent; TYPE_2__* kn_fp; } ;
struct filt_process_s {int dummy; } ;
struct TYPE_4__ {TYPE_1__* f_fglob; } ;
struct TYPE_3__ {scalar_t__ fg_data; } ;

/* Variables and functions */
 int EV_CLEAR ; 
 int filt_sowrite_common (struct knote*,struct socket*) ; 
 int /*<<< orphan*/  socket_lock (struct socket*,int) ; 
 int /*<<< orphan*/  socket_unlock (struct socket*,int) ; 

__attribute__((used)) static int
filt_sowprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev)
{
#pragma unused(data)
	struct socket *so = (struct socket *)kn->kn_fp->f_fglob->fg_data;
	int ret;

	socket_lock(so, 1);
	ret = filt_sowrite_common(kn, so);
	if (ret) {
		*kev = kn->kn_kevent;
		if (kn->kn_flags & EV_CLEAR) {
			kn->kn_fflags = 0;
			kn->kn_data = 0;
		}
	}
	socket_unlock(so, 1);
	return ret;
}