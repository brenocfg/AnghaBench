#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_long ;
struct pcmcia_device {struct net_device* priv; } ;
struct net_device {int dummy; } ;
struct hostap_interface {TYPE_1__* local; } ;
struct hostap_cs_priv {int dummy; } ;
struct TYPE_2__ {struct hostap_cs_priv* hw_priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_FLOW ; 
 int /*<<< orphan*/  PDEBUG (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  kfree (struct hostap_cs_priv*) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  prism2_free_local_data (struct net_device*) ; 
 int /*<<< orphan*/  prism2_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void prism2_detach(struct pcmcia_device *link)
{
	PDEBUG(DEBUG_FLOW, "prism2_detach\n");

	prism2_release((u_long)link);

	/* release net devices */
	if (link->priv) {
		struct hostap_cs_priv *hw_priv;
		struct net_device *dev;
		struct hostap_interface *iface;
		dev = link->priv;
		iface = netdev_priv(dev);
		hw_priv = iface->local->hw_priv;
		prism2_free_local_data(dev);
		kfree(hw_priv);
	}
}