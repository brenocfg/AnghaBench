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
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int EXTF_READONLY ; 
 int MEXT_FLAGS (struct mbuf*) ; 
 int M_EXT ; 
 int /*<<< orphan*/ * m_get_rfa (struct mbuf*) ; 

int
m_mclhasreference(struct mbuf *m)
{
	if (!(m->m_flags & M_EXT))
		return (0);

	ASSERT(m_get_rfa(m) != NULL);

	return ((MEXT_FLAGS(m) & EXTF_READONLY) ? 1 : 0);
}