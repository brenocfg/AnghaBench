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
struct bfa_s {int dummy; } ;
struct bfa_lps_s {int /*<<< orphan*/  qe; } ;
struct bfa_lps_mod_s {int /*<<< orphan*/  lps_active_q; int /*<<< orphan*/  lps_free_q; } ;

/* Variables and functions */
 struct bfa_lps_mod_s* BFA_LPS_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_lps_sm_init ; 
 int /*<<< orphan*/  bfa_q_deq (int /*<<< orphan*/ *,struct bfa_lps_s**) ; 
 int /*<<< orphan*/  bfa_sm_set_state (struct bfa_lps_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

struct bfa_lps_s  *
bfa_lps_alloc(struct bfa_s *bfa)
{
	struct bfa_lps_mod_s	*mod = BFA_LPS_MOD(bfa);
	struct bfa_lps_s	*lps = NULL;

	bfa_q_deq(&mod->lps_free_q, &lps);

	if (lps == NULL)
		return NULL;

	list_add_tail(&lps->qe, &mod->lps_active_q);

	bfa_sm_set_state(lps, bfa_lps_sm_init);
	return lps;
}