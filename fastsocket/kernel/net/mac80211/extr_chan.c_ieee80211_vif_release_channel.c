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
struct ieee80211_sub_if_data {TYPE_1__* local; scalar_t__ dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  chanctx_mtx; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  __ieee80211_vif_release_channel (struct ieee80211_sub_if_data*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ netif_carrier_ok (scalar_t__) ; 

void ieee80211_vif_release_channel(struct ieee80211_sub_if_data *sdata)
{
	WARN_ON(sdata->dev && netif_carrier_ok(sdata->dev));

	mutex_lock(&sdata->local->chanctx_mtx);
	__ieee80211_vif_release_channel(sdata);
	mutex_unlock(&sdata->local->chanctx_mtx);
}