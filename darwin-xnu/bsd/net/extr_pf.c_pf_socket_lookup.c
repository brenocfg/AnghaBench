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
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_8__ {int /*<<< orphan*/  gid; int /*<<< orphan*/  uid; int /*<<< orphan*/  pid; } ;
struct TYPE_7__ {TYPE_2__* udp; TYPE_1__* tcp; } ;
struct pf_pdesc {int proto; int af; TYPE_4__ lookup; struct pf_addr* src; struct pf_addr* dst; TYPE_3__ hdr; } ;
struct in6_addr {int /*<<< orphan*/ * s6_addr32; void** s6_addr16; } ;
struct pf_addr {struct in6_addr v6addr; int /*<<< orphan*/  v4addr; } ;
struct inpcbinfo {int dummy; } ;
typedef  int /*<<< orphan*/  s6 ;
typedef  int /*<<< orphan*/  d6 ;
struct TYPE_6__ {int /*<<< orphan*/  uh_dport; int /*<<< orphan*/  uh_sport; } ;
struct TYPE_5__ {int /*<<< orphan*/  th_dport; int /*<<< orphan*/  th_sport; } ;

/* Variables and functions */
#define  AF_INET 131 
#define  AF_INET6 130 
 int /*<<< orphan*/  GID_MAX ; 
 int /*<<< orphan*/  INPLOOKUP_WILDCARD ; 
#define  IPPROTO_TCP 129 
#define  IPPROTO_UDP 128 
 int /*<<< orphan*/  NO_PID ; 
 int PF_IN ; 
 int /*<<< orphan*/  UID_MAX ; 
 void* htons (int) ; 
 int in6_pcblookup_hash_exists (struct inpcbinfo*,struct in6_addr*,int /*<<< orphan*/ ,struct in6_addr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int in_pcblookup_hash_exists (struct inpcbinfo*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (struct in6_addr*,int /*<<< orphan*/ ,int) ; 
 struct inpcbinfo tcbinfo ; 
 struct inpcbinfo udbinfo ; 

int
pf_socket_lookup(int direction, struct pf_pdesc *pd)
{
	struct pf_addr		*saddr, *daddr;
	u_int16_t		 sport, dport;
	struct inpcbinfo	*pi;
	int 			inp = 0;

	if (pd == NULL)
		return (-1);
	pd->lookup.uid = UID_MAX;
	pd->lookup.gid = GID_MAX;
	pd->lookup.pid = NO_PID;

	switch (pd->proto) {
	case IPPROTO_TCP:
		if (pd->hdr.tcp == NULL)
			return (-1);
		sport = pd->hdr.tcp->th_sport;
		dport = pd->hdr.tcp->th_dport;
		pi = &tcbinfo;
		break;
	case IPPROTO_UDP:
		if (pd->hdr.udp == NULL)
			return (-1);
		sport = pd->hdr.udp->uh_sport;
		dport = pd->hdr.udp->uh_dport;
		pi = &udbinfo;
		break;
	default:
		return (-1);
	}
	if (direction == PF_IN) {
		saddr = pd->src;
		daddr = pd->dst;
	} else {
		u_int16_t	p;

		p = sport;
		sport = dport;
		dport = p;
		saddr = pd->dst;
		daddr = pd->src;
	}
	switch (pd->af) {
#if INET
	case AF_INET:
		inp = in_pcblookup_hash_exists(pi, saddr->v4addr, sport, daddr->v4addr, dport,
		    0, &pd->lookup.uid, &pd->lookup.gid, NULL);
#if INET6
		if (inp == 0) {
			struct in6_addr s6, d6;

			memset(&s6, 0, sizeof (s6));
			s6.s6_addr16[5] = htons(0xffff);
			memcpy(&s6.s6_addr32[3], &saddr->v4addr,
			    sizeof (saddr->v4addr));

			memset(&d6, 0, sizeof (d6));
			d6.s6_addr16[5] = htons(0xffff);
			memcpy(&d6.s6_addr32[3], &daddr->v4addr,
			    sizeof (daddr->v4addr));

			inp = in6_pcblookup_hash_exists(pi, &s6, sport,
			    &d6, dport, 0, &pd->lookup.uid, &pd->lookup.gid, NULL);
			if (inp == 0) {
				inp = in_pcblookup_hash_exists(pi, saddr->v4addr, sport,
				    daddr->v4addr, dport, INPLOOKUP_WILDCARD, &pd->lookup.uid, &pd->lookup.gid, NULL);
				if (inp == 0) {
					inp = in6_pcblookup_hash_exists(pi, &s6, sport,
					    &d6, dport, INPLOOKUP_WILDCARD,
					    &pd->lookup.uid, &pd->lookup.gid, NULL);
					if (inp == 0)
						return (-1);
				}
			}
		}
#else
		if (inp == 0) {
			inp = in_pcblookup_hash_exists(pi, saddr->v4addr, sport,
			    daddr->v4addr, dport, INPLOOKUP_WILDCARD,
			    &pd->lookup.uid, &pd->lookup.gid, NULL);
			if (inp == 0)
				return (-1);
		}
#endif /* !INET6 */
		break;
#endif /* INET */
#if INET6
	case AF_INET6:
		inp = in6_pcblookup_hash_exists(pi, &saddr->v6addr, sport, &daddr->v6addr,
		    dport, 0, &pd->lookup.uid, &pd->lookup.gid, NULL);
		if (inp == 0) {
			inp = in6_pcblookup_hash_exists(pi, &saddr->v6addr, sport,
			    &daddr->v6addr, dport, INPLOOKUP_WILDCARD,
			    &pd->lookup.uid, &pd->lookup.gid, NULL);
			if (inp == 0)
				return (-1);
		}
		break;
#endif /* INET6 */

	default:
		return (-1);
	}

	return (1);
}