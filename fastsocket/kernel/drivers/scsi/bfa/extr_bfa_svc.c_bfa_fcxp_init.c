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
struct bfa_fcxp_s {int /*<<< orphan*/  rsp_sgpg_q; int /*<<< orphan*/  rsp_sglen_cbfn; int /*<<< orphan*/  rsp_sga_cbfn; int /*<<< orphan*/  nrsp_sgles; int /*<<< orphan*/  use_irspbuf; int /*<<< orphan*/  req_sgpg_q; int /*<<< orphan*/  req_sglen_cbfn; int /*<<< orphan*/  req_sga_cbfn; int /*<<< orphan*/  nreq_sgles; int /*<<< orphan*/  use_ireqbuf; void* caller; int /*<<< orphan*/  fcxp_tag; } ;
typedef  int /*<<< orphan*/  bfa_fcxp_get_sglen_t ;
typedef  int /*<<< orphan*/  bfa_fcxp_get_sgaddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_fcxp_init_reqrsp (struct bfa_fcxp_s*,struct bfa_s*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_fcxp_init(struct bfa_fcxp_s *fcxp,
	       void *caller, struct bfa_s *bfa, int nreq_sgles,
	       int nrsp_sgles, bfa_fcxp_get_sgaddr_t req_sga_cbfn,
	       bfa_fcxp_get_sglen_t req_sglen_cbfn,
	       bfa_fcxp_get_sgaddr_t rsp_sga_cbfn,
	       bfa_fcxp_get_sglen_t rsp_sglen_cbfn)
{

	WARN_ON(bfa == NULL);

	bfa_trc(bfa, fcxp->fcxp_tag);

	fcxp->caller = caller;

	bfa_fcxp_init_reqrsp(fcxp, bfa,
		&fcxp->use_ireqbuf, &fcxp->nreq_sgles, &fcxp->req_sga_cbfn,
		&fcxp->req_sglen_cbfn, &fcxp->req_sgpg_q,
		nreq_sgles, req_sga_cbfn, req_sglen_cbfn);

	bfa_fcxp_init_reqrsp(fcxp, bfa,
		&fcxp->use_irspbuf, &fcxp->nrsp_sgles, &fcxp->rsp_sga_cbfn,
		&fcxp->rsp_sglen_cbfn, &fcxp->rsp_sgpg_q,
		nrsp_sgles, rsp_sga_cbfn, rsp_sglen_cbfn);

}