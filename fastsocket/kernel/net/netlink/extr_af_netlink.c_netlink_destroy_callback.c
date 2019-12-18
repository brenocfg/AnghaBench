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
struct netlink_callback {int /*<<< orphan*/  skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct netlink_callback*) ; 
 int /*<<< orphan*/  kfree_skb (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void netlink_destroy_callback(struct netlink_callback *cb)
{
	kfree_skb(cb->skb);
	kfree(cb);
}