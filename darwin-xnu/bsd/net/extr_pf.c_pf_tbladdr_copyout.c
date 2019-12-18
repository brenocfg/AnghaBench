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
struct pfr_ktable {int pfrkt_flags; int pfrkt_cnt; struct pfr_ktable* pfrkt_root; } ;
struct TYPE_2__ {int tblcnt; struct pfr_ktable* tbl; } ;
struct pf_addr_wrap {scalar_t__ type; TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 int PFR_TFLAG_ACTIVE ; 
 scalar_t__ PF_ADDR_TABLE ; 
 int /*<<< orphan*/  pf_lock ; 

void
pf_tbladdr_copyout(struct pf_addr_wrap *aw)
{
	struct pfr_ktable *kt = aw->p.tbl;

	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (aw->type != PF_ADDR_TABLE || kt == NULL)
		return;
	if (!(kt->pfrkt_flags & PFR_TFLAG_ACTIVE) && kt->pfrkt_root != NULL)
		kt = kt->pfrkt_root;
	aw->p.tbl = NULL;
	aw->p.tblcnt = (kt->pfrkt_flags & PFR_TFLAG_ACTIVE) ?
	    kt->pfrkt_cnt : -1;
}