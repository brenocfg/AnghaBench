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
struct TYPE_2__ {int redzone; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int mb_redzone_cookie ; 
 int /*<<< orphan*/  panic (char*,struct mbuf*,int,int,int) ; 

__attribute__((used)) static void
m_redzone_verify(struct mbuf *m)
{
	u_int32_t mb_redzone;

	VERIFY(m->m_flags & M_PKTHDR);

	mb_redzone = ((u_int32_t)(uintptr_t)m) ^ mb_redzone_cookie;
	if (m->m_pkthdr.redzone != mb_redzone) {
		panic("mbuf %p redzone violation with value 0x%x "
		    "(instead of 0x%x, using cookie 0x%x)\n",
		    m, m->m_pkthdr.redzone, mb_redzone, mb_redzone_cookie);
		/* NOTREACHED */
	}
}