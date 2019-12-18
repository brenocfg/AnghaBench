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
typedef  scalar_t__ u_long ;
struct net_device {int dummy; } ;
struct atmel_private {int station_state; int CurrentAuthentTransactionSeqNum; int /*<<< orphan*/  irqlock; int /*<<< orphan*/  management_timer; int /*<<< orphan*/  ReAssociationRequestRetryCnt; int /*<<< orphan*/  station_is_associated; int /*<<< orphan*/  AssociationRequestRetryCnt; int /*<<< orphan*/  exclude_unencrypted; int /*<<< orphan*/  wep_is_on; int /*<<< orphan*/  AuthenticationRequestRetryCnt; scalar_t__ card; int /*<<< orphan*/  (* present_callback ) (scalar_t__) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  MAX_ASSOCIATION_RETRIES ; 
 int /*<<< orphan*/  MAX_AUTHENTICATION_RETRIES ; 
 scalar_t__ MGMT_JIFFIES ; 
#define  STATION_STATE_ASSOCIATING 130 
#define  STATION_STATE_AUTHENTICATING 129 
 int /*<<< orphan*/  STATION_STATE_MGMT_ERROR ; 
#define  STATION_STATE_REASSOCIATING 128 
 int WLAN_AUTH_OPEN ; 
 int WLAN_AUTH_SHARED_KEY ; 
 int /*<<< orphan*/  atmel_enter_state (struct atmel_private*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct atmel_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  restart_search (struct atmel_private*) ; 
 int /*<<< orphan*/  send_association_request (struct atmel_private*,int) ; 
 int /*<<< orphan*/  send_authentication_request (struct atmel_private*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

__attribute__((used)) static void atmel_management_timer(u_long a)
{
	struct net_device *dev = (struct net_device *) a;
	struct atmel_private *priv = netdev_priv(dev);
	unsigned long flags;

	/* Check if the card has been yanked. */
	if (priv->card && priv->present_callback &&
		!(*priv->present_callback)(priv->card))
		return;

	spin_lock_irqsave(&priv->irqlock, flags);

	switch (priv->station_state) {

	case STATION_STATE_AUTHENTICATING:
		if (priv->AuthenticationRequestRetryCnt >= MAX_AUTHENTICATION_RETRIES) {
			atmel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->AuthenticationRequestRetryCnt = 0;
			restart_search(priv);
		} else {
			int auth = WLAN_AUTH_OPEN;
			priv->AuthenticationRequestRetryCnt++;
			priv->CurrentAuthentTransactionSeqNum = 0x0001;
			mod_timer(&priv->management_timer, jiffies + MGMT_JIFFIES);
			if (priv->wep_is_on && priv->exclude_unencrypted)
				auth = WLAN_AUTH_SHARED_KEY;
			send_authentication_request(priv, auth, NULL, 0);
	  }
	  break;

	case STATION_STATE_ASSOCIATING:
		if (priv->AssociationRequestRetryCnt == MAX_ASSOCIATION_RETRIES) {
			atmel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->AssociationRequestRetryCnt = 0;
			restart_search(priv);
		} else {
			priv->AssociationRequestRetryCnt++;
			mod_timer(&priv->management_timer, jiffies + MGMT_JIFFIES);
			send_association_request(priv, 0);
		}
	  break;

	case STATION_STATE_REASSOCIATING:
		if (priv->ReAssociationRequestRetryCnt == MAX_ASSOCIATION_RETRIES) {
			atmel_enter_state(priv, STATION_STATE_MGMT_ERROR);
			priv->station_is_associated = 0;
			priv->ReAssociationRequestRetryCnt = 0;
			restart_search(priv);
		} else {
			priv->ReAssociationRequestRetryCnt++;
			mod_timer(&priv->management_timer, jiffies + MGMT_JIFFIES);
			send_association_request(priv, 1);
		}
		break;

	default:
		break;
	}

	spin_unlock_irqrestore(&priv->irqlock, flags);
}