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
struct TYPE_2__ {int len; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; scalar_t__ m_len; struct mbuf* m_next; } ;

/* Variables and functions */
 int M_COPYALL ; 
 int M_COPYBACK0_COW ; 
 int M_COPYBACK0_PRESERVE ; 
 int M_PKTHDR ; 
 int m_copyback0 (struct mbuf**,int,int,int /*<<< orphan*/ *,int,int) ; 
 int m_length (struct mbuf*) ; 
 int /*<<< orphan*/  panic (char*) ; 

int
m_makewritable(struct mbuf **mp, int off, int len, int how)
{
	int error;
#if DEBUG
	struct mbuf *n;
	int origlen, reslen;

	origlen = m_length(*mp);
#endif /* DEBUG */

#if 0 /* M_COPYALL is large enough */
	if (len == M_COPYALL)
		len = m_length(*mp) - off; /* XXX */
#endif

	error = m_copyback0(mp, off, len, NULL,
	    M_COPYBACK0_PRESERVE | M_COPYBACK0_COW, how);

#if DEBUG
	reslen = 0;
	for (n = *mp; n; n = n->m_next)
		reslen += n->m_len;
	if (origlen != reslen)
		panic("m_makewritable: length changed");
	if (((*mp)->m_flags & M_PKTHDR) && reslen != (*mp)->m_pkthdr.len)
		panic("m_makewritable: inconsist");
#endif /* DEBUG */

	return (error);
}