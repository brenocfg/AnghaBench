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
typedef  int /*<<< orphan*/  u_int16_t ;
struct mbuf {scalar_t__ m_type; } ;
typedef  int /*<<< orphan*/  mcache_obj_t ;
typedef  int /*<<< orphan*/  mcache_audit_t ;

/* Variables and functions */
 int /*<<< orphan*/  MC_MBUF ; 
 int /*<<< orphan*/  MRANGE (struct mbuf*) ; 
 int /*<<< orphan*/  MT_FREE ; 
 int /*<<< orphan*/  mcache_dump_mca (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * mcl_audit_buf2mca (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  panic (char*,struct mbuf*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mcl_audit_mcheck_panic(struct mbuf *m)
{
	mcache_audit_t *mca;

	MRANGE(m);
	mca = mcl_audit_buf2mca(MC_MBUF, (mcache_obj_t *)m);

	panic("mcl_audit: freed mbuf %p with type 0x%x (instead of 0x%x)\n%s\n",
	    m, (u_int16_t)m->m_type, MT_FREE, mcache_dump_mca(mca));
	/* NOTREACHED */
}