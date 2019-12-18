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
struct TYPE_3__ {scalar_t__ fcp_abort_io; scalar_t__ fcp_cleanup; scalar_t__ fcp_cmd_send; } ;
struct fc_lport {TYPE_2__* host; struct fc_fcp_internal* scsi_priv; TYPE_1__ tt; } ;
struct fc_fcp_internal {int /*<<< orphan*/  scsi_pkt_pool; int /*<<< orphan*/  scsi_queue_lock; int /*<<< orphan*/  scsi_pkt_queue; int /*<<< orphan*/  max_can_queue; } ;
struct TYPE_4__ {int /*<<< orphan*/  can_queue; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ fc_fcp_abort_io ; 
 scalar_t__ fc_fcp_cleanup ; 
 scalar_t__ fc_fcp_cmd_send ; 
 int /*<<< orphan*/  kfree (struct fc_fcp_internal*) ; 
 struct fc_fcp_internal* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_create_slab_pool (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_pkt_cachep ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

int fc_fcp_init(struct fc_lport *lport)
{
	int rc;
	struct fc_fcp_internal *si;

	if (!lport->tt.fcp_cmd_send)
		lport->tt.fcp_cmd_send = fc_fcp_cmd_send;

	if (!lport->tt.fcp_cleanup)
		lport->tt.fcp_cleanup = fc_fcp_cleanup;

	if (!lport->tt.fcp_abort_io)
		lport->tt.fcp_abort_io = fc_fcp_abort_io;

	si = kzalloc(sizeof(struct fc_fcp_internal), GFP_KERNEL);
	if (!si)
		return -ENOMEM;
	lport->scsi_priv = si;
	si->max_can_queue = lport->host->can_queue;
	INIT_LIST_HEAD(&si->scsi_pkt_queue);
	spin_lock_init(&si->scsi_queue_lock);

	si->scsi_pkt_pool = mempool_create_slab_pool(2, scsi_pkt_cachep);
	if (!si->scsi_pkt_pool) {
		rc = -ENOMEM;
		goto free_internal;
	}
	return 0;

free_internal:
	kfree(si);
	return rc;
}