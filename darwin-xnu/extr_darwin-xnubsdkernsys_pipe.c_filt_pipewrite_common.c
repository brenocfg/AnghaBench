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
struct TYPE_2__ {scalar_t__ cnt; scalar_t__ size; } ;
struct pipe {int pipe_state; TYPE_1__ pipe_buffer; struct pipe* pipe_peer; } ;
struct knote {scalar_t__ kn_data; int kn_sfflags; scalar_t__ kn_sdata; int /*<<< orphan*/  kn_flags; } ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  EV_EOF ; 
 scalar_t__ MAX_PIPESIZE (struct pipe*) ; 
 int NOTE_LOWAT ; 
 scalar_t__ PIPE_BUF ; 
 int PIPE_DRAIN ; 
 int PIPE_EOF ; 

__attribute__((used)) static int
filt_pipewrite_common(struct knote *kn, struct pipe *rpipe)
{
	struct pipe *wpipe;

	/*
	 * we're being called back via the KNOTE post
	 * we made in pipeselwakeup, and we already hold the mutex...
	 */
	wpipe = rpipe->pipe_peer;

	if ((wpipe == NULL) || (wpipe->pipe_state & (PIPE_DRAIN | PIPE_EOF))) {
		kn->kn_data = 0;
		kn->kn_flags |= EV_EOF; 
		return (1);
	}
	kn->kn_data = MAX_PIPESIZE(wpipe) - wpipe->pipe_buffer.cnt;

	int64_t lowwat = PIPE_BUF;
	if (kn->kn_sfflags & NOTE_LOWAT) {
		if (wpipe->pipe_buffer.size && kn->kn_sdata > MAX_PIPESIZE(wpipe))
			lowwat = MAX_PIPESIZE(wpipe);
		else if (kn->kn_sdata > lowwat)
			lowwat = kn->kn_sdata;
	}

	return (kn->kn_data >= lowwat);
}