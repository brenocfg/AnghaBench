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
typedef  int /*<<< orphan*/  ushort ;
struct sk_buff_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __skb_queue_head_init (struct sk_buff_head*) ; 
 int /*<<< orphan*/  aoecmd_cfg_pkts (int /*<<< orphan*/ ,unsigned char,struct sk_buff_head*) ; 
 int /*<<< orphan*/  aoenet_xmit (struct sk_buff_head*) ; 

void
aoecmd_cfg(ushort aoemajor, unsigned char aoeminor)
{
	struct sk_buff_head queue;

	__skb_queue_head_init(&queue);
	aoecmd_cfg_pkts(aoemajor, aoeminor, &queue);
	aoenet_xmit(&queue);
}