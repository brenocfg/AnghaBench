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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  tmp_rt ;
struct route {int dummy; } ;
struct mbuf {struct mbuf* m_nextpkt; } ;
struct dn_pkt_tag {int dn_dir; int dn_flags; } ;

/* Variables and functions */
#define  DN_TO_IP6_IN 131 
#define  DN_TO_IP6_OUT 130 
#define  DN_TO_IP_IN 129 
#define  DN_TO_IP_OUT 128 
 int /*<<< orphan*/  DPRINTF (char*) ; 
 int /*<<< orphan*/  IPV6_FORWARDING ; 
 int IP_FORWARDING ; 
 int IP_RAWOUTPUT ; 
 int /*<<< orphan*/  PF_INET ; 
 int /*<<< orphan*/  PF_INET6 ; 
 int /*<<< orphan*/  ROUTE_RELEASE (struct route*) ; 
 scalar_t__ VM_KERNEL_ADDRPERM (struct mbuf*) ; 
 int /*<<< orphan*/  bzero (struct route*,int) ; 
 struct dn_pkt_tag* dn_tag_get (struct mbuf*) ; 
 int /*<<< orphan*/  ip6_output (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ip_output (struct mbuf*,int /*<<< orphan*/ *,struct route*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  proto_inject (int /*<<< orphan*/ ,struct mbuf*) ; 

__attribute__((used)) static void
dummynet_send(struct mbuf *m)
{
	struct dn_pkt_tag *pkt;
	struct mbuf *n;

	for (; m != NULL; m = n) {
		n = m->m_nextpkt;
		m->m_nextpkt = NULL;
		pkt = dn_tag_get(m);

		DPRINTF(("dummynet_send m: 0x%llx dn_dir: %d dn_flags: 0x%x\n",
		    (uint64_t)VM_KERNEL_ADDRPERM(m), pkt->dn_dir,
		    pkt->dn_flags));

	switch (pkt->dn_dir) {
		case DN_TO_IP_OUT: {
			struct route tmp_rt;

			/* route is already in the packet's dn_ro */
			bzero(&tmp_rt, sizeof (tmp_rt));

			/* Force IP_RAWOUTPUT as the IP header is fully formed */
			pkt->dn_flags |= IP_RAWOUTPUT | IP_FORWARDING;
			(void)ip_output(m, NULL, &tmp_rt, pkt->dn_flags, NULL, NULL);
			ROUTE_RELEASE(&tmp_rt);
			break ;
		}
		case DN_TO_IP_IN :
			proto_inject(PF_INET, m);
			break ;
#ifdef INET6
		case DN_TO_IP6_OUT: {
			/* routes already in the packet's dn_{ro6,pmtu} */
			ip6_output(m, NULL, NULL, IPV6_FORWARDING, NULL, NULL, NULL);
			break;
		}
		case DN_TO_IP6_IN:
			proto_inject(PF_INET6, m);
			break;
#endif /* INET6 */
		default:
			printf("dummynet: bad switch %d!\n", pkt->dn_dir);
			m_freem(m);
			break ;
	}
	}
}