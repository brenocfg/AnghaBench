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
typedef  int /*<<< orphan*/  u_int ;
struct TYPE_2__ {int /*<<< orphan*/  ext_size; int /*<<< orphan*/ * ext_buf; } ;
struct mbuf {int m_flags; int m_type; TYPE_1__ m_ext; } ;
struct ext_ref {int dummy; } ;
typedef  int /*<<< orphan*/  m_ext_free_func_t ;
typedef  int /*<<< orphan*/ * caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXTF_PAIRED ; 
 int /*<<< orphan*/  MBUF_INIT (struct mbuf*,int,int) ; 
 int MBUF_IS_PAIRED (struct mbuf*) ; 
 int /*<<< orphan*/  MEXT_INIT (struct mbuf*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct ext_ref*,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct mbuf*) ; 
 scalar_t__ MEXT_MINREF (struct mbuf*) ; 
 scalar_t__ MEXT_PREF (struct mbuf*) ; 
 int /*<<< orphan*/  MEXT_PRIV (struct mbuf*) ; 
 scalar_t__ MEXT_REF (struct mbuf*) ; 
 int M_PKTHDR ; 
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  m_get_ext_free (struct mbuf*) ; 
 struct ext_ref* m_get_rfa (struct mbuf*) ; 

void
m_ext_paired_activate(struct mbuf *m)
{
	struct ext_ref *rfa;
	int hdr, type;
	caddr_t extbuf;
	m_ext_free_func_t extfree;
	u_int extsize;

	VERIFY(MBUF_IS_PAIRED(m));
	VERIFY(MEXT_REF(m) == MEXT_MINREF(m));
	VERIFY(MEXT_PREF(m) == MEXT_MINREF(m));

	hdr = (m->m_flags & M_PKTHDR);
	type = m->m_type;
	extbuf = m->m_ext.ext_buf;
	extfree = m_get_ext_free(m);
	extsize = m->m_ext.ext_size;
	rfa = m_get_rfa(m);

	VERIFY(extbuf != NULL && rfa != NULL);

	/*
	 * Safe to reinitialize packet header tags, since it's
	 * already taken care of at m_free() time.  Similar to
	 * what's done in m_clattach() for the cluster.  Bump
	 * up MEXT_PREF to indicate activation.
	 */
	MBUF_INIT(m, hdr, type);
	MEXT_INIT(m, extbuf, extsize, extfree, (caddr_t)m, rfa,
	    1, 1, 2, EXTF_PAIRED, MEXT_PRIV(m), m);
}