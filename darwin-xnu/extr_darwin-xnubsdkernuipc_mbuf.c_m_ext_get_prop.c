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
typedef  int /*<<< orphan*/  uint32_t ;
struct mbuf {int m_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MEXT_PRIV (struct mbuf*) ; 
 int M_EXT ; 

uint32_t
m_ext_get_prop(struct mbuf *m)
{
	ASSERT(m->m_flags & M_EXT);
	return (MEXT_PRIV(m));
}