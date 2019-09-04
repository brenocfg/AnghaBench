#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int flags; scalar_t__ context; } ;
typedef  TYPE_1__ nstat_msg_hdr ;
struct TYPE_7__ {scalar_t__ ncs_context; int /*<<< orphan*/  ncs_seq; } ;
typedef  TYPE_2__ nstat_control_state ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 int /*<<< orphan*/  FALSE ; 
 int NSTAT_MSG_HDR_FLAG_CONTINUATION ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  nstat_send_error (TYPE_2__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
nstat_control_begin_query(
    nstat_control_state *state,
    const nstat_msg_hdr *hdrp)
{
	boolean_t partial = FALSE;

	if (hdrp->flags & NSTAT_MSG_HDR_FLAG_CONTINUATION)
	{
		/* A partial query all has been requested. */
		partial = TRUE;

		if (state->ncs_context != hdrp->context)
		{
			if (state->ncs_context != 0)
				nstat_send_error(state, state->ncs_context, EAGAIN);

			/* Initialize state for a partial query all. */
			state->ncs_context = hdrp->context;
			state->ncs_seq++;
		}
	}

	return partial;
}