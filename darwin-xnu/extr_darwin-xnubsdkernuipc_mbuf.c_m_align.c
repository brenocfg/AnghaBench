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
struct mbuf {scalar_t__ m_data; } ;

/* Variables and functions */
 int M_SIZE (struct mbuf*) ; 
 scalar_t__ M_START (struct mbuf*) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

void
m_align(struct mbuf *m, int len)
{
	int adjust = 0;

	/* At this point data must point to start */
	VERIFY(m->m_data == M_START(m));
	VERIFY(len >= 0);
	VERIFY(len <= M_SIZE(m));
	adjust = M_SIZE(m) - len;
	m->m_data += adjust &~ (sizeof(long) - 1);
}