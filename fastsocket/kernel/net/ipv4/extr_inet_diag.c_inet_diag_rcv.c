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
 int /*<<< orphan*/  inet_diag_mutex ; 
 int /*<<< orphan*/  inet_diag_rcv_msg ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  netlink_rcv_skb (struct sk_buff*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void inet_diag_rcv(struct sk_buff *skb)
{
	mutex_lock(&inet_diag_mutex);
	netlink_rcv_skb(skb, &inet_diag_rcv_msg);
	mutex_unlock(&inet_diag_mutex);
}