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
struct sk_buff {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 unsigned short eth_type_trans (struct sk_buff*,int /*<<< orphan*/ ) ; 

unsigned short eth_protocol(struct sk_buff *skb)
{
	return eth_type_trans(skb, skb->dev);
}