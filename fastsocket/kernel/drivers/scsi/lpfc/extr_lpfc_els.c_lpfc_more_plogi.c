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
struct lpfc_vport {int fc_flag; int /*<<< orphan*/  port_state; int /*<<< orphan*/  fc_plogi_cnt; scalar_t__ num_disc_nodes; } ;

/* Variables and functions */
 int FC_NLP_MORE ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_DISCOVERY ; 
 int lpfc_els_disc_plogi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void
lpfc_more_plogi(struct lpfc_vport *vport)
{
	int sentplogi;

	if (vport->num_disc_nodes)
		vport->num_disc_nodes--;

	/* Continue discovery with <num_disc_nodes> PLOGIs to go */
	lpfc_printf_vlog(vport, KERN_INFO, LOG_DISCOVERY,
			 "0232 Continue discovery with %d PLOGIs to go "
			 "Data: x%x x%x x%x\n",
			 vport->num_disc_nodes, vport->fc_plogi_cnt,
			 vport->fc_flag, vport->port_state);
	/* Check to see if there are more PLOGIs to be sent */
	if (vport->fc_flag & FC_NLP_MORE)
		/* go thru NPR nodes and issue any remaining ELS PLOGIs */
		sentplogi = lpfc_els_disc_plogi(vport);

	return;
}