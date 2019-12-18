#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u16 ;
struct net_device {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/  bits; TYPE_1__* func; struct net_device* dev; } ;
typedef  TYPE_2__ local_info_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* card_present ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int HFA384X_BAP0_EVENTS ; 
 int /*<<< orphan*/  HFA384X_EVSTAT_OFF ; 
 int HFA384X_EV_INFO ; 
 int HFA384X_EV_RX ; 
 int HFA384X_EV_TX ; 
 int HFA384X_EV_TXEXC ; 
 int HFA384X_INW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  HOSTAP_BITS_BAP_TASKLET ; 
 int /*<<< orphan*/  HOSTAP_BITS_BAP_TASKLET2 ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hfa384x_events_all (struct net_device*) ; 
 int /*<<< orphan*/  prism2_info (TYPE_2__*) ; 
 int /*<<< orphan*/  prism2_rx (TYPE_2__*) ; 
 int /*<<< orphan*/  prism2_tx_ev (TYPE_2__*) ; 
 int /*<<< orphan*/  prism2_txexc (TYPE_2__*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void hostap_bap_tasklet(unsigned long data)
{
	local_info_t *local = (local_info_t *) data;
	struct net_device *dev = local->dev;
	u16 ev;
	int frames = 30;

	if (local->func->card_present && !local->func->card_present(local))
		return;

	set_bit(HOSTAP_BITS_BAP_TASKLET, &local->bits);

	/* Process all pending BAP events without generating new interrupts
	 * for them */
	while (frames-- > 0) {
		ev = HFA384X_INW(HFA384X_EVSTAT_OFF);
		if (ev == 0xffff || !(ev & HFA384X_BAP0_EVENTS))
			break;
		if (ev & HFA384X_EV_RX)
			prism2_rx(local);
		if (ev & HFA384X_EV_INFO)
			prism2_info(local);
		if (ev & HFA384X_EV_TX)
			prism2_tx_ev(local);
		if (ev & HFA384X_EV_TXEXC)
			prism2_txexc(local);
	}

	set_bit(HOSTAP_BITS_BAP_TASKLET2, &local->bits);
	clear_bit(HOSTAP_BITS_BAP_TASKLET, &local->bits);

	/* Enable interrupts for new BAP events */
	hfa384x_events_all(dev);
	clear_bit(HOSTAP_BITS_BAP_TASKLET2, &local->bits);
}