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
struct bfa_s {int dummy; } ;
struct bfa_fcxp_mod_s {int /*<<< orphan*/  rsp_pld_sz; } ;

/* Variables and functions */
 struct bfa_fcxp_mod_s* BFA_FCXP_MOD (struct bfa_s*) ; 

u32
bfa_fcxp_get_maxrsp(struct bfa_s *bfa)
{
	struct bfa_fcxp_mod_s *mod = BFA_FCXP_MOD(bfa);

	return mod->rsp_pld_sz;
}