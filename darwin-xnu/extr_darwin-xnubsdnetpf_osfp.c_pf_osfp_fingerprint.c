#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct tcphdr {int th_off; } ;
struct pf_pdesc {scalar_t__ proto; int /*<<< orphan*/  af; } ;
struct pf_osfp_enlist {int dummy; } ;
struct ip6_hdr {int dummy; } ;
typedef  struct ip6_hdr ip ;
struct TYPE_4__ {struct ip6_hdr* pb_data; } ;
typedef  TYPE_1__ pbuf_t ;

/* Variables and functions */
 scalar_t__ IPPROTO_TCP ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 struct pf_osfp_enlist* pf_osfp_fingerprint_hdr (struct ip6_hdr*,struct ip6_hdr*,struct tcphdr*) ; 
 int /*<<< orphan*/  pf_pull_hdr (TYPE_1__*,int,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

struct pf_osfp_enlist *
pf_osfp_fingerprint(struct pf_pdesc *pd, pbuf_t *pbuf, int off,
    const struct tcphdr *tcp)
{
	struct ip *ip;
	struct ip6_hdr *ip6;
	char hdr[60];

	if ((pd->af != PF_INET && pd->af != PF_INET6) ||
	    pd->proto != IPPROTO_TCP ||
	    (tcp->th_off << 2) < (int)sizeof (*tcp))
		return (NULL);

	if (pd->af == PF_INET) {
		ip = pbuf->pb_data;
		ip6 = (struct ip6_hdr *)NULL;
	} else {
		ip = (struct ip *)NULL;
		ip6 = pbuf->pb_data;
	}
	if (!pf_pull_hdr(pbuf, off, hdr, tcp->th_off << 2, NULL, NULL,
	    pd->af))
		return (NULL);

	return (pf_osfp_fingerprint_hdr(ip, ip6, (struct tcphdr *)(void *)hdr));
}