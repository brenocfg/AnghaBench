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
typedef  int /*<<< orphan*/  u_int16_t ;
struct pf_addr {int dummy; } ;
typedef  int /*<<< orphan*/  sa_family_t ;
typedef  int /*<<< orphan*/  pbuf_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_ACPY (struct pf_addr*,struct pf_addr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
pf_change_ap(int dir, pbuf_t *pbuf, struct pf_addr *a, u_int16_t *p,
    u_int16_t *ic, u_int16_t *pc, struct pf_addr *an, u_int16_t pn,
    u_int8_t u, sa_family_t af, sa_family_t afn, int ua)
{
	struct pf_addr	ao;
	u_int16_t	po = *p;

	PF_ACPY(&ao, a, af);
	if (ua)
		PF_ACPY(a, an, afn);

	*p = pn;

	switch (af) {
#if INET
	case AF_INET:
		switch (afn) {
		case AF_INET:
			*ic = pf_cksum_fixup(pf_cksum_fixup(*ic,
			ao.addr16[0], an->addr16[0], 0),
			ao.addr16[1], an->addr16[1], 0);
			*p = pn;
			/*
			 * If the packet is originated from an ALG on the NAT gateway
			 * (source address is loopback or local), in which case the
			 * TCP/UDP checksum field contains the pseudo header checksum
			 * that's not yet complemented.
			 * In that case we do not need to fixup the checksum for port
			 * translation as the pseudo header checksum doesn't include ports.
			 *
			 * A packet generated locally will have UDP/TCP CSUM flag
			 * set (gets set in protocol output).
			 *
			 * It should be noted that the fixup doesn't do anything if the
			 * checksum is 0.
			 */
			if (dir == PF_OUT && pbuf != NULL &&
			    (*pbuf->pb_csum_flags & (CSUM_TCP | CSUM_UDP))) {
				/* Pseudo-header checksum does not include ports */
				*pc = ~pf_cksum_fixup(pf_cksum_fixup(~*pc,
				ao.addr16[0], an->addr16[0], u),
				ao.addr16[1], an->addr16[1], u);
			} else {
				*pc =
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
				*pc, ao.addr16[0], an->addr16[0], u),
				ao.addr16[1], an->addr16[1], u),
				po, pn, u);
			}
			break;
#ifdef INET6
		case AF_INET6:
			*p = pn;
			*pc = pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
			    pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(

			    pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(*pc,
			    ao.addr16[0], an->addr16[0], u),
			    ao.addr16[1], an->addr16[1], u),
			    0,            an->addr16[2], u),
			    0,            an->addr16[3], u),
			    0,            an->addr16[4], u),
			    0,            an->addr16[5], u),
			    0,            an->addr16[6], u),
			    0,            an->addr16[7], u),
			    po, pn, u);
			break;
#endif /* INET6 */
		}
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		switch (afn) {
		case AF_INET6:
		/*
		 * If the packet is originated from an ALG on the NAT gateway
		 * (source address is loopback or local), in which case the
		 * TCP/UDP checksum field contains the pseudo header checksum
		 * that's not yet complemented.
		 * A packet generated locally
		 * will have UDP/TCP CSUM flag set (gets set in protocol
		 * output).
		 */
			if (dir == PF_OUT && pbuf != NULL &&
			    (*pbuf->pb_csum_flags & (CSUM_TCPIPV6 |
						   CSUM_UDPIPV6))) {
			/* Pseudo-header checksum does not include ports */
				*pc =
				~pf_cksum_fixup(pf_cksum_fixup(
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
					~*pc,
					ao.addr16[0], an->addr16[0], u),
					ao.addr16[1], an->addr16[1], u),
					ao.addr16[2], an->addr16[2], u),
					ao.addr16[3], an->addr16[3], u),
					ao.addr16[4], an->addr16[4], u),
					ao.addr16[5], an->addr16[5], u),
					ao.addr16[6], an->addr16[6], u),
					ao.addr16[7], an->addr16[7], u);
			} else {
				*pc =
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
				pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
					*pc,
					ao.addr16[0], an->addr16[0], u),
					ao.addr16[1], an->addr16[1], u),
					ao.addr16[2], an->addr16[2], u),
					ao.addr16[3], an->addr16[3], u),
					ao.addr16[4], an->addr16[4], u),
					ao.addr16[5], an->addr16[5], u),
					ao.addr16[6], an->addr16[6], u),
					ao.addr16[7], an->addr16[7], u),
					po, pn, u);
			}
			break;
#ifdef INET
		case AF_INET:
			*pc = pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
			    pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(
			    pf_cksum_fixup(pf_cksum_fixup(pf_cksum_fixup(*pc,
			    ao.addr16[0], an->addr16[0], u),
			    ao.addr16[1], an->addr16[1], u),
			    ao.addr16[2], 0,             u),
			    ao.addr16[3], 0,             u),
			    ao.addr16[4], 0,             u),
			    ao.addr16[5], 0,             u),
			    ao.addr16[6], 0,             u),
			    ao.addr16[7], 0,             u),
			    po, pn, u);
			break;
#endif /* INET */
		}
		break;
#endif /* INET6 */
	}
}