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
typedef  int u16 ;
struct list_head {int dummy; } ;
struct bfa_s {int dummy; } ;
struct bfa_fcxp_mod_s {int num_fcxps; int /*<<< orphan*/  fcxp_rsp_unused_q; int /*<<< orphan*/  fcxp_rsp_free_q; int /*<<< orphan*/  fcxp_req_unused_q; int /*<<< orphan*/  fcxp_req_free_q; } ;

/* Variables and functions */
 struct bfa_fcxp_mod_s* BFA_FCXP_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_q_deq_tail (int /*<<< orphan*/ *,struct list_head**) ; 
 int /*<<< orphan*/  list_add_tail (struct list_head*,int /*<<< orphan*/ *) ; 

void
bfa_fcxp_res_recfg(struct bfa_s *bfa, u16 num_fcxp_fw)
{
	struct bfa_fcxp_mod_s	*mod = BFA_FCXP_MOD(bfa);
	struct list_head	*qe;
	int	i;

	for (i = 0; i < (mod->num_fcxps - num_fcxp_fw); i++) {
		if (i < ((mod->num_fcxps - num_fcxp_fw) / 2)) {
			bfa_q_deq_tail(&mod->fcxp_req_free_q, &qe);
			list_add_tail(qe, &mod->fcxp_req_unused_q);
		} else {
			bfa_q_deq_tail(&mod->fcxp_rsp_free_q, &qe);
			list_add_tail(qe, &mod->fcxp_rsp_unused_q);
		}
	}
}