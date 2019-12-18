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
typedef  int /*<<< orphan*/  u32 ;
struct sk_buff {int dummy; } ;
struct net_device {int dummy; } ;
struct ehea_swqe {int /*<<< orphan*/  tx_control; } ;

/* Variables and functions */
 int /*<<< orphan*/  EHEA_SWQE_DESCRIPTORS_PRESENT ; 
 int /*<<< orphan*/  write_swqe2_data (struct sk_buff*,struct net_device*,struct ehea_swqe*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xmit_common (struct sk_buff*,struct ehea_swqe*) ; 

__attribute__((used)) static void ehea_xmit2(struct sk_buff *skb, struct net_device *dev,
		       struct ehea_swqe *swqe, u32 lkey)
{
	swqe->tx_control |= EHEA_SWQE_DESCRIPTORS_PRESENT;

	xmit_common(skb, swqe);

	write_swqe2_data(skb, dev, swqe, lkey);
}