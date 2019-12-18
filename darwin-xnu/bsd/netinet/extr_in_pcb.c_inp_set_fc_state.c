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
struct inpcb {int inp_flags; TYPE_1__* inp_socket; int /*<<< orphan*/  inp_flowhash; } ;
struct TYPE_2__ {int /*<<< orphan*/  so_flags; } ;

/* Variables and functions */
#define  FADV_FLOW_CONTROLLED 129 
#define  FADV_SUSPENDED 128 
 int /*<<< orphan*/  INPFC_SOLOCKED ; 
 int INP_FC_FEEDBACK ; 
 int INP_FLOW_CONTROLLED ; 
 int INP_FLOW_SUSPENDED ; 
 int /*<<< orphan*/  SOF_SUSPENDED ; 
 int SO_FILT_HINT_LOCKED ; 
 int SO_FILT_HINT_SUSPEND ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  WNT_RELEASE ; 
 scalar_t__ WNT_STOPUSING ; 
 scalar_t__ in_pcb_checkstate (struct inpcb*,int /*<<< orphan*/ ,int) ; 
 struct inpcb* inp_fc_getinp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  soevent (TYPE_1__*,int) ; 

int
inp_set_fc_state(struct inpcb *inp, int advcode)
{
	struct inpcb *tmp_inp = NULL;
	/*
	 * If there was a feedback from the interface when
	 * send operation was in progress, we should ignore
	 * this flow advisory to avoid a race between setting
	 * flow controlled state and receiving feedback from
	 * the interface
	 */
	if (inp->inp_flags & INP_FC_FEEDBACK)
		return (0);

	inp->inp_flags &= ~(INP_FLOW_CONTROLLED | INP_FLOW_SUSPENDED);
	if ((tmp_inp = inp_fc_getinp(inp->inp_flowhash,
	    INPFC_SOLOCKED)) != NULL) {
		if (in_pcb_checkstate(tmp_inp, WNT_RELEASE, 1) == WNT_STOPUSING)
			return (0);
		VERIFY(tmp_inp == inp);
		switch (advcode) {
		case FADV_FLOW_CONTROLLED:
			inp->inp_flags |= INP_FLOW_CONTROLLED;
			break;
		case FADV_SUSPENDED:
			inp->inp_flags |= INP_FLOW_SUSPENDED;
			soevent(inp->inp_socket,
			    (SO_FILT_HINT_LOCKED | SO_FILT_HINT_SUSPEND));

			/* Record the fact that suspend event was sent */
			inp->inp_socket->so_flags |= SOF_SUSPENDED;
			break;
		}
		return (1);
	}
	return (0);
}