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
struct mbuf {int m_len; int m_flags; int m_data; struct mbuf* m_next; int /*<<< orphan*/  m_type; } ;
struct TYPE_2__ {int /*<<< orphan*/  ip6s_pulldown_alloc; int /*<<< orphan*/  ip6s_pulldown_copy; int /*<<< orphan*/  ip6s_pullup2_copy; int /*<<< orphan*/  ip6s_pullup2_alloc; int /*<<< orphan*/  ip6s_pullup2; int /*<<< orphan*/  ip6s_pullup2_fail; int /*<<< orphan*/  ip6s_pullup_copy; int /*<<< orphan*/  ip6s_pullup_alloc; int /*<<< orphan*/  ip6s_pullup; int /*<<< orphan*/  ip6s_pullup_fail; int /*<<< orphan*/  ip6s_pulldown; } ;

/* Variables and functions */
 int MCLBYTES ; 
 int /*<<< orphan*/  MCLGET (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MGET (struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MHLEN ; 
 int /*<<< orphan*/  M_DONTWAIT ; 
 int M_EXT ; 
 int M_LEADINGSPACE (struct mbuf*) ; 
 int M_TRAILINGSPACE (struct mbuf*) ; 
 int /*<<< orphan*/  bcopy (scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  caddr_t ; 
 TYPE_1__ ip6stat ; 
 int /*<<< orphan*/  m_adj (struct mbuf*,int) ; 
 int /*<<< orphan*/  m_copydata (struct mbuf*,int /*<<< orphan*/ ,int,scalar_t__) ; 
 struct mbuf* m_copym (struct mbuf*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/ * m_get_ext_free (struct mbuf*) ; 
 scalar_t__ m_mclhasreference (struct mbuf*) ; 
 scalar_t__ mtod (struct mbuf*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  panic (char*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

struct mbuf *
m_pulldown(struct mbuf *m, int off, int len, int *offp)
{
	struct mbuf *n = NULL, *o = NULL;
	int hlen = 0, tlen = 0, olen = 0;
	int sharedcluster = 0;
#if defined(PULLDOWN_STAT) && INET6
	static struct mbuf *prev = NULL;
	int prevlen = 0, prevmlen = 0;
#endif

	/* check invalid arguments. */
	if (m == NULL)
		panic("m == NULL in m_pulldown()");
	if (len > MCLBYTES) {
		m_freem(m);
		return NULL;	/* impossible */
	}

#if defined(PULLDOWN_STAT) && INET6
	ip6stat.ip6s_pulldown++;
#endif

#if defined(PULLDOWN_STAT) && INET6
	/* statistics for m_pullup */
	ip6stat.ip6s_pullup++;
	if (off + len > MHLEN)
		ip6stat.ip6s_pullup_fail++;
	else {
		int dlen, mlen;

		dlen = (prev == m) ? prevlen : m->m_len;
		mlen = (prev == m) ? prevmlen : m->m_len + M_TRAILINGSPACE(m);

		if (dlen >= off + len)
			ip6stat.ip6s_pullup--; /* call will not be made! */
		else if ((m->m_flags & M_EXT) != 0) {
			ip6stat.ip6s_pullup_alloc++;
			ip6stat.ip6s_pullup_copy++;
		} else {
			if (mlen >= off + len)
				ip6stat.ip6s_pullup_copy++;
			else {
				ip6stat.ip6s_pullup_alloc++;
				ip6stat.ip6s_pullup_copy++;
			}
		}

		prevlen = off + len;
		prevmlen = MHLEN;
	}

	/* statistics for m_pullup2 */
	ip6stat.ip6s_pullup2++;
	if (off + len > MCLBYTES)
		ip6stat.ip6s_pullup2_fail++;
	else {
		int dlen, mlen;

		dlen = (prev == m) ? prevlen : m->m_len;
		mlen = (prev == m) ? prevmlen : m->m_len + M_TRAILINGSPACE(m);
		prevlen = off + len;
		prevmlen = mlen;

		if (dlen >= off + len)
			ip6stat.ip6s_pullup2--; /* call will not be made! */
		else if ((m->m_flags & M_EXT) != 0) {
			ip6stat.ip6s_pullup2_alloc++;
			ip6stat.ip6s_pullup2_copy++;
			prevmlen = (off + len > MHLEN) ? MCLBYTES : MHLEN;
		} else {
			if (mlen >= off + len)
				ip6stat.ip6s_pullup2_copy++;
			else {
				ip6stat.ip6s_pullup2_alloc++;
				ip6stat.ip6s_pullup2_copy++;
				prevmlen = (off + len > MHLEN) ? MCLBYTES
							       : MHLEN;
			}
		}
	}

	prev = m;
#endif

#ifdef PULLDOWN_DEBUG
    {
	struct mbuf *t;
	printf("before:");
	for (t = m; t; t = t->m_next)
		printf(" %d", t->m_len);
	printf("\n");
    }
#endif
	n = m;

	/*
	 * Iterate and make n point to the mbuf
	 * within which the first byte at length
	 * offset is contained from the start of
	 * mbuf chain.
	 */
	while (n != NULL && off > 0) {
		if (n->m_len > off)
			break;
		off -= n->m_len;
		n = n->m_next;
	}

	/* be sure to point non-empty mbuf */
	while (n != NULL && n->m_len == 0)
		n = n->m_next;

	if (!n) {
		m_freem(m);
		return NULL;	/* mbuf chain too short */
	}

	/*
	 * the target data is on <n, off>.
	 * if we got enough data on the mbuf "n", we're done.
	 *
	 * It should be noted, that we should only do this either
	 * when offset is 0, i.e. data is pointing to the start
	 * or when the caller specifies an out argument to get
	 * the offset value in the mbuf to work with data pointer
	 * correctly.
	 *
	 * If offset is not 0 and caller did not provide out-argument
	 * to get offset, we should split the mbuf even when the length
	 * is contained in current mbuf.
	 */
	if ((off == 0 || offp) && len <= n->m_len - off)
		goto ok;

#if defined(PULLDOWN_STAT) && INET6
	ip6stat.ip6s_pulldown_copy++;
#endif

	/*
	 * when len <= n->m_len - off and off != 0, it is a special case.
	 * len bytes from <n, off> sits in single mbuf, but the caller does
	 * not like the starting position (off).
	 * chop the current mbuf into two pieces, set off to 0.
	 */
	if (len <= n->m_len - off) {
		o = m_copym(n, off, n->m_len - off, M_DONTWAIT);
		if (o == NULL) {
			m_freem(m);
			return NULL;	/* ENOBUFS */
		}
		n->m_len = off;
		o->m_next = n->m_next;
		n->m_next = o;
		n = n->m_next;
		off = 0;
		goto ok;
	}

	/*
	 * we need to take hlen from <n, off> and tlen from <n->m_next, 0>,
	 * and construct contiguous mbuf with m_len == len.
	 * note that hlen + tlen == len, and tlen > 0.
	 *
	 * Read these variables as head length and tail length
	 */
	hlen = n->m_len - off;
	tlen = len - hlen;

	/*
	 * ensure that we have enough trailing data on mbuf chain.
	 * if not, we can do nothing about the chain.
	 */
	olen = 0;
	for (o = n->m_next; o != NULL; o = o->m_next)
		olen += o->m_len;
	if (hlen + olen < len) {
		m_freem(m);
		return NULL;	/* mbuf chain too short */
	}

	/*
	 * easy cases first.
	 * we need to use m_copydata() to get data from <n->m_next, 0>.
	 */
	if ((n->m_flags & M_EXT) == 0)
		sharedcluster = 0;
	else {
		if (m_get_ext_free(n) != NULL)
			sharedcluster = 1;
		else if (m_mclhasreference(n))
			sharedcluster = 1;
		else
			sharedcluster = 0;
	}

	/*
	 * If we have enough space left in current mbuf to accomodate
	 * tail length, copy tail length worth of data starting with next mbuf
	 * and adjust the length of next one accordingly.
	 */
	if ((off == 0 || offp) && M_TRAILINGSPACE(n) >= tlen
	 && !sharedcluster) {
		m_copydata(n->m_next, 0, tlen, mtod(n, caddr_t) + n->m_len);
		n->m_len += tlen;
		m_adj(n->m_next, tlen);
		goto ok;
	}

	/*
	 * If have enough leading space in next mbuf to accomodate head length
	 * of current mbuf, and total resulting length of next mbuf is greater
	 * than or equal to requested len bytes, then just copy hlen from
	 * current to the next one and adjust sizes accordingly.
	 */
	if ((off == 0 || offp) && M_LEADINGSPACE(n->m_next) >= hlen &&
	    (n->m_next->m_len + hlen) >= len && !sharedcluster) {
		n->m_next->m_data -= hlen;
		n->m_next->m_len += hlen;
		bcopy(mtod(n, caddr_t) + off, mtod(n->m_next, caddr_t), hlen);
		n->m_len -= hlen;
		n = n->m_next;
		off = 0;
		goto ok;
	}

	/*
	 * now, we need to do the hard way.  don't m_copy as there's no room
	 * on both end.
	 */
#if defined(PULLDOWN_STAT) && INET6
	ip6stat.ip6s_pulldown_alloc++;
#endif
	MGET(o, M_DONTWAIT, m->m_type);
	if (o == NULL) {
		m_freem(m);
		return NULL;	/* ENOBUFS */
	}
	if (len > MHLEN) {	/* use MHLEN just for safety */
		MCLGET(o, M_DONTWAIT);
		if ((o->m_flags & M_EXT) == 0) {
			m_freem(m);
			m_free(o);
			return NULL;	/* ENOBUFS */
		}
	}
	/* get hlen from <n, off> into <o, 0> */
	o->m_len = hlen;
	bcopy(mtod(n, caddr_t) + off, mtod(o, caddr_t), hlen);
	n->m_len -= hlen;
	/* get tlen from <n->m_next, 0> into <o, hlen> */
	m_copydata(n->m_next, 0, tlen, mtod(o, caddr_t) + o->m_len);
	o->m_len += tlen;
	m_adj(n->m_next, tlen);
	o->m_next = n->m_next;
	n->m_next = o;
	n = o;
	off = 0;

ok:
#ifdef PULLDOWN_DEBUG
    {
	struct mbuf *t;
	printf("after:");
	for (t = m; t; t = t->m_next)
		printf("%c%d", t == n ? '*' : ' ', t->m_len);
	printf(" (off=%d)\n", off);
    }
#endif
	if (offp)
		*offp = off;
	return n;
}