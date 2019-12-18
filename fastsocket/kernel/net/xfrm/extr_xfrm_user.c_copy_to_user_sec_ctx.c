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
struct xfrm_policy {scalar_t__ security; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int copy_sec_ctx (scalar_t__,struct sk_buff*) ; 

__attribute__((used)) static inline int copy_to_user_sec_ctx(struct xfrm_policy *xp, struct sk_buff *skb)
{
	if (xp->security) {
		return copy_sec_ctx(xp->security, skb);
	}
	return 0;
}