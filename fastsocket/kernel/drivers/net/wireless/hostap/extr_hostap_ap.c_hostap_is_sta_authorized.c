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
typedef  int /*<<< orphan*/  u8 ;
struct sta_info {int flags; int /*<<< orphan*/  ap; } ;
struct ap_data {int /*<<< orphan*/  sta_table_lock; TYPE_1__* local; } ;
struct TYPE_2__ {scalar_t__ ieee_802_1x; } ;

/* Variables and functions */
 int WLAN_STA_ASSOC ; 
 int WLAN_STA_AUTHORIZED ; 
 struct sta_info* ap_get_sta (struct ap_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

int hostap_is_sta_authorized(struct ap_data *ap, u8 *sta_addr)
{
	struct sta_info *sta;
	int ret = 0;

	spin_lock(&ap->sta_table_lock);
	sta = ap_get_sta(ap, sta_addr);
	if (sta != NULL && (sta->flags & WLAN_STA_ASSOC) && !sta->ap &&
	    ((sta->flags & WLAN_STA_AUTHORIZED) ||
	     ap->local->ieee_802_1x == 0))
		ret = 1;
	spin_unlock(&ap->sta_table_lock);

	return ret;
}