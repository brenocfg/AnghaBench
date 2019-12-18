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
typedef  int u32 ;
struct net_device {int dummy; } ;
struct ipw2100_priv {int status; } ;

/* Variables and functions */
 int STATUS_ASSOCIATED ; 
 struct ipw2100_priv* libipw_priv (struct net_device*) ; 

__attribute__((used)) static u32 ipw2100_ethtool_get_link(struct net_device *dev)
{
	struct ipw2100_priv *priv = libipw_priv(dev);
	return (priv->status & STATUS_ASSOCIATED) ? 1 : 0;
}