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
typedef  int u_int8_t ;
typedef  int u_int16_t ;
struct xt_tcpoptstrip_target_info {int /*<<< orphan*/  strip_bmap; } ;
struct tcphdr {int /*<<< orphan*/  check; } ;
struct sk_buff {int /*<<< orphan*/  len; } ;

/* Variables and functions */
 unsigned int NF_DROP ; 
 int TCPOPT_NOP ; 
 unsigned int XT_CONTINUE ; 
 int /*<<< orphan*/  htons (int) ; 
 int /*<<< orphan*/  inet_proto_csum_replace2 (int /*<<< orphan*/ *,struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int*,int,unsigned int) ; 
 unsigned int optlen (int*,unsigned int) ; 
 int /*<<< orphan*/  skb_make_writable (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ skb_network_header (struct sk_buff*) ; 
 unsigned int tcp_hdrlen (struct sk_buff*) ; 
 int /*<<< orphan*/  tcpoptstrip_test_bit (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static unsigned int
tcpoptstrip_mangle_packet(struct sk_buff *skb,
			  const struct xt_tcpoptstrip_target_info *info,
			  unsigned int tcphoff, unsigned int minlen)
{
	unsigned int optl, i, j;
	struct tcphdr *tcph;
	u_int16_t n, o;
	u_int8_t *opt;

	if (!skb_make_writable(skb, skb->len))
		return NF_DROP;

	tcph = (struct tcphdr *)(skb_network_header(skb) + tcphoff);
	opt  = (u_int8_t *)tcph;

	/*
	 * Walk through all TCP options - if we find some option to remove,
	 * set all octets to %TCPOPT_NOP and adjust checksum.
	 */
	for (i = sizeof(struct tcphdr); i < tcp_hdrlen(skb); i += optl) {
		optl = optlen(opt, i);

		if (i + optl > tcp_hdrlen(skb))
			break;

		if (!tcpoptstrip_test_bit(info->strip_bmap, opt[i]))
			continue;

		for (j = 0; j < optl; ++j) {
			o = opt[i+j];
			n = TCPOPT_NOP;
			if ((i + j) % 2 == 0) {
				o <<= 8;
				n <<= 8;
			}
			inet_proto_csum_replace2(&tcph->check, skb, htons(o),
						 htons(n), 0);
		}
		memset(opt + i, TCPOPT_NOP, optl);
	}

	return XT_CONTINUE;
}