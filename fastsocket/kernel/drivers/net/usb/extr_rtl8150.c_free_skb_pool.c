#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__* rx_skb_pool; } ;
typedef  TYPE_1__ rtl8150_t ;

/* Variables and functions */
 int RX_SKB_POOL_SIZE ; 
 int /*<<< orphan*/  dev_kfree_skb (scalar_t__) ; 

__attribute__((used)) static void free_skb_pool(rtl8150_t *dev)
{
	int i;

	for (i = 0; i < RX_SKB_POOL_SIZE; i++)
		if (dev->rx_skb_pool[i])
			dev_kfree_skb(dev->rx_skb_pool[i]);
}