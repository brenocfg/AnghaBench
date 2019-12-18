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
typedef  int /*<<< orphan*/  u_int32_t ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int netlink_unicast (int /*<<< orphan*/ ,struct sk_buff*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nfnl ; 

int nfnetlink_unicast(struct sk_buff *skb, u_int32_t pid, int flags)
{
	return netlink_unicast(nfnl, skb, pid, flags);
}