#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct pf_pdesc {int lmw; int af; struct pf_addr* dst; struct pf_addr* src; int /*<<< orphan*/ * ip_sum; int /*<<< orphan*/  pf_mtag; TYPE_1__* mp; } ;
struct pf_addr {int dummy; } ;
struct ip6_hdr {int /*<<< orphan*/  ip6_dst; int /*<<< orphan*/  ip6_src; } ;
struct ip {int /*<<< orphan*/  ip_sum; int /*<<< orphan*/  ip_dst; int /*<<< orphan*/  ip_src; } ;
struct TYPE_5__ {void* pb_data; } ;
typedef  TYPE_1__ pbuf_t ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  VERIFY (int) ; 
 void* pbuf_ensure_writable (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pf_find_mtag_pbuf (TYPE_1__*) ; 

void *
pf_lazy_makewritable(struct pf_pdesc *pd, pbuf_t *pbuf, int len)
{
	void *p;

	if (pd->lmw < 0)
		return (NULL);

	VERIFY(pbuf == pd->mp);

	p = pbuf->pb_data;
	if (len > pd->lmw) {
		if ((p = pbuf_ensure_writable(pbuf, len)) == NULL)
			len = -1;
		pd->lmw = len;
		if (len >= 0) {
			pd->pf_mtag = pf_find_mtag_pbuf(pbuf);

			switch (pd->af) {
			case AF_INET: {
				struct ip *h = p;
				pd->src = (struct pf_addr *)(uintptr_t)&h->ip_src;
				pd->dst = (struct pf_addr *)(uintptr_t)&h->ip_dst;
				pd->ip_sum = &h->ip_sum;
				break;
			}
#if INET6
			case AF_INET6: {
				struct ip6_hdr *h = p;
				pd->src = (struct pf_addr *)(uintptr_t)&h->ip6_src;
				pd->dst = (struct pf_addr *)(uintptr_t)&h->ip6_dst;
				break;
			}
#endif /* INET6 */
			}
		}
	}

	return (len < 0 ? NULL : p);
}