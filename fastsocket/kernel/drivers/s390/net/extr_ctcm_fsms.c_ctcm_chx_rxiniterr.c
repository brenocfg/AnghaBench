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
struct net_device {int /*<<< orphan*/  dev; struct ctcm_priv* ml_priv; } ;
struct ctcm_priv {int /*<<< orphan*/  fsm; } ;
struct channel {int /*<<< orphan*/  id; int /*<<< orphan*/  retry; int /*<<< orphan*/  timer; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_ERROR ; 
 int CTC_EVENT_TIMER ; 
 int /*<<< orphan*/  CTC_STATE_RXERR ; 
 int /*<<< orphan*/  DEV_EVENT_RXDOWN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_MPCDEV (struct net_device*) ; 
 int /*<<< orphan*/ * ctc_ch_event_names ; 
 int /*<<< orphan*/  ctcm_chx_restart (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fsm_getstate_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctcm_chx_rxiniterr(fsm_instance *fi, int event, void *arg)
{
	struct channel *ch = arg;
	struct net_device *dev = ch->netdev;
	struct ctcm_priv *priv = dev->ml_priv;

	if (event == CTC_EVENT_TIMER) {
		if (!IS_MPCDEV(dev))
			/* TODO : check if MPC deletes timer somewhere */
			fsm_deltimer(&ch->timer);
		if (ch->retry++ < 3)
			ctcm_chx_restart(fi, event, arg);
		else {
			fsm_newstate(fi, CTC_STATE_RXERR);
			fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
		}
	} else {
		CTCM_DBF_TEXT_(ERROR, CTC_DBF_ERROR,
			"%s(%s): %s in %s", CTCM_FUNTAIL, ch->id,
			ctc_ch_event_names[event], fsm_getstate_str(fi));

		dev_warn(&dev->dev,
			"Initialization failed with RX/TX init handshake "
			"error %s\n", ctc_ch_event_names[event]);
	}
}