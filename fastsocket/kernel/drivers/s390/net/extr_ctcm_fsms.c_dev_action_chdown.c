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
struct net_device {struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/ * channel; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCMY_DBF_DEV_NAME (int /*<<< orphan*/ ,struct net_device*,char*) ; 
 int DEV_EVENT_RXDOWN ; 
 int DEV_EVENT_TXDOWN ; 
#define  DEV_STATE_RUNNING 133 
#define  DEV_STATE_STARTWAIT_RX 132 
 int DEV_STATE_STARTWAIT_RXTX ; 
#define  DEV_STATE_STARTWAIT_TX 131 
 int DEV_STATE_STOPPED ; 
#define  DEV_STATE_STOPWAIT_RX 130 
#define  DEV_STATE_STOPWAIT_RXTX 129 
#define  DEV_STATE_STOPWAIT_TX 128 
 scalar_t__ IS_MPC (struct ctcm_priv*) ; 
 int /*<<< orphan*/  MPC_CHANNEL_REMOVE ; 
 size_t READ ; 
 int /*<<< orphan*/  SETUP ; 
 size_t WRITE ; 
 int fsm_getstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mpc_channel_action (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void dev_action_chdown(fsm_instance *fi, int event, void *arg)
{

	struct net_device *dev = arg;
	struct ctcm_priv *priv = dev->ml_priv;

	CTCMY_DBF_DEV_NAME(SETUP, dev, "");

	switch (fsm_getstate(fi)) {
	case DEV_STATE_RUNNING:
		if (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_TX);
		else
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RX);
		break;
	case DEV_STATE_STARTWAIT_RX:
		if (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
		break;
	case DEV_STATE_STARTWAIT_TX:
		if (event == DEV_EVENT_RXDOWN)
			fsm_newstate(fi, DEV_STATE_STARTWAIT_RXTX);
		break;
	case DEV_STATE_STOPWAIT_RXTX:
		if (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPWAIT_RX);
		else
			fsm_newstate(fi, DEV_STATE_STOPWAIT_TX);
		break;
	case DEV_STATE_STOPWAIT_RX:
		if (event == DEV_EVENT_RXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPPED);
		break;
	case DEV_STATE_STOPWAIT_TX:
		if (event == DEV_EVENT_TXDOWN)
			fsm_newstate(fi, DEV_STATE_STOPPED);
		break;
	}
	if (IS_MPC(priv)) {
		if (event == DEV_EVENT_RXDOWN)
			mpc_channel_action(priv->channel[READ],
				READ, MPC_CHANNEL_REMOVE);
		else
			mpc_channel_action(priv->channel[WRITE],
				WRITE, MPC_CHANNEL_REMOVE);
	}
}