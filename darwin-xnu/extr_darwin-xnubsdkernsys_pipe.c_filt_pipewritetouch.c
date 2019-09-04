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
struct knote {int /*<<< orphan*/  kn_sdata; int /*<<< orphan*/  kn_sfflags; TYPE_1__* kn_fp; } ;
struct kevent_internal_s {int /*<<< orphan*/  data; int /*<<< orphan*/  fflags; } ;
struct TYPE_2__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int filt_pipewrite_common (struct knote*,struct pipe*) ; 

__attribute__((used)) static int
filt_pipewritetouch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct pipe *rpipe = (struct pipe *)kn->kn_fp->f_data;
	int res;

	PIPE_LOCK(rpipe);

	/* accept new kevent data (and save off lowat threshold and flag) */
	kn->kn_sfflags = kev->fflags;
	kn->kn_sdata = kev->data;

	/* determine if any event is now deemed fired */
	res = filt_pipewrite_common(kn, rpipe);

	PIPE_UNLOCK(rpipe);

	return res;
}