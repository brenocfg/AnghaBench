#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {scalar_t__ cnt; int /*<<< orphan*/  size; } ;
struct TYPE_5__ {struct eventqelt* tqh_first; } ;
struct pipe {int pipe_state; TYPE_3__ pipe_buffer; TYPE_1__ pipe_evlist; } ;
struct TYPE_8__ {int er_eventbits; scalar_t__ er_wcnt; scalar_t__ er_rcnt; } ;
struct TYPE_6__ {struct eventqelt* tqe_next; } ;
struct eventqelt {scalar_t__ ee_eventmask; TYPE_4__ ee_req; TYPE_2__ ee_slist; } ;

/* Variables and functions */
 int DBG_FUNC_END ; 
 int DBG_FUNC_START ; 
 int DBG_MISC_POST ; 
#define  EV_RCLOSED 130 
 int EV_RE ; 
 int EV_RESET ; 
#define  EV_RWBYTES 129 
#define  EV_WCLOSED 128 
 int EV_WR ; 
 int /*<<< orphan*/  KERNEL_DEBUG (int,int,int,int,int,int /*<<< orphan*/ ) ; 
 scalar_t__ MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ PIPE_BUF ; 
 int PIPE_EOF ; 
 int /*<<< orphan*/  PIPE_SIZE ; 
 int /*<<< orphan*/  evprocenque (struct eventqelt*) ; 

void
postpipeevent(struct pipe *pipep, int event)
{
	int	mask;
	struct eventqelt *evq;

	if (pipep == NULL)
	        return;
	KERNEL_DEBUG(DBG_MISC_POST|DBG_FUNC_START, event,0,0,1,0);

	for (evq = pipep->pipe_evlist.tqh_first;
	     evq != NULL; evq = evq->ee_slist.tqe_next) {

	        if (evq->ee_eventmask == 0)
		        continue;
	        mask = 0;

		switch (event & (EV_RWBYTES | EV_RCLOSED | EV_WCLOSED)) {

		case EV_RWBYTES:
		  if ((evq->ee_eventmask & EV_RE) && pipep->pipe_buffer.cnt) {
		          mask |= EV_RE;
			  evq->ee_req.er_rcnt = pipep->pipe_buffer.cnt;
		  }
		  if ((evq->ee_eventmask & EV_WR) && 
		      (MAX(pipep->pipe_buffer.size,PIPE_SIZE) - pipep->pipe_buffer.cnt) >= PIPE_BUF) {

		          if (pipep->pipe_state & PIPE_EOF) {
			          mask |= EV_WR|EV_RESET;
				  break;
			  }
			  mask |= EV_WR;
			  evq->ee_req.er_wcnt = MAX(pipep->pipe_buffer.size, PIPE_SIZE) - pipep->pipe_buffer.cnt;
		  }
		  break;

		case EV_WCLOSED:
		case EV_RCLOSED:
		  if ((evq->ee_eventmask & EV_RE)) {
		          mask |= EV_RE|EV_RCLOSED;
		  }
		  if ((evq->ee_eventmask & EV_WR)) {
		          mask |= EV_WR|EV_WCLOSED;
		  }
		  break;

		default:
		  return;
		}
		if (mask) {
		        /*
			 * disarm... postevents are nops until this event is 'read' via
			 * waitevent and then re-armed via modwatch
			 */
		        evq->ee_eventmask = 0;

			/*
			 * since events are disarmed until after the waitevent
			 * the ee_req.er_xxxx fields can't change once we've
			 * inserted this event into the proc queue...
			 * therefore, the waitevent will see a 'consistent'
			 * snapshot of the event, even though it won't hold
			 * the pipe lock, and we're updating the event outside
			 * of the proc lock, which it will hold
			 */
		        evq->ee_req.er_eventbits |= mask;

			KERNEL_DEBUG(DBG_MISC_POST, (uint32_t)evq, evq->ee_req.er_eventbits, mask, 1,0);

			evprocenque(evq);
		}
	}
	KERNEL_DEBUG(DBG_MISC_POST|DBG_FUNC_END, 0,0,0,1,0);
}