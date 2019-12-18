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
struct tcphdr {scalar_t__ check; int /*<<< orphan*/  window; int /*<<< orphan*/  ack_seq; } ;
struct net_lro_desc {int /*<<< orphan*/  data_csum; scalar_t__ ip_tot_len; struct iphdr* iph; int /*<<< orphan*/  tcp_rcv_tsecr; scalar_t__ tcp_saw_tstamp; int /*<<< orphan*/  tcp_window; int /*<<< orphan*/  tcp_ack; struct tcphdr* tcph; } ;
struct iphdr {int /*<<< orphan*/  daddr; int /*<<< orphan*/  saddr; int /*<<< orphan*/  ihl; scalar_t__ check; int /*<<< orphan*/  tot_len; } ;
typedef  int /*<<< orphan*/  __wsum ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 scalar_t__ IP_HDR_LEN (struct iphdr*) ; 
 int /*<<< orphan*/  TCP_HDR_LEN (struct tcphdr*) ; 
 int /*<<< orphan*/  csum_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  csum_partial (struct tcphdr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ csum_tcpudp_magic (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  htons (scalar_t__) ; 
 scalar_t__ ip_fast_csum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void lro_update_tcp_ip_header(struct net_lro_desc *lro_desc)
{
	struct iphdr *iph = lro_desc->iph;
	struct tcphdr *tcph = lro_desc->tcph;
	__be32 *p;
	__wsum tcp_hdr_csum;

	tcph->ack_seq = lro_desc->tcp_ack;
	tcph->window = lro_desc->tcp_window;

	if (lro_desc->tcp_saw_tstamp) {
		p = (__be32 *)(tcph + 1);
		*(p+2) = lro_desc->tcp_rcv_tsecr;
	}

	iph->tot_len = htons(lro_desc->ip_tot_len);

	iph->check = 0;
	iph->check = ip_fast_csum((u8 *)lro_desc->iph, iph->ihl);

	tcph->check = 0;
	tcp_hdr_csum = csum_partial(tcph, TCP_HDR_LEN(tcph), 0);
	lro_desc->data_csum = csum_add(lro_desc->data_csum, tcp_hdr_csum);
	tcph->check = csum_tcpudp_magic(iph->saddr, iph->daddr,
					lro_desc->ip_tot_len -
					IP_HDR_LEN(iph), IPPROTO_TCP,
					lro_desc->data_csum);
}