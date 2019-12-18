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
struct wimax_dev {int state; int /*<<< orphan*/  net_dev; } ;
struct sk_buff {int dummy; } ;
struct device {int dummy; } ;
typedef  enum wimax_st { ____Placeholder_wimax_st } wimax_st ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ WARN_ON (int) ; 
#define  WIMAX_ST_CONNECTED 137 
#define  WIMAX_ST_CONNECTING 136 
#define  WIMAX_ST_DOWN 135 
#define  WIMAX_ST_RADIO_OFF 134 
#define  WIMAX_ST_READY 133 
#define  WIMAX_ST_SCANNING 132 
#define  WIMAX_ST_UNINITIALIZED 131 
#define  __WIMAX_ST_INVALID 130 
#define  __WIMAX_ST_NULL 129 
#define  __WIMAX_ST_QUIESCING 128 
 int /*<<< orphan*/  __check_new_state (int,int,int) ; 
 int /*<<< orphan*/  __wimax_state_set (struct wimax_dev*,int) ; 
 int /*<<< orphan*/  d_fnend (int,struct device*,char*,struct wimax_dev*,int,int) ; 
 int /*<<< orphan*/  d_fnstart (int,struct device*,char*,struct wimax_dev*,int,int) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_tx_disable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_wake_queue (int /*<<< orphan*/ ) ; 
 struct device* wimax_dev_to_dev (struct wimax_dev*) ; 
 struct sk_buff* wimax_gnl_re_state_change_alloc (struct wimax_dev*,int,int,void**) ; 
 int /*<<< orphan*/  wimax_gnl_re_state_change_send (struct wimax_dev*,struct sk_buff*,void*) ; 

void __wimax_state_change(struct wimax_dev *wimax_dev, enum wimax_st new_state)
{
	struct device *dev = wimax_dev_to_dev(wimax_dev);
	enum wimax_st old_state = wimax_dev->state;
	struct sk_buff *stch_skb;
	void *header;

	d_fnstart(3, dev, "(wimax_dev %p new_state %u [old %u])\n",
		  wimax_dev, new_state, old_state);

	if (WARN_ON(new_state >= __WIMAX_ST_INVALID)) {
		dev_err(dev, "SW BUG: requesting invalid state %u\n",
			new_state);
		goto out;
	}
	if (old_state == new_state)
		goto out;
	header = NULL;	/* gcc complains? can't grok why */
	stch_skb = wimax_gnl_re_state_change_alloc(
		wimax_dev, new_state, old_state, &header);

	/* Verify the state transition and do exit-from-state actions */
	switch (old_state) {
	case __WIMAX_ST_NULL:
		__check_new_state(old_state, new_state,
				  1 << WIMAX_ST_DOWN);
		break;
	case WIMAX_ST_DOWN:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_UNINITIALIZED
				  | 1 << WIMAX_ST_RADIO_OFF);
		break;
	case __WIMAX_ST_QUIESCING:
		__check_new_state(old_state, new_state, 1 << WIMAX_ST_DOWN);
		break;
	case WIMAX_ST_UNINITIALIZED:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_RADIO_OFF);
		break;
	case WIMAX_ST_RADIO_OFF:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_READY);
		break;
	case WIMAX_ST_READY:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_RADIO_OFF
				  | 1 << WIMAX_ST_SCANNING
				  | 1 << WIMAX_ST_CONNECTING
				  | 1 << WIMAX_ST_CONNECTED);
		break;
	case WIMAX_ST_SCANNING:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_RADIO_OFF
				  | 1 << WIMAX_ST_READY
				  | 1 << WIMAX_ST_CONNECTING
				  | 1 << WIMAX_ST_CONNECTED);
		break;
	case WIMAX_ST_CONNECTING:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_RADIO_OFF
				  | 1 << WIMAX_ST_READY
				  | 1 << WIMAX_ST_SCANNING
				  | 1 << WIMAX_ST_CONNECTED);
		break;
	case WIMAX_ST_CONNECTED:
		__check_new_state(old_state, new_state,
				  1 << __WIMAX_ST_QUIESCING
				  | 1 << WIMAX_ST_RADIO_OFF
				  | 1 << WIMAX_ST_READY);
		netif_tx_disable(wimax_dev->net_dev);
		netif_carrier_off(wimax_dev->net_dev);
		break;
	case __WIMAX_ST_INVALID:
	default:
		dev_err(dev, "SW BUG: wimax_dev %p is in unknown state %u\n",
			wimax_dev, wimax_dev->state);
		WARN_ON(1);
		goto out;
	}

	/* Execute the actions of entry to the new state */
	switch (new_state) {
	case __WIMAX_ST_NULL:
		dev_err(dev, "SW BUG: wimax_dev %p entering NULL state "
			"from %u\n", wimax_dev, wimax_dev->state);
		WARN_ON(1);		/* Nobody can enter this state */
		break;
	case WIMAX_ST_DOWN:
		break;
	case __WIMAX_ST_QUIESCING:
		break;
	case WIMAX_ST_UNINITIALIZED:
		break;
	case WIMAX_ST_RADIO_OFF:
		break;
	case WIMAX_ST_READY:
		break;
	case WIMAX_ST_SCANNING:
		break;
	case WIMAX_ST_CONNECTING:
		break;
	case WIMAX_ST_CONNECTED:
		netif_carrier_on(wimax_dev->net_dev);
		netif_wake_queue(wimax_dev->net_dev);
		break;
	case __WIMAX_ST_INVALID:
	default:
		BUG();
	}
	__wimax_state_set(wimax_dev, new_state);
	if (stch_skb)
		wimax_gnl_re_state_change_send(wimax_dev, stch_skb, header);
out:
	d_fnend(3, dev, "(wimax_dev %p new_state %u [old %u]) = void\n",
		wimax_dev, new_state, old_state);
	return;
}