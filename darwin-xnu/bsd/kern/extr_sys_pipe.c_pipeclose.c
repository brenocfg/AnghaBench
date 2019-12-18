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
struct TYPE_2__ {int /*<<< orphan*/  si_note; } ;
struct pipe {int pipe_state; struct pipe* pipe_peer; TYPE_1__ pipe_sel; int /*<<< orphan*/ * pipe_label; scalar_t__ pipe_busy; } ;

/* Variables and functions */
 int /*<<< orphan*/  EV_RCLOSED ; 
 int /*<<< orphan*/  KNOTE (int /*<<< orphan*/ *,int) ; 
 int PIPE_DRAIN ; 
 int PIPE_EOF ; 
 int PIPE_KNOTE ; 
 int /*<<< orphan*/  PIPE_LOCK (struct pipe*) ; 
 int /*<<< orphan*/ * PIPE_MTX (struct pipe*) ; 
 int /*<<< orphan*/  PIPE_UNLOCK (struct pipe*) ; 
 int PIPE_WANT ; 
 int PIPE_WSELECT ; 
 int /*<<< orphan*/  PRIBIO ; 
 int /*<<< orphan*/  evpipefree (struct pipe*) ; 
 int /*<<< orphan*/  lck_mtx_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_pipe_label_destroy (struct pipe*) ; 
 int /*<<< orphan*/  msleep (struct pipe*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_free_kmem (struct pipe*) ; 
 int /*<<< orphan*/  pipe_garbage_collect (struct pipe*) ; 
 int /*<<< orphan*/  pipe_mtx_grp ; 
 int /*<<< orphan*/  pipe_zone ; 
 int /*<<< orphan*/  pipeselwakeup (struct pipe*,struct pipe*) ; 
 int /*<<< orphan*/  postpipeevent (struct pipe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wakeup (struct pipe*) ; 
 int /*<<< orphan*/  zfree (int /*<<< orphan*/ ,struct pipe*) ; 

__attribute__((used)) static void
pipeclose(struct pipe *cpipe)
{
	struct pipe *ppipe;

	if (cpipe == NULL)
		return;
	/* partially created pipes won't have a valid mutex. */
	if (PIPE_MTX(cpipe) != NULL)
		PIPE_LOCK(cpipe);
		

	/*
	 * If the other side is blocked, wake it up saying that
	 * we want to close it down.
	 */
	cpipe->pipe_state &= ~PIPE_DRAIN;
	cpipe->pipe_state |= PIPE_EOF;
	pipeselwakeup(cpipe, cpipe);
	
	while (cpipe->pipe_busy) {
		cpipe->pipe_state |= PIPE_WANT;

		wakeup(cpipe);
 		msleep(cpipe, PIPE_MTX(cpipe), PRIBIO, "pipecl", 0);
	}

#if CONFIG_MACF
	/*
	 * Free the shared pipe label only after the two ends are disconnected.
	 */
	if (cpipe->pipe_label != NULL && cpipe->pipe_peer == NULL)
		mac_pipe_label_destroy(cpipe);
#endif

	/*
	 * Disconnect from peer
	 */
	if ((ppipe = cpipe->pipe_peer) != NULL) {

		ppipe->pipe_state &= ~(PIPE_DRAIN);
		ppipe->pipe_state |= PIPE_EOF;

		pipeselwakeup(ppipe, ppipe);
		wakeup(ppipe);

		if (cpipe->pipe_state & PIPE_KNOTE)
		        KNOTE(&ppipe->pipe_sel.si_note, 1);

		postpipeevent(ppipe, EV_RCLOSED);

		ppipe->pipe_peer = NULL;
	}
	evpipefree(cpipe);

	/*
	 * free resources
	 */
	if (PIPE_MTX(cpipe) != NULL) {
		if (ppipe != NULL) {
			/*
			 * since the mutex is shared and the peer is still
			 * alive, we need to release the mutex, not free it
			 */
			PIPE_UNLOCK(cpipe);
		} else {
			/*
			 * peer is gone, so we're the sole party left with
			 * interest in this mutex... unlock and free it
			 */
			PIPE_UNLOCK(cpipe);
			lck_mtx_free(PIPE_MTX(cpipe), pipe_mtx_grp);
		}
	}
	pipe_free_kmem(cpipe);
	if (cpipe->pipe_state & PIPE_WSELECT) {
		pipe_garbage_collect(cpipe);
	} else {
		zfree(pipe_zone, cpipe);
		pipe_garbage_collect(NULL);
	}

}