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
struct mpcg_info {struct channel* ch; } ;
struct mpc_group {int send_qllc_disc; int /*<<< orphan*/  fsm; } ;
struct ctcm_priv {struct mpc_group* mpcg; } ;
struct channel {int /*<<< orphan*/  id; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int /*<<< orphan*/  MPCG_EVENT_INOP ; 
 int /*<<< orphan*/  MPC_TRACE ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 

void mpc_action_discontact(fsm_instance *fi, int event, void *arg)
{
	struct mpcg_info   *mpcginfo   = arg;
	struct channel	   *ch	       = mpcginfo->ch;
	struct net_device  *dev;
	struct ctcm_priv   *priv;
	struct mpc_group   *grp;

	if (ch) {
		dev = ch->netdev;
		if (dev) {
			priv = dev->ml_priv;
			if (priv) {
				CTCM_DBF_TEXT_(MPC_TRACE, CTC_DBF_NOTICE,
					"%s: %s: %s\n",
					CTCM_FUNTAIL, dev->name, ch->id);
				grp = priv->mpcg;
				grp->send_qllc_disc = 1;
				fsm_event(grp->fsm, MPCG_EVENT_INOP, dev);
			}
		}
	}

	return;
}