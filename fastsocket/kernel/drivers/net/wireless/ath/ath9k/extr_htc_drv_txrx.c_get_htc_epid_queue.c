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
struct sk_buff_head {int dummy; } ;
struct ath_common {int dummy; } ;
struct TYPE_2__ {struct sk_buff_head data_vo_queue; struct sk_buff_head data_vi_queue; struct sk_buff_head data_bk_queue; struct sk_buff_head data_be_queue; struct sk_buff_head cab_ep_queue; struct sk_buff_head mgmt_ep_queue; } ;
struct ath9k_htc_priv {TYPE_1__ tx; int /*<<< orphan*/  data_vo_ep; int /*<<< orphan*/  data_vi_ep; int /*<<< orphan*/  data_bk_ep; int /*<<< orphan*/  data_be_ep; int /*<<< orphan*/  cab_ep; int /*<<< orphan*/  mgmt_ep; int /*<<< orphan*/  ah; } ;

/* Variables and functions */
 struct ath_common* ath9k_hw_common (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ath_err (struct ath_common*,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline struct sk_buff_head*
get_htc_epid_queue(struct ath9k_htc_priv *priv, u8 epid)
{
	struct ath_common *common = ath9k_hw_common(priv->ah);
	struct sk_buff_head *epid_queue = NULL;

	if (epid == priv->mgmt_ep)
		epid_queue = &priv->tx.mgmt_ep_queue;
	else if (epid == priv->cab_ep)
		epid_queue = &priv->tx.cab_ep_queue;
	else if (epid == priv->data_be_ep)
		epid_queue = &priv->tx.data_be_queue;
	else if (epid == priv->data_bk_ep)
		epid_queue = &priv->tx.data_bk_queue;
	else if (epid == priv->data_vi_ep)
		epid_queue = &priv->tx.data_vi_queue;
	else if (epid == priv->data_vo_ep)
		epid_queue = &priv->tx.data_vo_queue;
	else
		ath_err(common, "Invalid EPID: %d\n", epid);

	return epid_queue;
}