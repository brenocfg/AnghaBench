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

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_rcv_skb (struct sk_buff*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_cfg_mutex ; 
 int /*<<< orphan*/  xfrm_user_rcv_msg ; 

__attribute__((used)) static void xfrm_netlink_rcv(struct sk_buff *skb)
{
	mutex_lock(&xfrm_cfg_mutex);
	netlink_rcv_skb(skb, &xfrm_user_rcv_msg);
	mutex_unlock(&xfrm_cfg_mutex);
}