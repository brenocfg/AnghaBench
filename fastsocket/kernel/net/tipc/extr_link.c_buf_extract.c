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
struct tipc_msg {int dummy; } ;
struct sk_buff {scalar_t__ data; } ;

/* Variables and functions */
 struct sk_buff* buf_acquire (scalar_t__) ; 
 scalar_t__ msg_size (struct tipc_msg*) ; 
 int /*<<< orphan*/  skb_copy_to_linear_data (struct sk_buff*,struct tipc_msg*,scalar_t__) ; 

__attribute__((used)) static struct sk_buff *buf_extract(struct sk_buff *skb, u32 from_pos)
{
	struct tipc_msg *msg = (struct tipc_msg *)(skb->data + from_pos);
	u32 size = msg_size(msg);
	struct sk_buff *eb;

	eb = buf_acquire(size);
	if (eb)
		skb_copy_to_linear_data(eb, msg, size);
	return eb;
}