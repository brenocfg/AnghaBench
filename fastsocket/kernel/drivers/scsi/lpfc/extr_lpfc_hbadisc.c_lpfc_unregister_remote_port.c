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
struct lpfc_nodelist {int /*<<< orphan*/  nlp_DID; int /*<<< orphan*/  vport; int /*<<< orphan*/  nlp_type; int /*<<< orphan*/  nlp_flag; struct fc_rport* rport; } ;
struct fc_rport {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KERN_INFO ; 
 int /*<<< orphan*/  LOG_NODE ; 
 int /*<<< orphan*/  LPFC_DISC_TRC_RPORT ; 
 int /*<<< orphan*/  fc_remote_port_delete (struct fc_rport*) ; 
 int /*<<< orphan*/  lpfc_debugfs_disc_trc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,struct fc_rport*) ; 

__attribute__((used)) static void
lpfc_unregister_remote_port(struct lpfc_nodelist *ndlp)
{
	struct fc_rport *rport = ndlp->rport;

	lpfc_debugfs_disc_trc(ndlp->vport, LPFC_DISC_TRC_RPORT,
		"rport delete:    did:x%x flg:x%x type x%x",
		ndlp->nlp_DID, ndlp->nlp_flag, ndlp->nlp_type);

	lpfc_printf_vlog(ndlp->vport, KERN_INFO, LOG_NODE,
			 "3184 rport unregister x%06x, rport %p\n",
			 ndlp->nlp_DID, rport);

	fc_remote_port_delete(rport);

	return;
}