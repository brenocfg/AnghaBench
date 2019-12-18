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
struct channel {int th_seg; int th_seq_num; int /*<<< orphan*/  collect_lock; scalar_t__ collect_len; int /*<<< orphan*/  collect_queue; int /*<<< orphan*/  sweep_queue; int /*<<< orphan*/  io_queue; int /*<<< orphan*/  flags; int /*<<< orphan*/ * trans_skb; int /*<<< orphan*/ * ccw; int /*<<< orphan*/  sweep_timer; int /*<<< orphan*/  timer; int /*<<< orphan*/  id; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 scalar_t__ CHANNEL_DIRECTION (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int CTC_STATE_STOPPED ; 
 int /*<<< orphan*/  DEV_EVENT_RXDOWN ; 
 int /*<<< orphan*/  DEV_EVENT_TXDOWN ; 
 scalar_t__ IS_MPC (struct channel*) ; 
 scalar_t__ READ ; 
 int /*<<< orphan*/  SETUP ; 
 int /*<<< orphan*/  clear_normalized_cda (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ctcm_purge_skb_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_kfree_skb_any (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  skb_queue_purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ctcm_chx_cleanup(fsm_instance *fi, int state,
		struct channel *ch)
{
	struct net_device *dev = ch->netdev;
	struct ctcm_priv *priv = dev->ml_priv;

	CTCM_DBF_TEXT_(SETUP, CTC_DBF_NOTICE,
			"%s(%s): %s[%d]\n",
			CTCM_FUNTAIL, dev->name, ch->id, state);

	fsm_deltimer(&ch->timer);
	if (IS_MPC(ch))
		fsm_deltimer(&ch->sweep_timer);

	fsm_newstate(fi, state);
	if (state == CTC_STATE_STOPPED && ch->trans_skb != NULL) {
		clear_normalized_cda(&ch->ccw[1]);
		dev_kfree_skb_any(ch->trans_skb);
		ch->trans_skb = NULL;
	}

	ch->th_seg = 0x00;
	ch->th_seq_num = 0x00;
	if (CHANNEL_DIRECTION(ch->flags) == READ) {
		skb_queue_purge(&ch->io_queue);
		fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	} else {
		ctcm_purge_skb_queue(&ch->io_queue);
		if (IS_MPC(ch))
			ctcm_purge_skb_queue(&ch->sweep_queue);
		spin_lock(&ch->collect_lock);
		ctcm_purge_skb_queue(&ch->collect_queue);
		ch->collect_len = 0;
		spin_unlock(&ch->collect_lock);
		fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);
	}
}