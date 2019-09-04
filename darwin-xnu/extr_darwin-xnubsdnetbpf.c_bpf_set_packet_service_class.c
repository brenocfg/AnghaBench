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
struct mbuf {int m_flags; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  SO_VALID_TC (int) ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_set_service_class (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  so_tc2msc (int) ; 

__attribute__((used)) static void
bpf_set_packet_service_class(struct mbuf *m, int tc)
{
	if (!(m->m_flags & M_PKTHDR))
		return;

	VERIFY(SO_VALID_TC(tc));
	(void) m_set_service_class(m, so_tc2msc(tc));
}