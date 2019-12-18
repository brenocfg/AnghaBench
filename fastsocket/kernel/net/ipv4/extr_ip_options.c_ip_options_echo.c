#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct iphdr {int dummy; } ;
struct ip_options {scalar_t__ optlen; unsigned char* __data; int rr; int rr_needaddr; int ts; int ts_needaddr; int ts_needtime; int srr; unsigned char faddr; int cipso; int /*<<< orphan*/  is_strictroute; } ;
typedef  unsigned char __be32 ;
struct TYPE_8__ {struct ip_options opt; } ;
struct TYPE_7__ {int /*<<< orphan*/  saddr; } ;
struct TYPE_6__ {int /*<<< orphan*/  dev; } ;
struct TYPE_5__ {unsigned char rt_spec_dst; } ;

/* Variables and functions */
 int EINVAL ; 
 TYPE_4__* IPCB (struct sk_buff*) ; 
 int /*<<< orphan*/  IPOPT_END ; 
 unsigned char IPOPT_TS_PRESPEC ; 
 scalar_t__ RTN_LOCAL ; 
 int /*<<< orphan*/  dev_net (int /*<<< orphan*/ ) ; 
 scalar_t__ inet_addr_type (int /*<<< orphan*/ ,unsigned char) ; 
 TYPE_3__* ip_hdr (struct sk_buff*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 
 int /*<<< orphan*/  memset (struct ip_options*,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* skb_dst (struct sk_buff*) ; 
 unsigned char* skb_network_header (struct sk_buff*) ; 
 TYPE_1__* skb_rtable (struct sk_buff*) ; 

int ip_options_echo(struct ip_options * dopt, struct sk_buff * skb)
{
	struct ip_options *sopt;
	unsigned char *sptr, *dptr;
	int soffset, doffset;
	int	optlen;
	__be32	daddr;

	memset(dopt, 0, sizeof(struct ip_options));

	sopt = &(IPCB(skb)->opt);

	if (sopt->optlen == 0)
		return 0;

	sptr = skb_network_header(skb);
	dptr = dopt->__data;

	daddr = skb_rtable(skb)->rt_spec_dst;

	if (sopt->rr) {
		optlen  = sptr[sopt->rr+1];
		soffset = sptr[sopt->rr+2];
		dopt->rr = dopt->optlen + sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->rr, optlen);
		if (sopt->rr_needaddr && soffset <= optlen) {
			if (soffset + 3 > optlen)
				return -EINVAL;
			dptr[2] = soffset + 4;
			dopt->rr_needaddr = 1;
		}
		dptr += optlen;
		dopt->optlen += optlen;
	}
	if (sopt->ts) {
		optlen = sptr[sopt->ts+1];
		soffset = sptr[sopt->ts+2];
		dopt->ts = dopt->optlen + sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->ts, optlen);
		if (soffset <= optlen) {
			if (sopt->ts_needaddr) {
				if (soffset + 3 > optlen)
					return -EINVAL;
				dopt->ts_needaddr = 1;
				soffset += 4;
			}
			if (sopt->ts_needtime) {
				if (soffset + 3 > optlen)
					return -EINVAL;
				if ((dptr[3]&0xF) != IPOPT_TS_PRESPEC) {
					dopt->ts_needtime = 1;
					soffset += 4;
				} else {
					dopt->ts_needtime = 0;

					if (soffset + 8 <= optlen) {
						__be32 addr;

						memcpy(&addr, sptr+soffset-1, 4);
						if (inet_addr_type(dev_net(skb_dst(skb)->dev), addr) != RTN_LOCAL) {
							dopt->ts_needtime = 1;
							soffset += 8;
						}
					}
				}
			}
			dptr[2] = soffset;
		}
		dptr += optlen;
		dopt->optlen += optlen;
	}
	if (sopt->srr) {
		unsigned char * start = sptr+sopt->srr;
		__be32 faddr;

		optlen  = start[1];
		soffset = start[2];
		doffset = 0;
		if (soffset > optlen)
			soffset = optlen + 1;
		soffset -= 4;
		if (soffset > 3) {
			memcpy(&faddr, &start[soffset-1], 4);
			for (soffset-=4, doffset=4; soffset > 3; soffset-=4, doffset+=4)
				memcpy(&dptr[doffset-1], &start[soffset-1], 4);
			/*
			 * RFC1812 requires to fix illegal source routes.
			 */
			if (memcmp(&ip_hdr(skb)->saddr,
				   &start[soffset + 3], 4) == 0)
				doffset -= 4;
		}
		if (doffset > 3) {
			memcpy(&start[doffset-1], &daddr, 4);
			dopt->faddr = faddr;
			dptr[0] = start[0];
			dptr[1] = doffset+3;
			dptr[2] = 4;
			dptr += doffset+3;
			dopt->srr = dopt->optlen + sizeof(struct iphdr);
			dopt->optlen += doffset+3;
			dopt->is_strictroute = sopt->is_strictroute;
		}
	}
	if (sopt->cipso) {
		optlen  = sptr[sopt->cipso+1];
		dopt->cipso = dopt->optlen+sizeof(struct iphdr);
		memcpy(dptr, sptr+sopt->cipso, optlen);
		dptr += optlen;
		dopt->optlen += optlen;
	}
	while (dopt->optlen & 3) {
		*dptr++ = IPOPT_END;
		dopt->optlen++;
	}
	return 0;
}