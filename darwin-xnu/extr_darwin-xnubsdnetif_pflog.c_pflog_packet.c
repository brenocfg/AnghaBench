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
typedef  int /*<<< orphan*/  u_int8_t ;
struct pfi_kif {int dummy; } ;
struct pf_ruleset {int dummy; } ;
struct pf_rule {int dummy; } ;
struct pf_pdesc {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */

int
pflog_packet(struct pfi_kif *kif, pbuf_t *pbuf, sa_family_t af, u_int8_t dir,
    u_int8_t reason, struct pf_rule *rm, struct pf_rule *am,
    struct pf_ruleset *ruleset, struct pf_pdesc *pd)
{
#if NBPFILTER > 0
	struct ifnet *ifn;
	struct pfloghdr hdr;
	struct mbuf *m;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (kif == NULL || !pbuf_is_valid(pbuf) || rm == NULL || pd == NULL)
		return (-1);

	if (rm->logif >= PFLOGIFS_MAX ||
	    (ifn = pflogifs[rm->logif]) == NULL || !ifn->if_bpf) {
		return (0);
	}

	if ((m = pbuf_to_mbuf(pbuf, FALSE)) == NULL)
		return (0);

	bzero(&hdr, sizeof (hdr));
	hdr.length = PFLOG_REAL_HDRLEN;
	hdr.af = af;
	hdr.action = rm->action;
	hdr.reason = reason;
	memcpy(hdr.ifname, kif->pfik_name, sizeof (hdr.ifname));

	if (am == NULL) {
		hdr.rulenr = htonl(rm->nr);
		hdr.subrulenr = -1;
	} else {
		hdr.rulenr = htonl(am->nr);
		hdr.subrulenr = htonl(rm->nr);
		if (ruleset != NULL && ruleset->anchor != NULL)
			strlcpy(hdr.ruleset, ruleset->anchor->name,
			    sizeof (hdr.ruleset));
	}
	if (rm->log & PF_LOG_SOCKET_LOOKUP && !pd->lookup.done)
		pd->lookup.done = pf_socket_lookup(dir, pd);
	if (pd->lookup.done > 0) {
		hdr.uid = pd->lookup.uid;
		hdr.pid = pd->lookup.pid;
	} else {
		hdr.uid = UID_MAX;
		hdr.pid = NO_PID;
	}
	hdr.rule_uid = rm->cuid;
	hdr.rule_pid = rm->cpid;
	hdr.dir = dir;

#if INET
	if (af == AF_INET && dir == PF_OUT) {
		struct ip *ip;

		ip = mtod(m, struct ip *);
		ip->ip_sum = 0;
		ip->ip_sum = in_cksum(m, ip->ip_hl << 2);
	}
#endif /* INET */

	atomic_add_64(&ifn->if_opackets, 1);
	atomic_add_64(&ifn->if_obytes, m->m_pkthdr.len);

	switch (dir) {
	case PF_IN:
		bpf_tap_in(ifn, DLT_PFLOG, m, &hdr, PFLOG_HDRLEN);
		break;

	case PF_OUT:
		bpf_tap_out(ifn, DLT_PFLOG, m, &hdr, PFLOG_HDRLEN);
		break;

	default:
		break;
	}
#endif /* NBPFILTER > 0 */
	return (0);
}