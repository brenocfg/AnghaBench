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
 int PIPE_DRAIN ; 
 int PIPE_EOF ; 

__attribute__((used)) static int
filt_piperead_common(struct knote *kn, struct pipe *rpipe)
{
	struct pipe *wpipe;
	int    retval;

	/*
	 * we're being called back via the KNOTE post
	 * we made in pipeselwakeup, and we already hold the mutex...
	 */

	wpipe = rpipe->pipe_peer;
	kn->kn_data = rpipe->pipe_buffer.cnt;
	if ((rpipe->pipe_state & (PIPE_DRAIN | PIPE_EOF)) ||
	    (wpipe == NULL) || (wpipe->pipe_state & (PIPE_DRAIN | PIPE_EOF))) {
		kn->kn_flags |= EV_EOF;
		retval = 1;
	} else {
		int64_t lowwat = 1;
		if (kn->kn_sfflags & NOTE_LOWAT) {
			if (rpipe->pipe_buffer.size && kn->kn_sdata > MAX_PIPESIZE(rpipe))
				lowwat = MAX_PIPESIZE(rpipe);
			else if (kn->kn_sdata > lowwat)
				lowwat = kn->kn_sdata;
		}
		retval = kn->kn_data >= lowwat;
	}
	return (retval);
}