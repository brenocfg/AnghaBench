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
struct sk_buff {scalar_t__ ip_summed; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 scalar_t__ CHECKSUM_NONE ; 
 int NETIF_F_ALL_CSUM ; 
 int NETIF_F_SG ; 
 int /*<<< orphan*/  can_checksum_protocol (int,int /*<<< orphan*/ ) ; 
 scalar_t__ illegal_highdma (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int harmonize_features(struct sk_buff *skb, __be16 protocol, int features)
{
	if (skb->ip_summed != CHECKSUM_NONE &&
	    !can_checksum_protocol(features, protocol)) {
		features &= ~NETIF_F_ALL_CSUM;
	} else if (illegal_highdma(skb->dev, skb)) {
		features &= ~NETIF_F_SG;
	}

	return features;
}