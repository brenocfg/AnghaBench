#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct pf_mtag {int dummy; } ;
struct mbuf {int dummy; } ;
struct TYPE_4__ {int pftag_flags; int /*<<< orphan*/ * pftag_hdr; } ;

/* Variables and functions */
 int PF_TAG_HDR_INET ; 
 int PF_TAG_HDR_INET6 ; 
 TYPE_1__* m_pftag (struct mbuf*) ; 
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__*,int) ; 

void
m_copy_pftag(struct mbuf *to, struct mbuf *from)
{
	memcpy(m_pftag(to), m_pftag(from), sizeof(struct pf_mtag));
#if PF_ECN
	m_pftag(to)->pftag_hdr = NULL;
	m_pftag(to)->pftag_flags &= ~(PF_TAG_HDR_INET|PF_TAG_HDR_INET6);
#endif /* PF_ECN */
}