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
struct sk_buff {int dummy; } ;
struct TYPE_3__ {scalar_t__ send_completion_tid; } ;
struct TYPE_4__ {TYPE_1__ send; } ;
struct hv_netvsc_packet {TYPE_2__ completion; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_kfree_skb_any (struct sk_buff*) ; 
 int /*<<< orphan*/  kfree (struct hv_netvsc_packet*) ; 

__attribute__((used)) static void netvsc_xmit_completion(void *context)
{
	struct hv_netvsc_packet *packet = (struct hv_netvsc_packet *)context;
	struct sk_buff *skb = (struct sk_buff *)
		(unsigned long)packet->completion.send.send_completion_tid;

	kfree(packet);

	if (skb)
		dev_kfree_skb_any(skb);
}