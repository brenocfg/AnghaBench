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
struct ctcm_priv {int /*<<< orphan*/  fsm; } ;
struct channel {int /*<<< orphan*/  flags; int /*<<< orphan*/  cdev; int /*<<< orphan*/  timer; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIRECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTCM_TIME_5_SEC ; 
 int /*<<< orphan*/  CTC_DBF_CRIT ; 
 int /*<<< orphan*/  CTC_EVENT_TIMER ; 
 int CTC_EVENT_UC_RCRESET ; 
 int CTC_EVENT_UC_RSRESET ; 
 int /*<<< orphan*/  CTC_STATE_RXERR ; 
 scalar_t__ CTC_STATE_SETUPWAIT ; 
 int /*<<< orphan*/  CTC_STATE_STARTRETRY ; 
 int /*<<< orphan*/  CTC_STATE_TXERR ; 
 int /*<<< orphan*/  DEV_EVENT_RXDOWN ; 
 int /*<<< orphan*/  DEV_EVENT_TXDOWN ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  IS_MPC (struct channel*) ; 
 scalar_t__ READ ; 
 int ccw_device_halt (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/ * ctc_ch_event_names ; 
 int /*<<< orphan*/  ctcm_ccw_check_rc (struct channel*,int,char*) ; 
 int /*<<< orphan*/  fsm_addtimer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct channel*) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 scalar_t__ fsm_getstate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_getstate_str (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctcm_chx_setuperr(fsm_instance *fi, int event, void *arg)
{
	struct channel *ch = arg;
	struct net_device *dev = ch->netdev;
	struct ctcm_priv *priv = dev->ml_priv;

	/*
	 * Special case: Got UC_RCRESET on setmode.
	 * This means that remote side isn't setup. In this case
	 * simply retry after some 10 secs...
	 */
	if ((fsm_getstate(fi) == CTC_STATE_SETUPWAIT) &&
	    ((event == CTC_EVENT_UC_RCRESET) ||
	     (event == CTC_EVENT_UC_RSRESET))) {
		fsm_newstate(fi, CTC_STATE_STARTRETRY);
		fsm_deltimer(&ch->timer);
		fsm_addtimer(&ch->timer, CTCM_TIME_5_SEC, CTC_EVENT_TIMER, ch);
		if (!IS_MPC(ch) && (CHANNEL_DIRECTION(ch->flags) == READ)) {
			int rc = ccw_device_halt(ch->cdev, (unsigned long)ch);
			if (rc != 0)
				ctcm_ccw_check_rc(ch, rc,
					"HaltIO in chx_setuperr");
		}
		return;
	}

	CTCM_DBF_TEXT_(ERROR, CTC_DBF_CRIT,
		"%s(%s) : %s error during %s channel setup state=%s\n",
		CTCM_FUNTAIL, dev->name, ctc_ch_event_names[event],
		(CHANNEL_DIRECTION(ch->flags) == READ) ? "RX" : "TX",
		fsm_getstate_str(fi));

	if (CHANNEL_DIRECTION(ch->flags) == READ) {
		fsm_newstate(fi, CTC_STATE_RXERR);
		fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	} else {
		fsm_newstate(fi, CTC_STATE_TXERR);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
	}
}