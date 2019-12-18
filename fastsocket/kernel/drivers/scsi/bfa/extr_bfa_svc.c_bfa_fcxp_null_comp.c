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
typedef  int /*<<< orphan*/  u32 ;
struct fchs_s {int dummy; } ;
struct bfa_fcxp_s {int dummy; } ;
typedef  int /*<<< orphan*/  bfa_status_t ;

/* Variables and functions */

__attribute__((used)) static void
bfa_fcxp_null_comp(void *bfad_fcxp, struct bfa_fcxp_s *fcxp, void *cbarg,
		   bfa_status_t req_status, u32 rsp_len,
		   u32 resid_len, struct fchs_s *rsp_fchs)
{
	/* discarded fcxp completion */
}