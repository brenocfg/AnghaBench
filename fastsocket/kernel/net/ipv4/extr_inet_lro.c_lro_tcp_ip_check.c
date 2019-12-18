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
struct tcphdr {scalar_t__ doff; scalar_t__ fin; scalar_t__ syn; scalar_t__ rst; int /*<<< orphan*/  ack; scalar_t__ urg; scalar_t__ ece; scalar_t__ cwr; } ;
struct net_lro_desc {scalar_t__ tcp_rcv_tsval; } ;
struct iphdr {scalar_t__ ihl; int /*<<< orphan*/  tot_len; } ;
typedef  scalar_t__ __be32 ;

/* Variables and functions */
 scalar_t__ INET_ECN_is_ce (int /*<<< orphan*/ ) ; 
 scalar_t__ IPH_LEN_WO_OPTIONS ; 
 scalar_t__ TCPH_LEN_WO_OPTIONS ; 
 scalar_t__ TCPH_LEN_W_TIMESTAMP ; 
 int TCPOLEN_TIMESTAMP ; 
 int TCPOPT_NOP ; 
 int TCPOPT_TIMESTAMP ; 
 scalar_t__ TCP_PAYLOAD_LENGTH (struct iphdr*,struct tcphdr*) ; 
 scalar_t__ after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ htonl (int) ; 
 int /*<<< orphan*/  ipv4_get_dsfield (struct iphdr*) ; 
 int /*<<< orphan*/  ntohl (scalar_t__) ; 
 int ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lro_tcp_ip_check(struct iphdr *iph, struct tcphdr *tcph,
			    int len, struct net_lro_desc *lro_desc)
{
        /* check ip header: don't aggregate padded frames */
	if (ntohs(iph->tot_len) != len)
		return -1;

	if (TCP_PAYLOAD_LENGTH(iph, tcph) == 0)
		return -1;

	if (iph->ihl != IPH_LEN_WO_OPTIONS)
		return -1;

	if (tcph->cwr || tcph->ece || tcph->urg || !tcph->ack
	    || tcph->rst || tcph->syn || tcph->fin)
		return -1;

	if (INET_ECN_is_ce(ipv4_get_dsfield(iph)))
		return -1;

	if (tcph->doff != TCPH_LEN_WO_OPTIONS
	    && tcph->doff != TCPH_LEN_W_TIMESTAMP)
		return -1;

	/* check tcp options (only timestamp allowed) */
	if (tcph->doff == TCPH_LEN_W_TIMESTAMP) {
		__be32 *topt = (__be32 *)(tcph + 1);

		if (*topt != htonl((TCPOPT_NOP << 24) | (TCPOPT_NOP << 16)
				   | (TCPOPT_TIMESTAMP << 8)
				   | TCPOLEN_TIMESTAMP))
			return -1;

		/* timestamp should be in right order */
		topt++;
		if (lro_desc && after(ntohl(lro_desc->tcp_rcv_tsval),
				      ntohl(*topt)))
			return -1;

		/* timestamp reply should not be zero */
		topt++;
		if (*topt == 0)
			return -1;
	}

	return 0;
}