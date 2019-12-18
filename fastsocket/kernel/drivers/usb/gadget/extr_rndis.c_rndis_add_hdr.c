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
struct sk_buff {int len; } ;
struct rndis_packet_msg_type {void* DataLength; void* DataOffset; void* MessageLength; void* MessageType; } ;

/* Variables and functions */
 int REMOTE_NDIS_PACKET_MSG ; 
 void* cpu_to_le32 (int) ; 
 int /*<<< orphan*/  memset (struct rndis_packet_msg_type*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ skb_push (struct sk_buff*,int) ; 

void rndis_add_hdr (struct sk_buff *skb)
{
	struct rndis_packet_msg_type	*header;

	if (!skb)
		return;
	header = (void *) skb_push (skb, sizeof *header);
	memset (header, 0, sizeof *header);
	header->MessageType = cpu_to_le32(REMOTE_NDIS_PACKET_MSG);
	header->MessageLength = cpu_to_le32(skb->len);
	header->DataOffset = cpu_to_le32 (36);
	header->DataLength = cpu_to_le32(skb->len - sizeof *header);
}