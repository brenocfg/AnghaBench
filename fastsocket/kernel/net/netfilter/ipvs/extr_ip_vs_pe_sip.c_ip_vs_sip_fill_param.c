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
struct udphdr {int dummy; } ;
struct sk_buff {unsigned int len; char* data; } ;
struct ip_vs_iphdr {scalar_t__ protocol; int len; } ;
struct ip_vs_conn_param {unsigned int pe_data_len; int /*<<< orphan*/  pe_data; int /*<<< orphan*/  af; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 scalar_t__ IPPROTO_UDP ; 
 scalar_t__ get_callid (char const*,unsigned int,unsigned int,unsigned int*,unsigned int*) ; 
 int /*<<< orphan*/  ip_vs_fill_iphdr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct ip_vs_iphdr*) ; 
 int /*<<< orphan*/  kmalloc (unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,char const*,unsigned int) ; 
 int skb_linearize (struct sk_buff*) ; 
 int /*<<< orphan*/  skb_network_header (struct sk_buff*) ; 

__attribute__((used)) static int
ip_vs_sip_fill_param(struct ip_vs_conn_param *p, struct sk_buff *skb)
{
	struct ip_vs_iphdr iph;
	unsigned int dataoff, datalen, matchoff, matchlen;
	const char *dptr;
	int retc;

	ip_vs_fill_iphdr(p->af, skb_network_header(skb), &iph);

	/* Only useful with UDP */
	if (iph.protocol != IPPROTO_UDP)
		return -EINVAL;

	/* No Data ? */
	dataoff = iph.len + sizeof(struct udphdr);
	if (dataoff >= skb->len)
		return -EINVAL;

	if ((retc=skb_linearize(skb)) < 0)
		return retc;
	dptr = skb->data + dataoff;
	datalen = skb->len - dataoff;

	if (get_callid(dptr, dataoff, datalen, &matchoff, &matchlen))
		return -EINVAL;

	p->pe_data = kmalloc(matchlen, GFP_ATOMIC);
	if (!p->pe_data)
		return -ENOMEM;

	/* N.B: pe_data is only set on success,
	 * this allows fallback to the default persistence logic on failure
	 */
	memcpy(p->pe_data, dptr + matchoff, matchlen);
	p->pe_data_len = matchlen;

	return 0;
}