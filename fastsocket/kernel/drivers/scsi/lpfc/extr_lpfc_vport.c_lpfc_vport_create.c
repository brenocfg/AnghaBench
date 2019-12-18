#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  portName; int /*<<< orphan*/  nodeName; } ;
struct TYPE_8__ {int /*<<< orphan*/  wwn; } ;
struct TYPE_9__ {TYPE_3__ u; } ;
struct TYPE_6__ {int /*<<< orphan*/  wwn; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
struct lpfc_vport {int vpi; int fc_flag; scalar_t__ port_state; struct fc_vport* fc_vport; TYPE_5__ fc_sparam; TYPE_4__ fc_nodename; TYPE_2__ fc_portname; struct lpfc_hba* phba; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct lpfc_hba {int sli_rev; scalar_t__ link_state; scalar_t__ fc_topology; int link_flag; int /*<<< orphan*/  pport; int /*<<< orphan*/  max_vpi; int /*<<< orphan*/  cfg_enable_npiv; } ;
struct fc_vport {scalar_t__ dd_data; int /*<<< orphan*/  port_name; int /*<<< orphan*/  node_name; int /*<<< orphan*/  dev; struct Scsi_Host* shost; } ;
struct Scsi_Host {scalar_t__ hostdata; } ;

/* Variables and functions */
 int EINTR ; 
 int FC_VFI_REGISTERED ; 
 int /*<<< orphan*/  FC_VPORT_DISABLED ; 
 int /*<<< orphan*/  FC_VPORT_FAILED ; 
 int /*<<< orphan*/  FC_VPORT_LINKDOWN ; 
 int FC_VPORT_NEEDS_INIT_VPI ; 
 int /*<<< orphan*/  FC_VPORT_NO_FABRIC_SUPP ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  LOG_ELS ; 
 int /*<<< orphan*/  LOG_VPORT ; 
 scalar_t__ LPFC_FABRIC_CFG_LINK ; 
 scalar_t__ LPFC_LINK_UP ; 
 int LPFC_SLI_REV4 ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int LS_NPIV_FAB_SUPPORTED ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int VPORT_ERROR ; 
 int VPORT_INVAL ; 
 int VPORT_NORESOURCES ; 
 int VPORT_OK ; 
 int /*<<< orphan*/  destroy_port (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_alloc_sysfs_attr (struct lpfc_vport*) ; 
 int lpfc_alloc_vpi (struct lpfc_hba*) ; 
 struct lpfc_vport* lpfc_create_port (struct lpfc_hba*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_debugfs_initialize (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_findnode_did (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_free_vpi (struct lpfc_hba*,int) ; 
 int lpfc_get_instance () ; 
 int /*<<< orphan*/  lpfc_host_attrib_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_initial_fdisc (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_set_disctmo (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int lpfc_sli4_init_vpi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_unique_wwpn (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_valid_wwn_format (struct lpfc_hba*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lpfc_vport_set_state (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int lpfc_vport_sparm (struct lpfc_hba*,struct lpfc_vport*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  u64_to_wwn (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
lpfc_vport_create(struct fc_vport *fc_vport, bool disable)
{
	struct lpfc_nodelist *ndlp;
	struct Scsi_Host *shost = fc_vport->shost;
	struct lpfc_vport *pport = (struct lpfc_vport *) shost->hostdata;
	struct lpfc_hba   *phba = pport->phba;
	struct lpfc_vport *vport = NULL;
	int instance;
	int vpi;
	int rc = VPORT_ERROR;
	int status;

	if ((phba->sli_rev < 3) || !(phba->cfg_enable_npiv)) {
		lpfc_printf_log(phba, KERN_ERR, LOG_VPORT,
				"1808 Create VPORT failed: "
				"NPIV is not enabled: SLImode:%d\n",
				phba->sli_rev);
		rc = VPORT_INVAL;
		goto error_out;
	}

	vpi = lpfc_alloc_vpi(phba);
	if (vpi == 0) {
		lpfc_printf_log(phba, KERN_ERR, LOG_VPORT,
				"1809 Create VPORT failed: "
				"Max VPORTs (%d) exceeded\n",
				phba->max_vpi);
		rc = VPORT_NORESOURCES;
		goto error_out;
	}

	/* Assign an unused board number */
	if ((instance = lpfc_get_instance()) < 0) {
		lpfc_printf_log(phba, KERN_ERR, LOG_VPORT,
				"1810 Create VPORT failed: Cannot get "
				"instance number\n");
		lpfc_free_vpi(phba, vpi);
		rc = VPORT_NORESOURCES;
		goto error_out;
	}

	vport = lpfc_create_port(phba, instance, &fc_vport->dev);
	if (!vport) {
		lpfc_printf_log(phba, KERN_ERR, LOG_VPORT,
				"1811 Create VPORT failed: vpi x%x\n", vpi);
		lpfc_free_vpi(phba, vpi);
		rc = VPORT_NORESOURCES;
		goto error_out;
	}

	vport->vpi = vpi;
	lpfc_debugfs_initialize(vport);

	if ((status = lpfc_vport_sparm(phba, vport))) {
		if (status == -EINTR) {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
					 "1831 Create VPORT Interrupted.\n");
			rc = VPORT_ERROR;
		} else {
			lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
					 "1813 Create VPORT failed. "
					 "Cannot get sparam\n");
			rc = VPORT_NORESOURCES;
		}
		lpfc_free_vpi(phba, vpi);
		destroy_port(vport);
		goto error_out;
	}

	u64_to_wwn(fc_vport->node_name, vport->fc_nodename.u.wwn);
	u64_to_wwn(fc_vport->port_name, vport->fc_portname.u.wwn);

	memcpy(&vport->fc_sparam.portName, vport->fc_portname.u.wwn, 8);
	memcpy(&vport->fc_sparam.nodeName, vport->fc_nodename.u.wwn, 8);

	if (!lpfc_valid_wwn_format(phba, &vport->fc_sparam.nodeName, "WWNN") ||
	    !lpfc_valid_wwn_format(phba, &vport->fc_sparam.portName, "WWPN")) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
				 "1821 Create VPORT failed. "
				 "Invalid WWN format\n");
		lpfc_free_vpi(phba, vpi);
		destroy_port(vport);
		rc = VPORT_INVAL;
		goto error_out;
	}

	if (!lpfc_unique_wwpn(phba, vport)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
				 "1823 Create VPORT failed. "
				 "Duplicate WWN on HBA\n");
		lpfc_free_vpi(phba, vpi);
		destroy_port(vport);
		rc = VPORT_INVAL;
		goto error_out;
	}

	/* Create binary sysfs attribute for vport */
	lpfc_alloc_sysfs_attr(vport);

	*(struct lpfc_vport **)fc_vport->dd_data = vport;
	vport->fc_vport = fc_vport;

	/*
	 * In SLI4, the vpi must be activated before it can be used
	 * by the port.
	 */
	if ((phba->sli_rev == LPFC_SLI_REV4) &&
	    (pport->fc_flag & FC_VFI_REGISTERED)) {
		rc = lpfc_sli4_init_vpi(vport);
		if (rc) {
			lpfc_printf_log(phba, KERN_ERR, LOG_VPORT,
					"1838 Failed to INIT_VPI on vpi %d "
					"status %d\n", vpi, rc);
			rc = VPORT_NORESOURCES;
			lpfc_free_vpi(phba, vpi);
			goto error_out;
		}
	} else if (phba->sli_rev == LPFC_SLI_REV4) {
		/*
		 * Driver cannot INIT_VPI now. Set the flags to
		 * init_vpi when reg_vfi complete.
		 */
		vport->fc_flag |= FC_VPORT_NEEDS_INIT_VPI;
		lpfc_vport_set_state(vport, FC_VPORT_LINKDOWN);
		rc = VPORT_OK;
		goto out;
	}

	if ((phba->link_state < LPFC_LINK_UP) ||
	    (pport->port_state < LPFC_FABRIC_CFG_LINK) ||
	    (phba->fc_topology == LPFC_TOPOLOGY_LOOP)) {
		lpfc_vport_set_state(vport, FC_VPORT_LINKDOWN);
		rc = VPORT_OK;
		goto out;
	}

	if (disable) {
		lpfc_vport_set_state(vport, FC_VPORT_DISABLED);
		rc = VPORT_OK;
		goto out;
	}

	/* Use the Physical nodes Fabric NDLP to determine if the link is
	 * up and ready to FDISC.
	 */
	ndlp = lpfc_findnode_did(phba->pport, Fabric_DID);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
	    ndlp->nlp_state == NLP_STE_UNMAPPED_NODE) {
		if (phba->link_flag & LS_NPIV_FAB_SUPPORTED) {
			lpfc_set_disctmo(vport);
			lpfc_initial_fdisc(vport);
		} else {
			lpfc_vport_set_state(vport, FC_VPORT_NO_FABRIC_SUPP);
			lpfc_printf_vlog(vport, KERN_ERR, LOG_ELS,
					 "0262 No NPIV Fabric support\n");
		}
	} else {
		lpfc_vport_set_state(vport, FC_VPORT_FAILED);
	}
	rc = VPORT_OK;

out:
	lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
			"1825 Vport Created.\n");
	lpfc_host_attrib_init(lpfc_shost_from_vport(vport));
error_out:
	return rc;
}