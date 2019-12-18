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
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {struct channel** channel; TYPE_1__* mpcg; int /*<<< orphan*/  restart_timer; } ;
struct channel {int /*<<< orphan*/  fsm; } ;
typedef  int /*<<< orphan*/  fsm_instance ;
struct TYPE_2__ {scalar_t__ channels_terminating; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTCMY_DBF_DEV_NAME (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int /*<<< orphan*/  CTC_EVENT_START ; 
 int /*<<< orphan*/  DEV_STATE_STARTWAIT_RXTX ; 
 scalar_t__ IS_MPC (struct ctcm_priv*) ; 
 int READ ; 
 int /*<<< orphan*/  SETUP ; 
 int WRITE ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_action_start(fsm_instance *fi, int event, void *arg)
{
	struct net_device *dev = arg;
	struct ctcm_priv *priv = dev->ml_priv;
	int direction;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");

	fsm_deltimer(&priv->restart_timer);
	fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
	if (IS_MPC(priv))
		priv->mpcg->channels_terminating = 0;
	for (direction = READ; direction <= WRITE; direction++) {
		struct channel *ch = priv->channel[direction];
		fsm_event(ch->fsm, CTC_EVENT_START, ch);
	}
}