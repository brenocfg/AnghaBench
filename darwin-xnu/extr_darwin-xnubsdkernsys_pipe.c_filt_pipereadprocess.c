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
struct pipe {int dummy; } ;
struct kevent_internal_s {int dummy; } ;
struct knote {int kn_flags; scalar_t__ kn_data; scalar_t__ kn_fflags; struct kevent_internal_s kn_kevent; TYPE_1__* kn_fp; } ;
struct filt_process_s {int dummy; } ;
struct TYPE_2__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int EV_CLEAR ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int filt_piperead_common (struct knote*,struct pipe*) ; 

__attribute__((used)) static int
filt_pipereadprocess(struct knote *kn, struct filt_process_s *data, struct kevent_internal_s *kev)
{
#pragma unused(data)
	struct pipe *rpipe = (struct pipe *)kn->kn_fp->f_data;
	int    retval;

	PIPE_LOCK(rpipe);
	retval = filt_piperead_common(kn, rpipe);
	if (retval) {
		*kev = kn->kn_kevent;
		if (kn->kn_flags & EV_CLEAR) {
			kn->kn_fflags = 0;
			kn->kn_data = 0;
		}
	}
	PIPE_UNLOCK(rpipe);

	return (retval);
}