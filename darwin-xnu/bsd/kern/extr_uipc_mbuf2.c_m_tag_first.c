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
struct TYPE_2__ {int /*<<< orphan*/  tags; } ;
struct mbuf {int m_flags; TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;

/* Variables and functions */
 int M_PKTHDR ; 
 struct m_tag* SLIST_FIRST (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VERIFY (int) ; 

struct m_tag *
m_tag_first(struct mbuf *m)
{
	VERIFY(m->m_flags & M_PKTHDR);

	return (SLIST_FIRST(&m->m_pkthdr.tags));
}