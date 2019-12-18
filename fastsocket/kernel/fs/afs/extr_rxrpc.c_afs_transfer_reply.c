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
struct sk_buff {size_t len; } ;
struct afs_call {scalar_t__ reply_size; scalar_t__ buffer; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG () ; 
 scalar_t__ skb_copy_bits (struct sk_buff*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 

void afs_transfer_reply(struct afs_call *call, struct sk_buff *skb)
{
	size_t len = skb->len;

	if (skb_copy_bits(skb, 0, call->buffer + call->reply_size, len) < 0)
		BUG();
	call->reply_size += len;
}