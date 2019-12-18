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
struct lpfc_vport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int /*<<< orphan*/  lpfc_can_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_cleanup_rcv_buffers (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_cleanup_rpis (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_els_flush_cmd (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_els_flush_rscn (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 

void
lpfc_port_link_failure(struct lpfc_vport *vport)
{
	lpfc_vport_set_state(vport, FC_VPORT_LINKDOWN);

	/* Cleanup any outstanding received buffers */
	lpfc_cleanup_rcv_buffers(vport);

	/* Cleanup any outstanding RSCN activity */
	lpfc_els_flush_rscn(vport);

	/* Cleanup any outstanding ELS commands */
	lpfc_els_flush_cmd(vport);

	lpfc_cleanup_rpis(vport, 0);

	/* Turn off discovery timer if its running */
	lpfc_can_disctmo(vport);
}