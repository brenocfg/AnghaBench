#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct pf_ruleset {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  tblname; } ;
struct TYPE_3__ {int /*<<< orphan*/ * tbl; } ;
struct pf_addr_wrap {scalar_t__ type; TYPE_2__ v; TYPE_1__ p; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCK_MTX_ASSERT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LCK_MTX_ASSERT_OWNED ; 
 scalar_t__ PF_ADDR_TABLE ; 
 int /*<<< orphan*/  pf_lock ; 
 int /*<<< orphan*/ * pfr_attach_table (struct pf_ruleset*,int /*<<< orphan*/ ) ; 

int
pf_tbladdr_setup(struct pf_ruleset *rs, struct pf_addr_wrap *aw)
{
	LCK_MTX_ASSERT(pf_lock, LCK_MTX_ASSERT_OWNED);

	if (aw->type != PF_ADDR_TABLE)
		return (0);
	if ((aw->p.tbl = pfr_attach_table(rs, aw->v.tblname)) == NULL)
		return (1);
	return (0);
}