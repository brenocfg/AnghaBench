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
struct sock {int dummy; } ;
struct sk_buff {int dummy; } ;
struct nr_sock {int /*<<< orphan*/  dest_addr; int /*<<< orphan*/  source_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  AX25_ADDR_LEN ; 
 unsigned char AX25_CBIT ; 
 unsigned char AX25_EBIT ; 
 unsigned char AX25_SSSID_SPARE ; 
 int /*<<< orphan*/  ENETUNREACH ; 
 int /*<<< orphan*/  NR_NETWORK_LEN ; 
 int /*<<< orphan*/  kfree_skb (struct sk_buff*) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_disconnect (struct sock*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nr_route_frame (struct sk_buff*,int /*<<< orphan*/ *) ; 
 struct nr_sock* nr_sk (struct sock*) ; 
 unsigned char* skb_push (struct sk_buff*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sysctl_netrom_network_ttl_initialiser ; 

void nr_transmit_buffer(struct sock *sk, struct sk_buff *skb)
{
	struct nr_sock *nr = nr_sk(sk);
	unsigned char *dptr;

	/*
	 *	Add the protocol byte and network header.
	 */
	dptr = skb_push(skb, NR_NETWORK_LEN);

	memcpy(dptr, &nr->source_addr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] &= ~AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	memcpy(dptr, &nr->dest_addr, AX25_ADDR_LEN);
	dptr[6] &= ~AX25_CBIT;
	dptr[6] |= AX25_EBIT;
	dptr[6] |= AX25_SSSID_SPARE;
	dptr += AX25_ADDR_LEN;

	*dptr++ = sysctl_netrom_network_ttl_initialiser;

	if (!nr_route_frame(skb, NULL)) {
		kfree_skb(skb);
		nr_disconnect(sk, ENETUNREACH);
	}
}