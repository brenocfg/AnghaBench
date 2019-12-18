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
struct pf_pooladdr {int /*<<< orphan*/  kif; int /*<<< orphan*/  addr; } ;
struct pf_palist {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PFI_KIF_REF_RULE ; 
 struct pf_pooladdr* TAILQ_FIRST (struct pf_palist*) ; 
 int /*<<< orphan*/  TAILQ_REMOVE (struct pf_palist*,struct pf_pooladdr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  entries ; 
 int /*<<< orphan*/  pf_pooladdr_pl ; 
 int /*<<< orphan*/  pf_tbladdr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfi_dynaddr_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pfi_kif_unref (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pool_put (int /*<<< orphan*/ *,struct pf_pooladdr*) ; 

__attribute__((used)) static void
pf_empty_pool(struct pf_palist *poola)
{
	struct pf_pooladdr	*empty_pool_pa;

	while ((empty_pool_pa = TAILQ_FIRST(poola)) != NULL) {
		pfi_dynaddr_remove(&empty_pool_pa->addr);
		pf_tbladdr_remove(&empty_pool_pa->addr);
		pfi_kif_unref(empty_pool_pa->kif, PFI_KIF_REF_RULE);
		TAILQ_REMOVE(poola, empty_pool_pa, entries);
		pool_put(&pf_pooladdr_pl, empty_pool_pa);
	}
}