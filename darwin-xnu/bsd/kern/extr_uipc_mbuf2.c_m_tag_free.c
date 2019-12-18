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
typedef  int /*<<< orphan*/  u_int64_t ;
struct mbuf {int m_flags; scalar_t__ m_data; } ;
struct m_taghdr {scalar_t__ refcnt; } ;
struct m_tag {scalar_t__ m_tag_id; scalar_t__ m_tag_type; scalar_t__ m_tag_cookie; int /*<<< orphan*/  m_tag_len; } ;
typedef  int /*<<< orphan*/  caddr_t ;

/* Variables and functions */
 int IS_P2ALIGNED (struct m_taghdr*,int) ; 
 scalar_t__ KERNEL_MODULE_TAG_ID ; 
 scalar_t__ KERNEL_TAG_TYPE_MACLABEL ; 
 scalar_t__ MLEN ; 
 int M_TAGHDR ; 
 scalar_t__ M_TAG_ALIGN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M_TAG_FREE_PATTERN ; 
 scalar_t__ M_TAG_VALID_PATTERN ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 struct mbuf* m_dtom (struct m_tag*) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_mclfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mac_mbuf_tag_destroy (struct m_tag*) ; 

void
m_tag_free(struct m_tag *t)
{
#if CONFIG_MACF_NET
	if (t != NULL && 
	    t->m_tag_id   == KERNEL_MODULE_TAG_ID &&
	    t->m_tag_type == KERNEL_TAG_TYPE_MACLABEL)
		mac_mbuf_tag_destroy(t);
#endif
	if (t == NULL)
		return;

	VERIFY(t->m_tag_cookie == M_TAG_VALID_PATTERN);

	if (M_TAG_ALIGN(t->m_tag_len) + sizeof (struct m_taghdr) <= MLEN) {
		struct mbuf * m = m_dtom(t);
		VERIFY(m->m_flags & M_TAGHDR);
		struct m_taghdr *hdr = (struct m_taghdr *)(void *)m->m_data;

		VERIFY(IS_P2ALIGNED(hdr + 1, sizeof (u_int64_t)));

		/* No other tags in this mbuf */
		if(--hdr->refcnt == 0) {
			m_free(m);
			return;
		}

		/* Pattern-fill the header */
		u_int64_t *fill_ptr = (u_int64_t *)t;
		u_int64_t *end_ptr = (u_int64_t *)(t + 1);
		while (fill_ptr < end_ptr) {
			*fill_ptr = M_TAG_FREE_PATTERN;
			fill_ptr++;
		}
	} else {
		m_mclfree((caddr_t)t);
	}
}