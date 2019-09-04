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
struct TYPE_3__ {int /*<<< orphan*/  si_note; } ;
struct pipe {int pipe_state; TYPE_1__ pipe_sel; struct pipe* pipe_peer; } ;
struct knote {scalar_t__ kn_filter; TYPE_2__* kn_fp; } ;
struct TYPE_4__ {scalar_t__ f_data; } ;

/* Variables and functions */
 scalar_t__ EVFILT_WRITE ; 
 scalar_t__ KNOTE_DETACH (int /*<<< orphan*/ *,struct knote*) ; 
 int PIPE_KNOTE ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 

__attribute__((used)) static void
filt_pipedetach(struct knote *kn)
{
	struct pipe *cpipe = (struct pipe *)kn->kn_fp->f_data;

	PIPE_LOCK(cpipe);

	if (kn->kn_filter == EVFILT_WRITE) {
	        if (cpipe->pipe_peer == NULL) {
		        PIPE_UNLOCK(cpipe);
			return;
		}
		cpipe = cpipe->pipe_peer;
	}
	if (cpipe->pipe_state & PIPE_KNOTE) {
	        if (KNOTE_DETACH(&cpipe->pipe_sel.si_note, kn))
		        cpipe->pipe_state &= ~PIPE_KNOTE;
	}
	PIPE_UNLOCK(cpipe);
}