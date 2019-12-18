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
struct TYPE_2__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {int /*<<< orphan*/  sin_zero; int /*<<< orphan*/  sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sk_buff {scalar_t__ len; } ;
struct msghdr {int dummy; } ;
struct iphdr {int /*<<< orphan*/  daddr; } ;
typedef  int /*<<< orphan*/  sin ;
typedef  int /*<<< orphan*/  __be16 ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  IP_ORIGDSTADDR ; 
 int /*<<< orphan*/  SOL_IP ; 
 struct iphdr* ip_hdr (struct sk_buff*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_cmsg (struct msghdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,struct sockaddr_in*) ; 
 scalar_t__ skb_transport_header (struct sk_buff*) ; 
 scalar_t__ skb_transport_offset (struct sk_buff*) ; 

__attribute__((used)) static void ip_cmsg_recv_dstaddr(struct msghdr *msg, struct sk_buff *skb)
{
	struct sockaddr_in sin;
	struct iphdr *iph = ip_hdr(skb);
	__be16 *ports = (__be16 *)skb_transport_header(skb);

	if (skb_transport_offset(skb) + 4 > skb->len)
		return;

	/* All current transport protocols have the port numbers in the
	 * first four bytes of the transport header and this function is
	 * written with this assumption in mind.
	 */

	sin.sin_family = AF_INET;
	sin.sin_addr.s_addr = iph->daddr;
	sin.sin_port = ports[1];
	memset(sin.sin_zero, 0, sizeof(sin.sin_zero));

	put_cmsg(msg, SOL_IP, IP_ORIGDSTADDR, sizeof(sin), &sin);
}