#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_6__ {int cap_info; } ;
struct TYPE_5__ {int cap_info; } ;
struct TYPE_7__ {TYPE_2__ ht_capa; TYPE_1__ ht_capa_mask; } ;
struct TYPE_8__ {TYPE_3__ mgd; } ;
struct ieee80211_sub_if_data {TYPE_4__ u; } ;
struct ieee80211_sta_ht_cap {int /*<<< orphan*/  cap; } ;
typedef  int __le16 ;

/* Variables and functions */
 int cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __check_htcap_disable(struct ieee80211_sub_if_data *sdata,
				  struct ieee80211_sta_ht_cap *ht_cap,
				  u16 flag)
{
	__le16 le_flag = cpu_to_le16(flag);
	if (sdata->u.mgd.ht_capa_mask.cap_info & le_flag) {
		if (!(sdata->u.mgd.ht_capa.cap_info & le_flag))
			ht_cap->cap &= ~flag;
	}
}