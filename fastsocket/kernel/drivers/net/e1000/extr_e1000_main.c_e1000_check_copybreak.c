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
typedef  scalar_t__ u32 ;
struct sk_buff {scalar_t__ data; } ;
struct net_device {int dummy; } ;
struct e1000_buffer {struct sk_buff* skb; } ;

/* Variables and functions */
 int /*<<< orphan*/  NET_IP_ALIGN ; 
 scalar_t__ copybreak ; 
 struct sk_buff* netdev_alloc_skb_ip_align (struct net_device*,scalar_t__) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data_offset (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 

__attribute__((used)) static void e1000_check_copybreak(struct net_device *netdev,
				 struct e1000_buffer *buffer_info,
				 u32 length, struct sk_buff **skb)
{
	struct sk_buff *new_skb;

	if (length > copybreak)
		return;

	new_skb = netdev_alloc_skb_ip_align(netdev, length);
	if (!new_skb)
		return;

	skb_copy_to_linear_data_offset(new_skb, -NET_IP_ALIGN,
				       (*skb)->data - NET_IP_ALIGN,
				       length + NET_IP_ALIGN);
	/* save the skb in buffer_info as good */
	buffer_info->skb = *skb;
	*skb = new_skb;
}