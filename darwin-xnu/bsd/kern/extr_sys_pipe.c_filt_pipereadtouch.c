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
struct knote {int /*<<< orphan*/  kn_sfflags; int /*<<< orphan*/  kn_sdata; TYPE_1__* kn_fp; } ;
struct kevent_internal_s {int /*<<< orphan*/  fflags; int /*<<< orphan*/  data; } ;
struct TYPE_2__ {scalar_t__ f_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int filt_piperead_common (struct knote*,struct pipe*) ; 

__attribute__((used)) static int
filt_pipereadtouch(struct knote *kn, struct kevent_internal_s *kev)
{
	struct pipe *rpipe = (struct pipe *)kn->kn_fp->f_data;
	int retval;

	PIPE_LOCK(rpipe);

	/* accept new inputs (and save the low water threshold and flag) */
	kn->kn_sdata = kev->data;
	kn->kn_sfflags = kev->fflags;

	/* identify if any events are now fired */
	retval = filt_piperead_common(kn, rpipe);

	PIPE_UNLOCK(rpipe);

	return retval;
}