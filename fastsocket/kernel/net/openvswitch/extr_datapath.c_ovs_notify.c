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
struct genl_multicast_group {int /*<<< orphan*/  id; } ;
struct genl_info {int /*<<< orphan*/  nlhdr; int /*<<< orphan*/  snd_pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  genl_info_net (struct genl_info*) ; 
 int /*<<< orphan*/  genl_notify (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ovs_notify(struct sk_buff *skb, struct genl_info *info,
		       struct genl_multicast_group *grp)
{
	genl_notify(skb, genl_info_net(info), info->snd_pid,
		    grp->id, info->nlhdr, GFP_KERNEL);
}