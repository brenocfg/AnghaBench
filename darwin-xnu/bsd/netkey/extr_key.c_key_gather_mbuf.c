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
struct sadb_msghdr {int* extlen; int /*<<< orphan*/ * extoff; int /*<<< orphan*/ ** ext; int /*<<< orphan*/ * msg; } ;
struct sadb_msg {int dummy; } ;
struct TYPE_2__ {scalar_t__ len; } ;
struct mbuf {int m_len; int m_flags; TYPE_1__ m_pkthdr; struct mbuf* m_next; } ;

/* Variables and functions */
 int /*<<< orphan*/  MGETHDR (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MT_DATA ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  M_WAITOK ; 
 int PFKEY_ALIGN8 (int) ; 
 int SADB_EXT_MAX ; 
 int SADB_EXT_RESERVED ; 
 int /*<<< orphan*/  caddr_t ; 
 struct mbuf* key_alloc_mbuf (int) ; 
 int /*<<< orphan*/  m_cat (struct mbuf*,struct mbuf*) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 struct mbuf* m_copym (struct mbuf*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/  mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 

__attribute__((used)) static struct mbuf *
key_gather_mbuf(struct mbuf *m, const struct sadb_msghdr *mhp,
				int ndeep, int nitem, int *items)
{
	int idx;
	int i;
	struct mbuf *result = NULL, *n;
	int len;
	
	if (m == NULL || mhp == NULL)
		panic("null pointer passed to key_gather");
	
	for (i = 0; i < nitem; i++) {
		idx = items[i];
		if (idx < 0 || idx > SADB_EXT_MAX)
			goto fail;
		/* don't attempt to pull empty extension */
		if (idx == SADB_EXT_RESERVED && mhp->msg == NULL)
			continue;
		if (idx != SADB_EXT_RESERVED  &&
		    (mhp->ext[idx] == NULL || mhp->extlen[idx] == 0))
			continue;
		
		if (idx == SADB_EXT_RESERVED) {
			len = PFKEY_ALIGN8(sizeof(struct sadb_msg));
			MGETHDR(n, M_WAITOK, MT_DATA); // sadb_msg len < MHLEN - enforced by _CASSERT
			if (!n)
				goto fail;
			n->m_len = len;
			n->m_next = NULL;
			m_copydata(m, 0, sizeof(struct sadb_msg),
					   mtod(n, caddr_t));
		} else if (i < ndeep) {
			len = mhp->extlen[idx];
			n = key_alloc_mbuf(len);
			if (!n || n->m_next) {	/*XXX*/
				if (n)
					m_freem(n);
				goto fail;
			}
			m_copydata(m, mhp->extoff[idx], mhp->extlen[idx],
					   mtod(n, caddr_t));
		} else {
			n = m_copym(m, mhp->extoff[idx], mhp->extlen[idx],
						M_WAITOK);
		}
		if (n == NULL)
			goto fail;
		
		if (result)
			m_cat(result, n);
		else
			result = n;
	}
	
	if ((result->m_flags & M_PKTHDR) != 0) {
		result->m_pkthdr.len = 0;
		for (n = result; n; n = n->m_next)
			result->m_pkthdr.len += n->m_len;
	}
	
	return result;
	
fail:
	m_freem(result);
	return NULL;
}