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
typedef  scalar_t__ u16 ;
struct bfa_ioim_s {scalar_t__ nsges; int /*<<< orphan*/  sgpg_q; int /*<<< orphan*/  sgpg; scalar_t__ nsgpgs; TYPE_1__* iosp; int /*<<< orphan*/  bfa; } ;
typedef  int /*<<< orphan*/  bfa_boolean_t ;
struct TYPE_2__ {int /*<<< orphan*/  sgpg_wqe; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FALSE ; 
 scalar_t__ BFA_SGPG_NPAGE (scalar_t__) ; 
 scalar_t__ BFA_STATUS_OK ; 
 int /*<<< orphan*/  BFA_TRUE ; 
 scalar_t__ BFI_SGE_INLINE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_first (int /*<<< orphan*/ *) ; 
 scalar_t__ bfa_sgpg_malloc (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  bfa_sgpg_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static bfa_boolean_t
bfa_ioim_sgpg_alloc(struct bfa_ioim_s *ioim)
{
	u16	nsgpgs;

	WARN_ON(ioim->nsges <= BFI_SGE_INLINE);

	/*
	 * allocate SG pages needed
	 */
	nsgpgs = BFA_SGPG_NPAGE(ioim->nsges);
	if (!nsgpgs)
		return BFA_TRUE;

	if (bfa_sgpg_malloc(ioim->bfa, &ioim->sgpg_q, nsgpgs)
	    != BFA_STATUS_OK) {
		bfa_sgpg_wait(ioim->bfa, &ioim->iosp->sgpg_wqe, nsgpgs);
		return BFA_FALSE;
	}

	ioim->nsgpgs = nsgpgs;
	ioim->sgpg = bfa_q_first(&ioim->sgpg_q);

	return BFA_TRUE;
}