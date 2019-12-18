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
struct TYPE_2__ {unsigned int len; } ;
struct mbuf {int m_flags; scalar_t__ m_len; struct mbuf* m_next; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 

unsigned int
m_length(struct mbuf *m)
{
	struct mbuf *m0;
	unsigned int pktlen;

	if (m->m_flags & M_PKTHDR)
		return (m->m_pkthdr.len);

	pktlen = 0;
	for (m0 = m; m0 != NULL; m0 = m0->m_next)
		pktlen += m0->m_len;
	return (pktlen);
}