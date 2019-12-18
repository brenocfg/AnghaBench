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
struct bfa_rport_s {int /*<<< orphan*/  qe; int /*<<< orphan*/  bfa; } ;
struct bfa_rport_mod_s {int /*<<< orphan*/  rp_free_q; int /*<<< orphan*/  rp_active_q; } ;

/* Variables and functions */
 struct bfa_rport_mod_s* BFA_RPORT_MOD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_q_is_on_q (int /*<<< orphan*/ *,struct bfa_rport_s*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
bfa_rport_free(struct bfa_rport_s *rport)
{
	struct bfa_rport_mod_s *mod = BFA_RPORT_MOD(rport->bfa);

	WARN_ON(!bfa_q_is_on_q(&mod->rp_active_q, rport));
	list_del(&rport->qe);
	list_add_tail(&rport->qe, &mod->rp_free_q);
}