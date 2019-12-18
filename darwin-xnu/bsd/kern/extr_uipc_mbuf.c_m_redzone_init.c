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

__attribute__((used)) static void
m_redzone_init(struct mbuf *m)
{
	VERIFY(m->m_flags & M_PKTHDR);
	/*
	 * Each mbuf has a unique red zone pattern, which is a XOR
	 * of the red zone cookie and the address of the mbuf.
	 */
	m->m_pkthdr.redzone = ((u_int32_t)(uintptr_t)m) ^ mb_redzone_cookie;
}