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
struct sk_buff {int dummy; } ;
struct be_adapter {int dummy; } ;

/* Variables and functions */
 scalar_t__ BE3_chip (struct be_adapter*) ; 
 scalar_t__ be_ipv6_exthdr_check (struct sk_buff*) ; 

__attribute__((used)) static int be_ipv6_tx_stall_chk(struct be_adapter *adapter,
				struct sk_buff *skb)
{
	return BE3_chip(adapter) && be_ipv6_exthdr_check(skb);
}