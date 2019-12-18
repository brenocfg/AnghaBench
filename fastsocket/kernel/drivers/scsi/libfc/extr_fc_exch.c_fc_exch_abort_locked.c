#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct fc_seq {int dummy; } ;
struct fc_frame {int dummy; } ;
struct fc_exch {int esb_stat; int state; int /*<<< orphan*/  lp; int /*<<< orphan*/  sid; int /*<<< orphan*/  did; int /*<<< orphan*/  seq; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int ENXIO ; 
 int ESB_ST_ABNORMAL ; 
 int ESB_ST_COMPLETE ; 
 int ESB_ST_SEQ_INIT ; 
 int FC_EX_DONE ; 
 int FC_EX_RST_CLEANUP ; 
 int FC_FC_END_SEQ ; 
 int FC_FC_SEQ_INIT ; 
 int /*<<< orphan*/  FC_RCTL_BA_ABTS ; 
 int /*<<< orphan*/  FC_TYPE_BLS ; 
 int /*<<< orphan*/  fc_exch_timer_set_locked (struct fc_exch*,unsigned int) ; 
 int /*<<< orphan*/  fc_fill_fc_hdr (struct fc_frame*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct fc_frame* fc_frame_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int fc_seq_send_locked (int /*<<< orphan*/ ,struct fc_seq*,struct fc_frame*) ; 
 struct fc_seq* fc_seq_start_next_locked (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fc_exch_abort_locked(struct fc_exch *ep,
				unsigned int timer_msec)
{
	struct fc_seq *sp;
	struct fc_frame *fp;
	int error;

	if (ep->esb_stat & (ESB_ST_COMPLETE | ESB_ST_ABNORMAL) ||
	    ep->state & (FC_EX_DONE | FC_EX_RST_CLEANUP))
		return -ENXIO;

	/*
	 * Send the abort on a new sequence if possible.
	 */
	sp = fc_seq_start_next_locked(&ep->seq);
	if (!sp)
		return -ENOMEM;

	ep->esb_stat |= ESB_ST_SEQ_INIT | ESB_ST_ABNORMAL;
	if (timer_msec)
		fc_exch_timer_set_locked(ep, timer_msec);

	/*
	 * If not logged into the fabric, don't send ABTS but leave
	 * sequence active until next timeout.
	 */
	if (!ep->sid)
		return 0;

	/*
	 * Send an abort for the sequence that timed out.
	 */
	fp = fc_frame_alloc(ep->lp, 0);
	if (fp) {
		fc_fill_fc_hdr(fp, FC_RCTL_BA_ABTS, ep->did, ep->sid,
			       FC_TYPE_BLS, FC_FC_END_SEQ | FC_FC_SEQ_INIT, 0);
		error = fc_seq_send_locked(ep->lp, sp, fp);
	} else
		error = -ENOBUFS;
	return error;
}