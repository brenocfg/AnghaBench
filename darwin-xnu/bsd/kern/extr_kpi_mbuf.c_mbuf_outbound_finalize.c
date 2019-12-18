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
typedef  int u_int32_t ;
struct TYPE_2__ {int /*<<< orphan*/  csum_flags; } ;
struct mbuf {TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
#define  PF_INET 129 
#define  PF_INET6 128 
 int /*<<< orphan*/  in6_finalize_cksum (struct mbuf*,size_t,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_finalize_cksum (struct mbuf*,size_t,int /*<<< orphan*/ ) ; 

void
mbuf_outbound_finalize(struct mbuf *m, u_int32_t pf, size_t o)
{
	/* Generate the packet in software, client needs it */
	switch (pf) {
	case PF_INET:
		(void) in_finalize_cksum(m, o, m->m_pkthdr.csum_flags);
		break;

	case PF_INET6:
#if INET6
		/*
		 * Checksum offload should not have been enabled when
		 * extension headers exist; indicate that the callee
		 * should skip such case by setting optlen to -1.
		 */
		(void) in6_finalize_cksum(m, o, -1, -1, m->m_pkthdr.csum_flags);
#endif /* INET6 */
		break;

	default:
		break;
	}
}