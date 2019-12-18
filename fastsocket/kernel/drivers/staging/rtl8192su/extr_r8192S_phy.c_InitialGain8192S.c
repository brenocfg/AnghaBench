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
typedef  int /*<<< orphan*/  u8 ;
struct r8192_priv {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 struct r8192_priv* ieee80211_priv (struct net_device*) ; 

void InitialGain8192S(struct net_device *dev,	u8 Operation)
{
#ifdef TO_DO_LIST
	struct r8192_priv *priv = ieee80211_priv(dev);
#endif

}