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
typedef  int /*<<< orphan*/  uint32_t ;
struct lpfc_vport {TYPE_1__* phba; } ;
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  nlp_rpi; int /*<<< orphan*/  nlp_listp; } ;
struct TYPE_2__ {scalar_t__ sli_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_NODE ; 
 scalar_t__ LPFC_SLI_REV4 ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (struct lpfc_vport*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_initialize_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_sli4_alloc_rpi (TYPE_1__*) ; 
 int /*<<< orphan*/  memset (struct lpfc_nodelist*,int /*<<< orphan*/ ,int) ; 

void
lpfc_nlp_init(struct lpfc_vport *vport, struct lpfc_nodelist *ndlp,
	      uint32_t did)
{
	memset(ndlp, 0, sizeof (struct lpfc_nodelist));

	lpfc_initialize_node(vport, ndlp, did);
	INIT_LIST_HEAD(&ndlp->nlp_listp);
	if (vport->phba->sli_rev == LPFC_SLI_REV4)
		ndlp->nlp_rpi = lpfc_sli4_alloc_rpi(vport->phba);


	lpfc_debugfs_disc_trc(vport, LPFC_DISC_TRC_NODE,
		"node init:       did:x%x",
		ndlp->nlp_DID, 0, 0);

	return;
}