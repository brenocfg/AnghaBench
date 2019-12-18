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
struct sk_buff {TYPE_1__* nf_bridge; } ;
struct TYPE_2__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int ETH_HLEN ; 
 int /*<<< orphan*/  __skb_push (struct sk_buff*,int) ; 
 int nf_bridge_encap_header_len (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int,int /*<<< orphan*/ ,int) ; 
 int skb_cow_head (struct sk_buff*,int) ; 

int nf_bridge_copy_header(struct sk_buff *skb)
{
	int err;
	int header_size = ETH_HLEN + nf_bridge_encap_header_len(skb);

	err = skb_cow_head(skb, header_size);
	if (err)
		return err;

	skb_copy_to_linear_data_offset(skb, -header_size,
				       skb->nf_bridge->data, header_size);
	__skb_push(skb, nf_bridge_encap_header_len(skb));
	return 0;
}