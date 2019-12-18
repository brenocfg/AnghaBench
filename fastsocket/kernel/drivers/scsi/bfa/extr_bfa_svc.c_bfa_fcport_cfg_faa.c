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
typedef  int /*<<< orphan*/  u8 ;
struct bfa_s {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  faa_state; } ;
struct bfa_fcport_s {TYPE_1__ cfg; } ;

/* Variables and functions */
 struct bfa_fcport_s* BFA_FCPORT_MOD (struct bfa_s*) ; 
 int /*<<< orphan*/  bfa_trc (struct bfa_s*,int /*<<< orphan*/ ) ; 

void
bfa_fcport_cfg_faa(struct bfa_s *bfa, u8 state)
{
	struct bfa_fcport_s *fcport = BFA_FCPORT_MOD(bfa);

	bfa_trc(bfa, state);
	fcport->cfg.faa_state = state;
}