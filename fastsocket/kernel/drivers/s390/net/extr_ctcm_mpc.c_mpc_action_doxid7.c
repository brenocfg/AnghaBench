#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xid2 {int /*<<< orphan*/  xid2_option; } ;
struct net_device {struct ctcm_priv* ml_priv; } ;
struct mpc_group {scalar_t__ outstanding_xid7_p2; scalar_t__ roll; int /*<<< orphan*/  fsm; } ;
struct ctcm_priv {struct channel** channel; struct mpc_group* mpcg; } ;
struct channel {TYPE_2__* xid_skb; TYPE_1__* ccw; int /*<<< orphan*/  fsm; int /*<<< orphan*/  xid_skb_data; struct xid2* xid; } ;
typedef  int /*<<< orphan*/  fsm_instance ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_4__ {void* cmd_code; } ;

/* Variables and functions */
 void* CCW_CMD_SENSE_CMD ; 
 void* CCW_CMD_WRITE_CTL ; 
 scalar_t__ CH_XID7_PENDING1 ; 
 scalar_t__ CH_XID7_PENDING2 ; 
 scalar_t__ CH_XID7_PENDING3 ; 
 scalar_t__ CH_XID7_PENDING4 ; 
 int /*<<< orphan*/  MPCG_EVENT_DOIO ; 
 int READ ; 
 int /*<<< orphan*/  TH_HEADER_LENGTH ; 
 int WRITE ; 
 int /*<<< orphan*/  XID2_7 ; 
 scalar_t__ YSIDE ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 scalar_t__ fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_put (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  skb_reset_tail_pointer (TYPE_2__*) ; 
 int /*<<< orphan*/  thdummy ; 
 int /*<<< orphan*/  thnorm ; 

__attribute__((used)) static void mpc_action_doxid7(fsm_instance *fsm, int event, void *arg)
{
	struct net_device *dev = arg;
	struct ctcm_priv  *priv = dev->ml_priv;
	struct mpc_group  *grp  = NULL;
	int direction;
	int send = 0;

	if (priv)
		grp = priv->mpcg;
	if (grp == NULL)
		return;

	for (direction = READ; direction <= WRITE; direction++)	{
		struct channel *ch = priv->channel[direction];
		struct xid2 *thisxid = ch->xid;
		ch->xid_skb->data = ch->xid_skb_data;
		skb_reset_tail_pointer(ch->xid_skb);
		ch->xid_skb->len = 0;
		thisxid->xid2_option = XID2_7;
		send = 0;

		/* xid7 phase 1 */
		if (grp->outstanding_xid7_p2 > 0) {
			if (grp->roll == YSIDE) {
				if (fsm_getstate(ch->fsm) == CH_XID7_PENDING1) {
					fsm_newstate(ch->fsm, CH_XID7_PENDING2);
					ch->ccw[8].cmd_code = CCW_CMD_SENSE_CMD;
					memcpy(skb_put(ch->xid_skb,
							TH_HEADER_LENGTH),
					       &thdummy, TH_HEADER_LENGTH);
					send = 1;
				}
			} else if (fsm_getstate(ch->fsm) < CH_XID7_PENDING2) {
					fsm_newstate(ch->fsm, CH_XID7_PENDING2);
					ch->ccw[8].cmd_code = CCW_CMD_WRITE_CTL;
					memcpy(skb_put(ch->xid_skb,
						       TH_HEADER_LENGTH),
					       &thnorm, TH_HEADER_LENGTH);
					send = 1;
			}
		} else {
			/* xid7 phase 2 */
			if (grp->roll == YSIDE) {
				if (fsm_getstate(ch->fsm) < CH_XID7_PENDING4) {
					fsm_newstate(ch->fsm, CH_XID7_PENDING4);
					memcpy(skb_put(ch->xid_skb,
						       TH_HEADER_LENGTH),
					       &thnorm, TH_HEADER_LENGTH);
					ch->ccw[8].cmd_code = CCW_CMD_WRITE_CTL;
					send = 1;
				}
			} else if (fsm_getstate(ch->fsm) == CH_XID7_PENDING3) {
				fsm_newstate(ch->fsm, CH_XID7_PENDING4);
				ch->ccw[8].cmd_code = CCW_CMD_SENSE_CMD;
				memcpy(skb_put(ch->xid_skb, TH_HEADER_LENGTH),
						&thdummy, TH_HEADER_LENGTH);
				send = 1;
			}
		}

		if (send)
			fsm_event(grp->fsm, MPCG_EVENT_DOIO, ch);
	}

	return;
}