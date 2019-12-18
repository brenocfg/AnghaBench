#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__* mbuf_t ;
typedef  int /*<<< orphan*/  mbuf_how_t ;
typedef  int /*<<< orphan*/  errno_t ;
struct TYPE_10__ {int len; } ;
struct TYPE_11__ {size_t m_len; int m_flags; TYPE_1__ m_pkthdr; struct TYPE_11__* m_next; int /*<<< orphan*/  m_type; } ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENOBUFS ; 
 void* MIN (scalar_t__,size_t) ; 
 size_t MINCLSIZE ; 
 scalar_t__ MLEN ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  bcopy (char const*,char*,unsigned int) ; 
 TYPE_2__* m_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* m_getclr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ mbuf_data (TYPE_2__*) ; 
 scalar_t__ mbuf_maxlen (TYPE_2__*) ; 
 int /*<<< orphan*/  mbuf_mclget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 scalar_t__ mbuf_trailingspace (TYPE_2__*) ; 

errno_t
mbuf_copyback(
	mbuf_t		m,
	size_t		off,
	size_t		len,
	const void	*data,
	mbuf_how_t	how)
{
	size_t	mlen;
	mbuf_t	m_start = m;
	mbuf_t	n;
	int		totlen = 0;
	errno_t		result = 0;
	const char	*cp = data;

	if (m == NULL || len == 0 || data == NULL)
		return (EINVAL);

	while (off > (mlen = m->m_len)) {
		off -= mlen;
		totlen += mlen;
		if (m->m_next == 0) {
			n = m_getclr(how, m->m_type);
			if (n == 0) {
				result = ENOBUFS;
				goto out;
			}
			n->m_len = MIN(MLEN, len + off);
			m->m_next = n;
		}
		m = m->m_next;
	}

	while (len > 0) {
		mlen = MIN(m->m_len - off, len);
		if (mlen < len && m->m_next == NULL &&
		    mbuf_trailingspace(m) > 0) {
			size_t	grow = MIN(mbuf_trailingspace(m), len - mlen);
			mlen += grow;
			m->m_len += grow;
		}
		bcopy(cp, off + (char *)mbuf_data(m), (unsigned)mlen);
		cp += mlen;
		len -= mlen;
		mlen += off;
		off = 0;
		totlen += mlen;
		if (len == 0)
			break;
		if (m->m_next == 0) {
			n = m_get(how, m->m_type);
			if (n == NULL) {
				result = ENOBUFS;
				goto out;
			}
			if (len > MINCLSIZE) {
				/*
				 * cluster allocation failure is okay,
				 * we can grow chain
				 */
				mbuf_mclget(how, m->m_type, &n);
			}
			n->m_len = MIN(mbuf_maxlen(n), len);
			m->m_next = n;
		}
		m = m->m_next;
	}

out:
	if ((m_start->m_flags & M_PKTHDR) && (m_start->m_pkthdr.len < totlen))
		m_start->m_pkthdr.len = totlen;

	return (result);
}