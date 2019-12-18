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
struct ndis_80211_bssid_ex {int /*<<< orphan*/  length; } ;

/* Variables and functions */
 int le32_to_cpu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ndis_80211_bssid_ex *next_bssid_list_item(
					struct ndis_80211_bssid_ex *bssid,
					int *bssid_len, void *buf, int len)
{
	void *buf_end, *bssid_end;

	buf_end = (char *)buf + len;
	bssid_end = (char *)bssid + *bssid_len;

	if ((int)(buf_end - bssid_end) < sizeof(bssid->length)) {
		*bssid_len = 0;
		return NULL;
	} else {
		bssid = (void *)((char *)bssid + *bssid_len);
		*bssid_len = le32_to_cpu(bssid->length);
		return bssid;
	}
}