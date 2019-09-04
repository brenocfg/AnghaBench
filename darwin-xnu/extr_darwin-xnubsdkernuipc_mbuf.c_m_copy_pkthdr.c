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
struct mbuf {int m_flags; int /*<<< orphan*/  m_pktdat; int /*<<< orphan*/  m_data; int /*<<< orphan*/  m_pkthdr; } ;

/* Variables and functions */
 int M_COPYFLAGS ; 
 int M_EXT ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_classifier_init (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_redzone_init (struct mbuf*) ; 
 int /*<<< orphan*/  m_redzone_verify (struct mbuf*) ; 
 int /*<<< orphan*/  m_scratch_init (struct mbuf*) ; 
 int /*<<< orphan*/  m_tag_delete_chain (struct mbuf*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  m_tag_init (struct mbuf*,int) ; 

void
m_copy_pkthdr(struct mbuf *to, struct mbuf *from)
{
	VERIFY(from->m_flags & M_PKTHDR);

	/* Check for scratch area overflow */
	m_redzone_verify(from);

	if (to->m_flags & M_PKTHDR) {
		/* Check for scratch area overflow */
		m_redzone_verify(to);
		/* We will be taking over the tags of 'to' */
		m_tag_delete_chain(to, NULL);
	}
	to->m_pkthdr = from->m_pkthdr;		/* especially tags */
	m_classifier_init(from, 0);		/* purge classifier info */
	m_tag_init(from, 1);			/* purge all tags from src */
	m_scratch_init(from);			/* clear src scratch area */
	to->m_flags = (from->m_flags & M_COPYFLAGS) | (to->m_flags & M_EXT);
	if ((to->m_flags & M_EXT) == 0)
		to->m_data = to->m_pktdat;
	m_redzone_init(to);			/* setup red zone on dst */
}