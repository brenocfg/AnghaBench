#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  initiator; } ;
struct bfa_fcs_itnim_s {TYPE_2__ stats; TYPE_1__* rport; int /*<<< orphan*/  fcs; } ;
struct TYPE_3__ {int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFA_FCS_ITNIM_SM_INITIATOR ; 
 int /*<<< orphan*/  bfa_sm_send_event (struct bfa_fcs_itnim_s*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
bfa_fcs_itnim_is_initiator(struct bfa_fcs_itnim_s *itnim)
{
	bfa_trc(itnim->fcs, itnim->rport->pid);
	itnim->stats.initiator++;
	bfa_sm_send_event(itnim, BFA_FCS_ITNIM_SM_INITIATOR);
}