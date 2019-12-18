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
struct TYPE_3__ {void* submod_enabled; } ;
struct bfa_s {TYPE_1__ iocfc; void* queue_process; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* start ) (struct bfa_s*) ;} ;

/* Variables and functions */
 void* BFA_TRUE ; 
 int BFI_IOC_MAX_CQS ; 
 int /*<<< orphan*/  bfa_isr_rspq_ack (struct bfa_s*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfa_rspq_ci (struct bfa_s*,int) ; 
 TYPE_2__** hal_mods ; 
 int /*<<< orphan*/  stub1 (struct bfa_s*) ; 

__attribute__((used)) static void
bfa_iocfc_start_submod(struct bfa_s *bfa)
{
	int		i;

	bfa->queue_process = BFA_TRUE;
	for (i = 0; i < BFI_IOC_MAX_CQS; i++)
		bfa_isr_rspq_ack(bfa, i, bfa_rspq_ci(bfa, i));

	for (i = 0; hal_mods[i]; i++)
		hal_mods[i]->start(bfa);

	bfa->iocfc.submod_enabled = BFA_TRUE;
}