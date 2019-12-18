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
struct ctcm_priv {struct channel** channel; int /*<<< orphan*/  fsm; } ;
struct channel {int /*<<< orphan*/  cdev; int /*<<< orphan*/ * fsm; int /*<<< orphan*/  timer; struct net_device* netdev; } ;
typedef  int /*<<< orphan*/  fsm_instance ;

/* Variables and functions */
 int /*<<< orphan*/  CTCM_DBF_TEXT_ (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CTCM_FUNTAIL ; 
 int /*<<< orphan*/  CTC_DBF_NOTICE ; 
 int /*<<< orphan*/  CTC_STATE_DTERM ; 
 int /*<<< orphan*/  DEV_EVENT_RXDOWN ; 
 int /*<<< orphan*/  DEV_EVENT_TXDOWN ; 
 int /*<<< orphan*/  TRACE ; 
 size_t WRITE ; 
 int /*<<< orphan*/  ccw_device_halt (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  fsm_deltimer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsm_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct net_device*) ; 
 int /*<<< orphan*/  fsm_newstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ctcm_chx_rxdisc(fsm_instance *fi, int event, void *arg)
{
	struct channel *ch = arg;
	struct channel *ch2;
	struct net_device *dev = ch->netdev;
	struct ctcm_priv *priv = dev->ml_priv;

	CTCM_DBF_TEXT_(TRACE, CTC_DBF_NOTICE,
			"%s: %s: remote disconnect - re-init ...",
				CTCM_FUNTAIL, dev->name);
	fsm_deltimer(&ch->timer);
	/*
	 * Notify device statemachine
	 */
	fsm_event(priv->fsm, DEV_EVENT_RXDOWN, dev);
	fsm_event(priv->fsm, DEV_EVENT_TXDOWN, dev);

	fsm_newstate(fi, CTC_STATE_DTERM);
	ch2 = priv->channel[WRITE];
	fsm_newstate(ch2->fsm, CTC_STATE_DTERM);

	ccw_device_halt(ch->cdev, (unsigned long)ch);
	ccw_device_halt(ch2->cdev, (unsigned long)ch2);
}