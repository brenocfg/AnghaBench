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
struct net_device {int /*<<< orphan*/  dev; struct ctcm_priv* ml_priv; int /*<<< orphan*/  name; } ;
struct ctcm_priv {int /*<<< orphan*/ * channel; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ctcm_priv*,int,int) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int DEV_EVENT_RXUP ; 
 int DEV_EVENT_TXUP ; 
 int DEV_STATE_RUNNING ; 
#define  DEV_STATE_STARTWAIT_RX 132 
#define  DEV_STATE_STARTWAIT_RXTX 131 
#define  DEV_STATE_STARTWAIT_TX 130 
#define  DEV_STATE_STOPWAIT_RX 129 
 int DEV_STATE_STOPWAIT_RXTX ; 
#define  DEV_STATE_STOPWAIT_TX 128 
 scalar_t__ IS_MPC (struct ctcm_priv*) ; 
 int /*<<< orphan*/  MPC_CHANNEL_ADD ; 
 size_t READ ; 
 int /*<<< orphan*/  SETUP ; 
 size_t WRITE ; 
 int /*<<< orphan*/  ctcm_clear_busy (struct net_device*) ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 
 int fsm_getstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpc_channel_action (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_action_chup(fsm_instance *fi, int event, void *arg)
{
	struct net_device *dev = arg;
	struct ctcm_priv *priv = dev->ml_priv;
	int dev_stat = fsm_getstate(fi);

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_NOTICE,
			"%s(%s): priv = %p [%d,%d]\n ",	CTCM_FUNTAIL,
				dev->name, dev->ml_priv, dev_stat, event);

	switch (fsm_getstate(fi)) {
	case DEV_STATE_STARTWAIT_RXTX:
		if (event == DEV_EVENT_RXUP)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_TX);
		else
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RX);
		break;
	case DEV_STATE_STARTWAIT_RX:
		if (event == DEV_EVENT_RXUP) {
			fsm_newstate(fi, DEV_STATE_RUNNING);
			dev_info(&dev->dev,
				"Connected with remote side\n");
			ctcm_clear_busy(dev);
		}
		break;
	case DEV_STATE_STARTWAIT_TX:
		if (event == DEV_EVENT_TXUP) {
			fsm_newstate(fi, DEV_STATE_RUNNING);
			dev_info(&dev->dev,
				"Connected with remote side\n");
			ctcm_clear_busy(dev);
		}
		break;
	case DEV_STATE_STOPWAIT_TX:
		if (event == DEV_EVENT_RXUP)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RXTX);
		break;
	case DEV_STATE_STOPWAIT_RX:
		if (event == DEV_EVENT_TXUP)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RXTX);
		break;
	}

	if (IS_MPC(priv)) {
		if (event == DEV_EVENT_RXUP)
			mpc_channel_action(priv->channel[READ],
				READ, MPC_CHANNEL_ADD);
		else
			mpc_channel_action(priv->channel[WRITE],
				WRITE, MPC_CHANNEL_ADD);
	}
}