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
struct mbuf {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_INIT (struct mbuf*,int,short) ; 
 int MCR_NOSLEEP ; 
 int MCR_TRYHARD ; 
 int /*<<< orphan*/  MC_MBUF ; 
 int MSLEEPF (int) ; 
 int /*<<< orphan*/  MT_FREE ; 
 int /*<<< orphan*/  m_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_free (struct mbuf*) ; 
 scalar_t__ mac_init_mbuf (struct mbuf*,int) ; 
 struct mbuf* mcache_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mtype_stat_dec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mtype_stat_inc (short) ; 

__attribute__((used)) static inline struct mbuf *
m_get_common(int wait, short type, int hdr)
{
	struct mbuf *m;
	int mcflags = MSLEEPF(wait);

	/* Is this due to a non-blocking retry?  If so, then try harder */
	if (mcflags & MCR_NOSLEEP)
		mcflags |= MCR_TRYHARD;

	m = mcache_alloc(m_cache(MC_MBUF), mcflags);
	if (m != NULL) {
		MBUF_INIT(m, hdr, type);
		mtype_stat_inc(type);
		mtype_stat_dec(MT_FREE);
#if CONFIG_MACF_NET
		if (hdr && mac_init_mbuf(m, wait) != 0) {
			m_free(m);
			return (NULL);
		}
#endif /* MAC_NET */
	}
	return (m);
}