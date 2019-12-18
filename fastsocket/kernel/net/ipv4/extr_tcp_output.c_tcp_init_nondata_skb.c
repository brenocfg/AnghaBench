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
typedef  int u8 ;
typedef  void* u32 ;
struct sk_buff {scalar_t__ csum; } ;
struct TYPE_4__ {int flags; void* end_seq; void* seq; scalar_t__ sacked; } ;
struct TYPE_3__ {int gso_segs; scalar_t__ gso_type; scalar_t__ gso_size; } ;

/* Variables and functions */
 int TCPCB_FLAG_FIN ; 
 int TCPCB_FLAG_SYN ; 
 TYPE_2__* TCP_SKB_CB (struct sk_buff*) ; 
 TYPE_1__* skb_shinfo (struct sk_buff*) ; 

__attribute__((used)) static void tcp_init_nondata_skb(struct sk_buff *skb, u32 seq, u8 flags)
{
	skb->csum = 0;

	TCP_SKB_CB(skb)->flags = flags;
	TCP_SKB_CB(skb)->sacked = 0;

	skb_shinfo(skb)->gso_segs = 1;
	skb_shinfo(skb)->gso_size = 0;
	skb_shinfo(skb)->gso_type = 0;

	TCP_SKB_CB(skb)->seq = seq;
	if (flags & (TCPCB_FLAG_SYN | TCPCB_FLAG_FIN))
		seq++;
	TCP_SKB_CB(skb)->end_seq = seq;
}