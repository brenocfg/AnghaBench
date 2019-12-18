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
struct lpfc_vport {scalar_t__ port_type; int vport_flag; int load_flag; scalar_t__ port_state; int vpi_state; int unreg_vpi_cmpl; int /*<<< orphan*/  listentry; scalar_t__ work_port_events; int /*<<< orphan*/  vpi; struct lpfc_hba* phba; scalar_t__ ct_flags; scalar_t__ cfg_enable_da_id; } ;
struct lpfc_nodelist {scalar_t__ nlp_state; } ;
struct lpfc_hba {int fc_ratov; scalar_t__ link_state; scalar_t__ fc_topology; int /*<<< orphan*/  hbalock; struct lpfc_vport* pport; int /*<<< orphan*/  ndlp_lock; int /*<<< orphan*/  nlp_mem_pool; } ;
struct fc_vport {scalar_t__ dd_data; scalar_t__ shost; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FC_UNLOADING ; 
 int /*<<< orphan*/  Fabric_DID ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KERN_ERR ; 
 int /*<<< orphan*/  KERN_WARNING ; 
 int /*<<< orphan*/  LOG_VPORT ; 
 scalar_t__ LPFC_LINK_UP ; 
 scalar_t__ LPFC_PHYSICAL_PORT ; 
 scalar_t__ LPFC_TOPOLOGY_LOOP ; 
 int LPFC_VPI_REGISTERED ; 
 scalar_t__ LPFC_VPORT_FAILED ; 
 scalar_t__ LPFC_VPORT_READY ; 
 int /*<<< orphan*/  NLP_CHK_FREE_REQ (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_CHK_NODE_ACT (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  NLP_SET_FREE_REQ (struct lpfc_nodelist*) ; 
 scalar_t__ NLP_STE_UNMAPPED_NODE ; 
 int /*<<< orphan*/  NLP_STE_UNUSED_NODE ; 
 int /*<<< orphan*/  NameServer_DID ; 
 int /*<<< orphan*/  SLI_CTNS_DA_ID ; 
 int STATIC_VPORT ; 
 int VPORT_ERROR ; 
 int VPORT_INVAL ; 
 int VPORT_OK ; 
 int /*<<< orphan*/  fc_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_del_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lpfc_cleanup (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_debugfs_terminate (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_dequeue_node (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_discovery_wait (struct lpfc_vport*) ; 
 struct lpfc_nodelist* lpfc_enable_node (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 struct lpfc_nodelist* lpfc_findnode_did (struct lpfc_vport*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_free_sysfs_attr (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_free_vpi (struct lpfc_hba*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_issue_els_npiv_logo (struct lpfc_vport*,struct lpfc_nodelist*) ; 
 scalar_t__ lpfc_mbx_unreg_vpi (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_nlp_get (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_nlp_init (struct lpfc_vport*,struct lpfc_nodelist*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_nlp_put (struct lpfc_nodelist*) ; 
 int /*<<< orphan*/  lpfc_ns_cmd (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lpfc_printf_log (struct lpfc_hba*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_printf_vlog (struct lpfc_vport*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lpfc_shost_from_vport (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_sli_host_down (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_stop_vport_timers (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_unreg_all_rpis (struct lpfc_vport*) ; 
 int /*<<< orphan*/  lpfc_unreg_default_rpis (struct lpfc_vport*) ; 
 struct lpfc_nodelist* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 long schedule_timeout (long) ; 
 int /*<<< orphan*/  scsi_host_get (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

int
lpfc_vport_delete(struct fc_vport *fc_vport)
{
	struct lpfc_nodelist *ndlp = NULL;
	struct Scsi_Host *shost = (struct Scsi_Host *) fc_vport->shost;
	struct lpfc_vport *vport = *(struct lpfc_vport **)fc_vport->dd_data;
	struct lpfc_hba   *phba = vport->phba;
	long timeout;
	bool ns_ndlp_referenced = false;

	if (vport->port_type == LPFC_PHYSICAL_PORT) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
				 "1812 vport_delete failed: Cannot delete "
				 "physical host\n");
		return VPORT_ERROR;
	}

	/* If the vport is a static vport fail the deletion. */
	if ((vport->vport_flag & STATIC_VPORT) &&
		!(phba->pport->load_flag & FC_UNLOADING)) {
		lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
				 "1837 vport_delete failed: Cannot delete "
				 "static vport.\n");
		return VPORT_ERROR;
	}
	spin_lock_irq(&phba->hbalock);
	vport->load_flag |= FC_UNLOADING;
	spin_unlock_irq(&phba->hbalock);
	/*
	 * If we are not unloading the driver then prevent the vport_delete
	 * from happening until after this vport's discovery is finished.
	 */
	if (!(phba->pport->load_flag & FC_UNLOADING)) {
		int check_count = 0;
		while (check_count < ((phba->fc_ratov * 3) + 3) &&
		       vport->port_state > LPFC_VPORT_FAILED &&
		       vport->port_state < LPFC_VPORT_READY) {
			check_count++;
			msleep(1000);
		}
		if (vport->port_state > LPFC_VPORT_FAILED &&
		    vport->port_state < LPFC_VPORT_READY)
			return -EAGAIN;
	}
	/*
	 * This is a bit of a mess.  We want to ensure the shost doesn't get
	 * torn down until we're done with the embedded lpfc_vport structure.
	 *
	 * Beyond holding a reference for this function, we also need a
	 * reference for outstanding I/O requests we schedule during delete
	 * processing.  But once we scsi_remove_host() we can no longer obtain
	 * a reference through scsi_host_get().
	 *
	 * So we take two references here.  We release one reference at the
	 * bottom of the function -- after delinking the vport.  And we
	 * release the other at the completion of the unreg_vpi that get's
	 * initiated after we've disposed of all other resources associated
	 * with the port.
	 */
	if (!scsi_host_get(shost))
		return VPORT_INVAL;
	if (!scsi_host_get(shost)) {
		scsi_host_put(shost);
		return VPORT_INVAL;
	}
	lpfc_free_sysfs_attr(vport);

	lpfc_debugfs_terminate(vport);

	/*
	 * The call to fc_remove_host might release the NameServer ndlp. Since
	 * we might need to use the ndlp to send the DA_ID CT command,
	 * increment the reference for the NameServer ndlp to prevent it from
	 * being released.
	 */
	ndlp = lpfc_findnode_did(vport, NameServer_DID);
	if (ndlp && NLP_CHK_NODE_ACT(ndlp)) {
		lpfc_nlp_get(ndlp);
		ns_ndlp_referenced = true;
	}

	/* Remove FC host and then SCSI host with the vport */
	fc_remove_host(lpfc_shost_from_vport(vport));
	scsi_remove_host(lpfc_shost_from_vport(vport));

	ndlp = lpfc_findnode_did(phba->pport, Fabric_DID);

	/* In case of driver unload, we shall not perform fabric logo as the
	 * worker thread already stopped at this stage and, in this case, we
	 * can safely skip the fabric logo.
	 */
	if (phba->pport->load_flag & FC_UNLOADING) {
		if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
		    ndlp->nlp_state == NLP_STE_UNMAPPED_NODE &&
		    phba->link_state >= LPFC_LINK_UP) {
			/* First look for the Fabric ndlp */
			ndlp = lpfc_findnode_did(vport, Fabric_DID);
			if (!ndlp)
				goto skip_logo;
			else if (!NLP_CHK_NODE_ACT(ndlp)) {
				ndlp = lpfc_enable_node(vport, ndlp,
							NLP_STE_UNUSED_NODE);
				if (!ndlp)
					goto skip_logo;
			}
			/* Remove ndlp from vport npld list */
			lpfc_dequeue_node(vport, ndlp);

			/* Indicate free memory when release */
			spin_lock_irq(&phba->ndlp_lock);
			NLP_SET_FREE_REQ(ndlp);
			spin_unlock_irq(&phba->ndlp_lock);
			/* Kick off release ndlp when it can be safely done */
			lpfc_nlp_put(ndlp);
		}
		goto skip_logo;
	}

	/* Otherwise, we will perform fabric logo as needed */
	if (ndlp && NLP_CHK_NODE_ACT(ndlp) &&
	    ndlp->nlp_state == NLP_STE_UNMAPPED_NODE &&
	    phba->link_state >= LPFC_LINK_UP &&
	    phba->fc_topology != LPFC_TOPOLOGY_LOOP) {
		if (vport->cfg_enable_da_id) {
			timeout = msecs_to_jiffies(phba->fc_ratov * 2000);
			if (!lpfc_ns_cmd(vport, SLI_CTNS_DA_ID, 0, 0))
				while (vport->ct_flags && timeout)
					timeout = schedule_timeout(timeout);
			else
				lpfc_printf_log(vport->phba, KERN_WARNING,
						LOG_VPORT,
						"1829 CT command failed to "
						"delete objects on fabric\n");
		}
		/* First look for the Fabric ndlp */
		ndlp = lpfc_findnode_did(vport, Fabric_DID);
		if (!ndlp) {
			/* Cannot find existing Fabric ndlp, allocate one */
			ndlp = mempool_alloc(phba->nlp_mem_pool, GFP_KERNEL);
			if (!ndlp)
				goto skip_logo;
			lpfc_nlp_init(vport, ndlp, Fabric_DID);
			/* Indicate free memory when release */
			NLP_SET_FREE_REQ(ndlp);
		} else {
			if (!NLP_CHK_NODE_ACT(ndlp)) {
				ndlp = lpfc_enable_node(vport, ndlp,
						NLP_STE_UNUSED_NODE);
				if (!ndlp)
					goto skip_logo;
			}

			/* Remove ndlp from vport list */
			lpfc_dequeue_node(vport, ndlp);
			spin_lock_irq(&phba->ndlp_lock);
			if (!NLP_CHK_FREE_REQ(ndlp))
				/* Indicate free memory when release */
				NLP_SET_FREE_REQ(ndlp);
			else {
				/* Skip this if ndlp is already in free mode */
				spin_unlock_irq(&phba->ndlp_lock);
				goto skip_logo;
			}
			spin_unlock_irq(&phba->ndlp_lock);
		}

		/*
		 * If the vpi is not registered, then a valid FDISC doesn't
		 * exist and there is no need for a ELS LOGO.  Just cleanup
		 * the ndlp.
		 */
		if (!(vport->vpi_state & LPFC_VPI_REGISTERED)) {
			lpfc_nlp_put(ndlp);
			goto skip_logo;
		}

		vport->unreg_vpi_cmpl = VPORT_INVAL;
		timeout = msecs_to_jiffies(phba->fc_ratov * 2000);
		if (!lpfc_issue_els_npiv_logo(vport, ndlp))
			while (vport->unreg_vpi_cmpl == VPORT_INVAL && timeout)
				timeout = schedule_timeout(timeout);
	}

	if (!(phba->pport->load_flag & FC_UNLOADING))
		lpfc_discovery_wait(vport);

skip_logo:

	/*
	 * If the NameServer ndlp has been incremented to allow the DA_ID CT
	 * command to be sent, decrement the ndlp now.
	 */
	if (ns_ndlp_referenced) {
		ndlp = lpfc_findnode_did(vport, NameServer_DID);
		lpfc_nlp_put(ndlp);
	}

	lpfc_cleanup(vport);
	lpfc_sli_host_down(vport);

	lpfc_stop_vport_timers(vport);

	if (!(phba->pport->load_flag & FC_UNLOADING)) {
		lpfc_unreg_all_rpis(vport);
		lpfc_unreg_default_rpis(vport);
		/*
		 * Completion of unreg_vpi (lpfc_mbx_cmpl_unreg_vpi)
		 * does the scsi_host_put() to release the vport.
		 */
		if (lpfc_mbx_unreg_vpi(vport))
			scsi_host_put(shost);
	} else
		scsi_host_put(shost);

	lpfc_free_vpi(phba, vport->vpi);
	vport->work_port_events = 0;
	spin_lock_irq(&phba->hbalock);
	list_del_init(&vport->listentry);
	spin_unlock_irq(&phba->hbalock);
	lpfc_printf_vlog(vport, KERN_ERR, LOG_VPORT,
			 "1828 Vport Deleted.\n");
	scsi_host_put(shost);
	return VPORT_OK;
}