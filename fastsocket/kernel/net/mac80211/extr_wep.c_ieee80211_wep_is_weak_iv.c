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
typedef  int u8 ;
typedef  int u32 ;
struct sk_buff {int* data; } ;
struct TYPE_2__ {int /*<<< orphan*/  keylen; } ;
struct ieee80211_key {TYPE_1__ conf; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; } ;

/* Variables and functions */
 unsigned int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int ieee80211_wep_weak_iv (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool ieee80211_wep_is_weak_iv(struct sk_buff *skb,
				     struct ieee80211_key *key)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *)skb->data;
	unsigned int hdrlen;
	u8 *ivpos;
	u32 iv;

	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	ivpos = skb->data + hdrlen;
	iv = (ivpos[0] << 16) | (ivpos[1] << 8) | ivpos[2];

	return ieee80211_wep_weak_iv(iv, key->conf.keylen);
}