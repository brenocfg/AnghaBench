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
struct net_device {int /*<<< orphan*/  name; struct ctcm_priv* ml_priv; } ;
struct mpc_group {int flow_off_called; int /*<<< orphan*/  fsm; } ;
struct ctcm_priv {struct channel** channel; struct mpc_group* mpcg; } ;
struct channel {int /*<<< orphan*/  ch_tasklet; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_DEBUG ; 
 int MPCG_STATE_FLOWC ; 
 int MPCG_STATE_READY ; 
 int /*<<< orphan*/  MPC_TRACE ; 
 size_t READ ; 
 struct net_device* ctcmpc_get_dev (int) ; 
 int fsm_getstate (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  tasklet_schedule (int /*<<< orphan*/ *) ; 

void ctc_mpc_flow_control(int port_num, int flowc)
{
	struct ctcm_priv *priv;
	struct mpc_group *grp;
	struct net_device *dev;
	struct channel *rch;
	int mpcg_state;

	dev = ctcmpc_get_dev(port_num);
	if (dev == NULL)
		return;
	priv = dev->ml_priv;
	grp = priv->mpcg;

	CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_DEBUG,
			"%s: %s: flowc = %d",
				CTCM_FUNTAIL, dev->name, flowc);

	rch = priv->channel[READ];

	mpcg_state = fsm_getstate(grp->fsm);
	switch (flowc) {
	case 1:
		if (mpcg_state == MPCG_STATE_FLOWC)
			break;
		if (mpcg_state == MPCG_STATE_READY) {
			if (grp->flow_off_called == 1)
				grp->flow_off_called = 0;
			else
				fsm_newstate(grp->fsm, MPCG_STATE_FLOWC);
			break;
		}
		break;
	case 0:
		if (mpcg_state == MPCG_STATE_FLOWC) {
			fsm_newstate(grp->fsm, MPCG_STATE_READY);
			/* ensure any data that has accumulated */
			/* on the io_queue will now be sen t	*/
			tasklet_schedule(&rch->ch_tasklet);
		}
		/* possible race condition			*/
		if (mpcg_state == MPCG_STATE_READY) {
			grp->flow_off_called = 1;
			break;
		}
		break;
	}

}