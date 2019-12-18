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
typedef  scalar_t__ u32 ;
struct sk_buff {int dummy; } ;
struct TYPE_2__ {scalar_t__ protocol; } ;

/* Variables and functions */
 int EACCES ; 
 int /*<<< orphan*/  ICMP_DEST_UNREACH ; 
 int /*<<< orphan*/  ICMP_HOST_ANO ; 
 int /*<<< orphan*/  ICMP_NET_ANO ; 
 scalar_t__ IPPROTO_ICMP ; 
 int /*<<< orphan*/  icmp_send (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* ip_hdr (struct sk_buff*) ; 

void cipso_v4_error(struct sk_buff *skb, int error, u32 gateway)
{
	if (ip_hdr(skb)->protocol == IPPROTO_ICMP || error != -EACCES)
		return;

	if (gateway)
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_NET_ANO, 0);
	else
		icmp_send(skb, ICMP_DEST_UNREACH, ICMP_HOST_ANO, 0);
}