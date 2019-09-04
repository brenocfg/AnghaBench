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
typedef  unsigned int u_int ;
struct TYPE_2__ {unsigned int len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 unsigned int m_length2 (struct mbuf*,int /*<<< orphan*/ *) ; 

unsigned int
m_fixhdr(struct mbuf *m0)
{
	u_int len;

	VERIFY(m0->m_flags & M_PKTHDR);

	len = m_length2(m0, NULL);
	m0->m_pkthdr.len = len;
	return (len);
}