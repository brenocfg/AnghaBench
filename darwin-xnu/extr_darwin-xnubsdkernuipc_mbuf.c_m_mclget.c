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
struct TYPE_2__ {int /*<<< orphan*/ * ext_buf; } ;
struct mbuf {TYPE_1__ m_ext; } ;
struct ext_ref {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MBUF_CL_INIT (struct mbuf*,int /*<<< orphan*/ *,struct ext_ref*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MSLEEPF (int) ; 
 int /*<<< orphan*/ * m_mclalloc (int) ; 
 struct ext_ref* mcache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mcache_free (int /*<<< orphan*/ ,struct ext_ref*) ; 
 int /*<<< orphan*/  ref_cache ; 

struct mbuf *
m_mclget(struct mbuf *m, int wait)
{
	struct ext_ref *rfa;

	if ((rfa = mcache_alloc(ref_cache, MSLEEPF(wait))) == NULL)
		return (m);

	m->m_ext.ext_buf = m_mclalloc(wait);
	if (m->m_ext.ext_buf != NULL) {
		MBUF_CL_INIT(m, m->m_ext.ext_buf, rfa, 1, 0);
	} else {
		mcache_free(ref_cache, rfa);
	}
	return (m);
}