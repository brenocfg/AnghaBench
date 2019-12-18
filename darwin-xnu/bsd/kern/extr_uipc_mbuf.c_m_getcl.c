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
typedef  int /*<<< orphan*/  u_int16_t ;
struct TYPE_2__ {void* ext_buf; } ;
struct mbuf {scalar_t__ m_type; scalar_t__ m_flags; TYPE_1__ m_ext; } ;
struct ext_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  MBUF_CL_INIT (struct mbuf*,void*,struct ext_ref*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MBUF_INIT (struct mbuf*,int,int) ; 
 scalar_t__ MBUF_IS_COMPOSITE (struct mbuf*) ; 
 int MCR_NOSLEEP ; 
 int MCR_TRYHARD ; 
 int /*<<< orphan*/  MC_MBUF_CL ; 
 int /*<<< orphan*/  MEXT_FLAGS (struct mbuf*) ; 
 int MSLEEPF (int) ; 
 scalar_t__ MT_FREE ; 
 scalar_t__ M_EXT ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_freem (struct mbuf*) ; 
 int /*<<< orphan*/ * m_get_ext_free (struct mbuf*) ; 
 struct ext_ref* m_get_rfa (struct mbuf*) ; 
 scalar_t__ mac_init_mbuf (struct mbuf*,int) ; 
 struct mbuf* mcache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtype_stat_dec (scalar_t__) ; 
 int /*<<< orphan*/  mtype_stat_inc (int) ; 

struct mbuf *
m_getcl(int wait, int type, int flags)
{
	struct mbuf *m;
	int mcflags = MSLEEPF(wait);
	int hdr = (flags & M_PKTHDR);

	/* Is this due to a non-blocking retry?  If so, then try harder */
	if (mcflags & MCR_NOSLEEP)
		mcflags |= MCR_TRYHARD;

	m = mcache_alloc(m_cache(MC_MBUF_CL), mcflags);
	if (m != NULL) {
		u_int16_t flag;
		struct ext_ref *rfa;
		void *cl;

		VERIFY(m->m_type == MT_FREE && m->m_flags == M_EXT);
		cl = m->m_ext.ext_buf;
		rfa = m_get_rfa(m);

		ASSERT(cl != NULL && rfa != NULL);
		VERIFY(MBUF_IS_COMPOSITE(m) && m_get_ext_free(m) == NULL);

		flag = MEXT_FLAGS(m);

		MBUF_INIT(m, hdr, type);
		MBUF_CL_INIT(m, cl, rfa, 1, flag);

		mtype_stat_inc(type);
		mtype_stat_dec(MT_FREE);
#if CONFIG_MACF_NET
		if (hdr && mac_init_mbuf(m, wait) != 0) {
			m_freem(m);
			return (NULL);
		}
#endif /* MAC_NET */
	}
	return (m);
}