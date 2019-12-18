#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct r8180_priv {int txbuffsize; TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct ieee80211_header_data {int dummy; } ;
struct TYPE_4__ {scalar_t__ QoS_Enable; } ;
struct ieee80211_device {TYPE_2__ current_network; } ;
struct TYPE_3__ {int fts; } ;

/* Variables and functions */
 int get_curr_tx_free_desc (struct net_device*,int) ; 
 struct r8180_priv* ieee80211_priv (struct net_device*) ; 
 struct ieee80211_device* netdev_priv (struct net_device*) ; 

short check_nic_enought_desc(struct net_device *dev, int priority)
{
	struct r8180_priv *priv = ieee80211_priv(dev);
	struct ieee80211_device *ieee = netdev_priv(dev);
	int requiredbyte, required;

	requiredbyte = priv->ieee80211->fts + sizeof(struct ieee80211_header_data);

	if (ieee->current_network.QoS_Enable)
		requiredbyte += 2;

	required = requiredbyte / (priv->txbuffsize-4);

	if (requiredbyte % priv->txbuffsize)
		required++;

	/* for now we keep two free descriptor as a safety boundary
	 * between the tail and the head
	 */

	return (required+2 < get_curr_tx_free_desc(dev,priority));
}