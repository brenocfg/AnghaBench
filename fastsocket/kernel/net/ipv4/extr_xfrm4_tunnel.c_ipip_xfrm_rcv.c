#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {int protocol; } ;

/* Variables and functions */
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

__attribute__((used)) static int ipip_xfrm_rcv(struct xfrm_state *x, struct sk_buff *skb)
{
	return ip_hdr(skb)->protocol;
}