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
struct bfi_lps_logout_req_s {int /*<<< orphan*/  mh; int /*<<< orphan*/  port_name; int /*<<< orphan*/  fw_tag; } ;
struct bfa_lps_s {int /*<<< orphan*/  reqq; int /*<<< orphan*/  bfa; int /*<<< orphan*/  pwwn; int /*<<< orphan*/  fw_tag; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFI_LPS_H2I_LOGOUT_REQ ; 
 int /*<<< orphan*/  BFI_MC_LPS ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  bfa_fn_lpu (int /*<<< orphan*/ ) ; 
 struct bfi_lps_logout_req_s* bfa_reqq_next (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_reqq_produce (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfi_h2i_set (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
bfa_lps_send_logout(struct bfa_lps_s *lps)
{
	struct bfi_lps_logout_req_s *m;

	m = bfa_reqq_next(lps->bfa, lps->reqq);
	WARN_ON(!m);

	bfi_h2i_set(m->mh, BFI_MC_LPS, BFI_LPS_H2I_LOGOUT_REQ,
		bfa_fn_lpu(lps->bfa));

	m->fw_tag = lps->fw_tag;
	m->port_name = lps->pwwn;
	bfa_reqq_produce(lps->bfa, lps->reqq, m->mh);
}