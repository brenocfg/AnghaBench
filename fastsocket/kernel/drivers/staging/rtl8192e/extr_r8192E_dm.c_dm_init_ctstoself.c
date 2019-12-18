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
struct r8192_priv {TYPE_1__* ieee80211; } ;
struct net_device {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  CTSToSelfTH; int /*<<< orphan*/  bCTSToSelfEnable; } ;

/* Variables and functions */
 int /*<<< orphan*/  CTSToSelfTHVal ; 
 int /*<<< orphan*/  TRUE ; 
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

__attribute__((used)) static void dm_init_ctstoself(struct net_device * dev)
{
	struct r8192_priv *priv = ieee80211_priv((struct net_device *)dev);

	priv->ieee80211->bCTSToSelfEnable = TRUE;
	priv->ieee80211->CTSToSelfTH = CTSToSelfTHVal;
}