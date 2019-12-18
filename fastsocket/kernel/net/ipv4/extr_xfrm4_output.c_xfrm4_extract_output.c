#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  protocol; } ;
struct TYPE_3__ {int /*<<< orphan*/  protocol; } ;

/* Variables and functions */
 TYPE_2__* XFRM_MODE_SKB_CB (struct sk_buff*) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 
 int xfrm4_extract_header (struct sk_buff*) ; 
 int xfrm4_tunnel_check_size (struct sk_buff*) ; 

int xfrm4_extract_output(struct xfrm_state *x, struct sk_buff *skb)
{
	int err;

	err = xfrm4_tunnel_check_size(skb);
	if (err)
		return err;

	XFRM_MODE_SKB_CB(skb)->protocol = ip_hdr(skb)->protocol;

	return xfrm4_extract_header(skb);
}