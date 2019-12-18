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
typedef  scalar_t__ u32 ;
struct qeth_card {int dummy; } ;
struct net_device {int /*<<< orphan*/  features; struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int EPERM ; 
 int /*<<< orphan*/  IPA_OUTBOUND_CHECKSUM ; 
 int /*<<< orphan*/  NETIF_F_IP_CSUM ; 
 scalar_t__ qeth_is_supported (struct qeth_card*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int qeth_l3_ethtool_set_tx_csum(struct net_device *dev, u32 data)
{
	struct qeth_card *card = dev->ml_priv;

	if (data) {
		if (qeth_is_supported(card, IPA_OUTBOUND_CHECKSUM))
			dev->features |= NETIF_F_IP_CSUM;
		else
			return -EPERM;
	} else
		dev->features &= ~NETIF_F_IP_CSUM;

	return 0;
}