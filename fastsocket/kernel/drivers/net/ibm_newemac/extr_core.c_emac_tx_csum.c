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
typedef  int /*<<< orphan*/  u16 ;
struct sk_buff {scalar_t__ ip_summed; } ;
struct TYPE_2__ {int /*<<< orphan*/  tx_packets_csum; } ;
struct emac_instance {TYPE_1__ stats; } ;

/* Variables and functions */
 scalar_t__ CHECKSUM_PARTIAL ; 
 int /*<<< orphan*/  EMAC_FTR_HAS_TAH ; 
 int /*<<< orphan*/  EMAC_TX_CTRL_TAH_CSUM ; 
 scalar_t__ emac_has_feature (struct emac_instance*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline u16 emac_tx_csum(struct emac_instance *dev,
			       struct sk_buff *skb)
{
	if (emac_has_feature(dev, EMAC_FTR_HAS_TAH) &&
		(skb->ip_summed == CHECKSUM_PARTIAL)) {
		++dev->stats.tx_packets_csum;
		return EMAC_TX_CTRL_TAH_CSUM;
	}
	return 0;
}