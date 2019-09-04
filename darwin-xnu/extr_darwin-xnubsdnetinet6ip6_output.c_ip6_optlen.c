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
struct ip6_ext {int ip6e_len; } ;
struct in6pcb {TYPE_1__* in6p_outputopts; } ;
struct TYPE_2__ {scalar_t__ ip6po_dest2; scalar_t__ ip6po_rthdr; scalar_t__ ip6po_dest1; scalar_t__ ip6po_hbh; } ;

/* Variables and functions */

int
ip6_optlen(struct in6pcb *in6p)
{
	int len;

	if (!in6p->in6p_outputopts)
		return (0);

	len = 0;
#define	elen(x)								\
	(((struct ip6_ext *)(x)) ?					\
	(((struct ip6_ext *)(x))->ip6e_len + 1) << 3 : 0)

	len += elen(in6p->in6p_outputopts->ip6po_hbh);
	if (in6p->in6p_outputopts->ip6po_rthdr) {
		/* dest1 is valid with rthdr only */
		len += elen(in6p->in6p_outputopts->ip6po_dest1);
	}
	len += elen(in6p->in6p_outputopts->ip6po_rthdr);
	len += elen(in6p->in6p_outputopts->ip6po_dest2);
	return (len);
#undef elen
}