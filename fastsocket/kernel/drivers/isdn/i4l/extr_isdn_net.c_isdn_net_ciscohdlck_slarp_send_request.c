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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {int dummy; } ;
typedef  int /*<<< orphan*/  isdn_net_local ;
typedef  int /*<<< orphan*/  __be32 ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  CISCO_ADDR_UNICAST ; 
 int /*<<< orphan*/  CISCO_CTRL ; 
 int /*<<< orphan*/  CISCO_SLARP_REQUEST ; 
 int /*<<< orphan*/  CISCO_TYPE_SLARP ; 
 int /*<<< orphan*/  cpu_to_be16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpu_to_be32 (int /*<<< orphan*/ ) ; 
 struct sk_buff* isdn_net_ciscohdlck_alloc_skb (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  isdn_net_write_super (int /*<<< orphan*/ *,struct sk_buff*) ; 
 unsigned char* skb_put (struct sk_buff*,int) ; 

__attribute__((used)) static void
isdn_net_ciscohdlck_slarp_send_request(isdn_net_local *lp)
{
	struct sk_buff *skb;
	unsigned char *p;

	skb = isdn_net_ciscohdlck_alloc_skb(lp, 4 + 14);
	if (!skb)
		return;

	p = skb_put(skb, 4 + 14);

	/* cisco header */
	*(u8 *)(p + 0) = CISCO_ADDR_UNICAST;
	*(u8 *)(p + 1) = CISCO_CTRL;
	*(__be16 *)(p + 2) = cpu_to_be16(CISCO_TYPE_SLARP);

	/* slarp request */
	*(__be32 *)(p +  4) = cpu_to_be32(CISCO_SLARP_REQUEST);
	*(__be32 *)(p +  8) = cpu_to_be32(0); // address
	*(__be32 *)(p + 12) = cpu_to_be32(0); // netmask
	*(__be16 *)(p + 16) = cpu_to_be16(0); // unused
	p += 18;

	isdn_net_write_super(lp, skb);
}