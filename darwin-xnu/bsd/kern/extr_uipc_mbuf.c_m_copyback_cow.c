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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int M_COPYBACK0_COPYBACK ; 
 int M_COPYBACK0_COW ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int m_copyback0 (struct mbuf**,int,int,void const*,int,int) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int m_length (struct mbuf*) ; 

struct mbuf *
m_copyback_cow(struct mbuf *m0, int off, int len, const void *cp, int how)
{
	int error;

	/* don't support chain expansion */
	VERIFY(off + len <= m_length(m0));

	error = m_copyback0(&m0, off, len, cp,
	    M_COPYBACK0_COPYBACK | M_COPYBACK0_COW, how);
	if (error) {
		/*
		 * no way to recover from partial success.
		 * just free the chain.
		 */
		m_freem(m0);
		return (NULL);
	}
	return (m0);
}