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
struct ibmvfc_target {void (* job_step ) (struct ibmvfc_target*) ;TYPE_1__* vhost; } ;
struct TYPE_2__ {int /*<<< orphan*/  work_wait_q; } ;

/* Variables and functions */
 int /*<<< orphan*/  IBMVFC_TGT_ACTION_INIT ; 
 int /*<<< orphan*/  ibmvfc_set_tgt_action (struct ibmvfc_target*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ibmvfc_init_tgt(struct ibmvfc_target *tgt,
			    void (*job_step) (struct ibmvfc_target *))
{
	ibmvfc_set_tgt_action(tgt, IBMVFC_TGT_ACTION_INIT);
	tgt->job_step = job_step;
	wake_up(&tgt->vhost->work_wait_q);
}