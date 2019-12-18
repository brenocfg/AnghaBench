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
struct sk_buff {scalar_t__ cb; } ;
struct inet6_skb_parm {int iif; } ;

/* Variables and functions */

__attribute__((used)) static int sctp_v6_skb_iif(const struct sk_buff *skb)
{
	struct inet6_skb_parm *opt = (struct inet6_skb_parm *) skb->cb;
	return opt->iif;
}