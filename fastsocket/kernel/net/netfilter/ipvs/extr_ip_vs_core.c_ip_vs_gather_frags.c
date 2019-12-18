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
 int ip_defrag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  ip_send_check (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int ip_vs_gather_frags(struct sk_buff *skb, u_int32_t user)
{
	int err = ip_defrag(skb, user);

	if (!err)
		ip_send_check(ip_hdr(skb));

	return err;
}