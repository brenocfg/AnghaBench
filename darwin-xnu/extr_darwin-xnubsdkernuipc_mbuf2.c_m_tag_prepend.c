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
struct mbuf {TYPE_1__ m_pkthdr; } ;
struct m_tag {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SLIST_INSERT_HEAD (int /*<<< orphan*/ *,struct m_tag*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_tag_link ; 

void
m_tag_prepend(struct mbuf *m, struct m_tag *t)
{
	VERIFY(m != NULL && t != NULL);

	SLIST_INSERT_HEAD(&m->m_pkthdr.tags, t, m_tag_link);
}