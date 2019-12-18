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
struct sk_buff {scalar_t__ data; } ;
struct TYPE_3__ {int /*<<< orphan*/  c; } ;
struct TYPE_4__ {TYPE_1__ dst_addr; } ;
typedef  TYPE_2__ STRIP_Header ;

/* Variables and functions */
 scalar_t__ arp_find (int /*<<< orphan*/ ,struct sk_buff*) ; 

__attribute__((used)) static int strip_rebuild_header(struct sk_buff *skb)
{
#ifdef CONFIG_INET
	STRIP_Header *header = (STRIP_Header *) skb->data;

	/* Arp find returns zero if if knows the address, */
	/* or if it doesn't know the address it sends an ARP packet and returns non-zero */
	return arp_find(header->dst_addr.c, skb) ? 1 : 0;
#else
	return 0;
#endif
}