#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  _net_mtag; } ;
struct TYPE_4__ {TYPE_1__ builtin_mtag; int /*<<< orphan*/  tags; } ;
struct mbuf {int m_flags; TYPE_2__ m_pkthdr; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 

void
m_tag_init(struct mbuf *m, int all)
{
	VERIFY(m->m_flags & M_PKTHDR);

	SLIST_INIT(&m->m_pkthdr.tags);
	/*
	 * If the caller wants to preserve static mbuf tags
	 * (e.g. m_dup_pkthdr), don't zero them out.
	 */
	if (all) {
		bzero(&m->m_pkthdr.builtin_mtag._net_mtag,
		    sizeof (m->m_pkthdr.builtin_mtag._net_mtag));
	}
}