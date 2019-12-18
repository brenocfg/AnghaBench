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
typedef  scalar_t__ u8 ;
struct tx_mgmt_hdr {scalar_t__ cookie; } ;
struct tx_frame_hdr {scalar_t__ cookie; } ;
struct sk_buff {scalar_t__ data; } ;
struct ath9k_htc_priv {scalar_t__ mgmt_ep; scalar_t__ data_bk_ep; scalar_t__ data_be_ep; scalar_t__ data_vi_ep; scalar_t__ data_vo_ep; scalar_t__ cab_ep; } ;

/* Variables and functions */

__attribute__((used)) static inline bool check_cookie(struct ath9k_htc_priv *priv,
				struct sk_buff *skb,
				u8 cookie, u8 epid)
{
	u8 fcookie = 0;

	if (epid == priv->mgmt_ep) {
		struct tx_mgmt_hdr *hdr;
		hdr = (struct tx_mgmt_hdr *) skb->data;
		fcookie = hdr->cookie;
	} else if ((epid == priv->data_bk_ep) ||
		   (epid == priv->data_be_ep) ||
		   (epid == priv->data_vi_ep) ||
		   (epid == priv->data_vo_ep) ||
		   (epid == priv->cab_ep)) {
		struct tx_frame_hdr *hdr;
		hdr = (struct tx_frame_hdr *) skb->data;
		fcookie = hdr->cookie;
	}

	if (fcookie == cookie)
		return true;

	return false;
}