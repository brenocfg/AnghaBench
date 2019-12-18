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
typedef  int u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int MAX (int,int) ; 
 int MBIGCL_LOWAT ; 
 int MBUF_GROWTH_NORMAL_THRESH ; 
 int MB_GROWTH_AGGRESSIVE ; 
 int MB_GROWTH_NORMAL ; 
 int /*<<< orphan*/  MC_16KCL ; 
 int /*<<< orphan*/  MC_BIGCL ; 
 int /*<<< orphan*/  MC_CL ; 
 int /*<<< orphan*/  MC_MBUF ; 
 int NCLPBGSHIFT ; 
 int NCLPJCLSHIFT ; 
 int NMBPCLSHIFT ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int m_infree (int /*<<< orphan*/ ) ; 
 int m_maxlimit (int /*<<< orphan*/ ) ; 
 size_t m_maxsize (int /*<<< orphan*/ ) ; 
 int m_minlimit (int /*<<< orphan*/ ) ; 
 int m_total (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mbuf_mlock ; 
 int /*<<< orphan*/  mbwdog_logger (char*,int,int,int,int) ; 
 int nclusters ; 
 int njcl ; 

__attribute__((used)) static int
m_howmany(int num, size_t bufsize)
{
	int i = 0, j = 0;
	u_int32_t m_mbclusters, m_clusters, m_bigclusters, m_16kclusters;
	u_int32_t m_mbfree, m_clfree, m_bigclfree, m_16kclfree;
	u_int32_t sumclusters, freeclusters;
	u_int32_t percent_pool, percent_kmem;
	u_int32_t mb_growth, mb_growth_thresh;

	VERIFY(bufsize == m_maxsize(MC_BIGCL) ||
	    bufsize == m_maxsize(MC_16KCL));

	LCK_MTX_ASSERT(mbuf_mlock, LCK_MTX_ASSERT_OWNED);

	/* Numbers in 2K cluster units */
	m_mbclusters = m_total(MC_MBUF) >> NMBPCLSHIFT;
	m_clusters = m_total(MC_CL);
	m_bigclusters = m_total(MC_BIGCL) << NCLPBGSHIFT;
	m_16kclusters = m_total(MC_16KCL);
	sumclusters = m_mbclusters + m_clusters + m_bigclusters;

	m_mbfree = m_infree(MC_MBUF) >> NMBPCLSHIFT;
	m_clfree = m_infree(MC_CL);
	m_bigclfree = m_infree(MC_BIGCL) << NCLPBGSHIFT;
	m_16kclfree = m_infree(MC_16KCL);
	freeclusters = m_mbfree + m_clfree + m_bigclfree;

	/* Bail if we've maxed out the mbuf memory map */
	if ((bufsize == m_maxsize(MC_BIGCL) && sumclusters >= nclusters) ||
	    (njcl > 0 && bufsize == m_maxsize(MC_16KCL) &&
	    (m_16kclusters << NCLPJCLSHIFT) >= njcl)) {
		mbwdog_logger("maxed out nclusters (%u >= %u) or njcl (%u >= %u)",
		    sumclusters, nclusters,
		    (m_16kclusters << NCLPJCLSHIFT), njcl);
		return (0);
	}

	if (bufsize == m_maxsize(MC_BIGCL)) {
		/* Under minimum */
		if (m_bigclusters < m_minlimit(MC_BIGCL))
			return (m_minlimit(MC_BIGCL) - m_bigclusters);

		percent_pool =
		    ((sumclusters - freeclusters) * 100) / sumclusters;
		percent_kmem = (sumclusters * 100) / nclusters;

		/*
		 * If a light/normal user, grow conservatively (75%)
		 * If a heavy user, grow aggressively (50%)
		 */
		if (percent_kmem < MBUF_GROWTH_NORMAL_THRESH)
			mb_growth = MB_GROWTH_NORMAL;
		else
			mb_growth = MB_GROWTH_AGGRESSIVE;

		if (percent_kmem < 5) {
			/* For initial allocations */
			i = num;
		} else {
			/* Return if >= MBIGCL_LOWAT clusters available */
			if (m_infree(MC_BIGCL) >= MBIGCL_LOWAT &&
			    m_total(MC_BIGCL) >=
			    MBIGCL_LOWAT + m_minlimit(MC_BIGCL))
				return (0);

			/* Ensure at least num clusters are accessible */
			if (num >= m_infree(MC_BIGCL))
				i = num - m_infree(MC_BIGCL);
			if (num > m_total(MC_BIGCL) - m_minlimit(MC_BIGCL))
				j = num - (m_total(MC_BIGCL) -
				    m_minlimit(MC_BIGCL));

			i = MAX(i, j);

			/*
			 * Grow pool if percent_pool > 75 (normal growth)
			 * or percent_pool > 50 (aggressive growth).
			 */
			mb_growth_thresh = 100 - (100 / (1 << mb_growth));
			if (percent_pool > mb_growth_thresh)
				j = ((sumclusters + num) >> mb_growth) -
				    freeclusters;
			i = MAX(i, j);
		}

		/* Check to ensure we didn't go over limits */
		if (i + m_bigclusters >= m_maxlimit(MC_BIGCL))
			i = m_maxlimit(MC_BIGCL) - m_bigclusters;
		if ((i << 1) + sumclusters >= nclusters)
			i = (nclusters - sumclusters) >> 1;
		VERIFY((m_total(MC_BIGCL) + i) <= m_maxlimit(MC_BIGCL));
		VERIFY(sumclusters + (i << 1) <= nclusters);

	} else { /* 16K CL */
		VERIFY(njcl > 0);
		/* Ensure at least num clusters are available */
		if (num >= m_16kclfree)
			i = num - m_16kclfree;

		/* Always grow 16KCL pool aggressively */
		if (((m_16kclusters + num) >> 1) > m_16kclfree)
			j = ((m_16kclusters + num) >> 1) - m_16kclfree;
		i = MAX(i, j);

		/* Check to ensure we don't go over limit */
		if ((i + m_total(MC_16KCL)) >= m_maxlimit(MC_16KCL))
			i = m_maxlimit(MC_16KCL) - m_total(MC_16KCL);
	}
	return (i);
}