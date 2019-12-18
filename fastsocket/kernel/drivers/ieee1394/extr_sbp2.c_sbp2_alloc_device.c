#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct unit_directory {int /*<<< orphan*/  device; TYPE_3__* ne; } ;
struct sbp2_status_block {int dummy; } ;
struct sbp2_lu {size_t speed_code; scalar_t__ status_fifo_addr; struct Scsi_Host* shost; int /*<<< orphan*/  lu_list; struct sbp2_fwhost_info* hi; int /*<<< orphan*/  protocol_work; int /*<<< orphan*/  state; int /*<<< orphan*/  cmd_orb_lock; int /*<<< orphan*/  cmd_orb_completed; int /*<<< orphan*/  cmd_orb_inuse; int /*<<< orphan*/  max_payload_size; struct unit_directory* ud; TYPE_3__* ne; } ;
struct sbp2_fwhost_info {int /*<<< orphan*/  logical_units; TYPE_4__* host; } ;
struct Scsi_Host {unsigned long* hostdata; int /*<<< orphan*/  max_cmd_len; } ;
typedef  int /*<<< orphan*/  quadlet_t ;
struct TYPE_8__ {int /*<<< orphan*/  parent; } ;
struct TYPE_11__ {int /*<<< orphan*/  low_addr_space; TYPE_2__* driver; TYPE_1__ device; } ;
struct TYPE_10__ {TYPE_4__* host; } ;
struct TYPE_9__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CSR1212_ALL_SPACE_END ; 
 scalar_t__ CSR1212_INVALID_ADDR_SPACE ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 size_t IEEE1394_SPEED_100 ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SBP2LU_STATE_RUNNING ; 
 int /*<<< orphan*/  SBP2_ERR (char*) ; 
 int /*<<< orphan*/  SBP2_MAX_CDB_SIZE ; 
 scalar_t__ SBP2_MAX_SEG_SIZE ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_set_drvdata (int /*<<< orphan*/ *,struct sbp2_lu*) ; 
 scalar_t__ dma_get_max_seg_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_set_max_seg_size (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ hpsb_allocate_and_register_addrspace (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct sbp2_fwhost_info* hpsb_create_hostinfo (int /*<<< orphan*/ *,TYPE_4__*,int) ; 
 struct sbp2_fwhost_info* hpsb_get_hostinfo (int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  hpsb_register_addrspace (int /*<<< orphan*/ *,TYPE_4__*,int /*<<< orphan*/ *,int,int) ; 
 struct sbp2_lu* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sbp2_hi_logical_units_lock ; 
 int /*<<< orphan*/  sbp2_highlevel ; 
 int /*<<< orphan*/  sbp2_ops ; 
 int /*<<< orphan*/  sbp2_physdma_ops ; 
 int /*<<< orphan*/  sbp2_remove_device (struct sbp2_lu*) ; 
 int /*<<< orphan*/  sbp2_shost_template ; 
 int /*<<< orphan*/ * sbp2_speedto_max_payload ; 
 int /*<<< orphan*/  scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ *) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  try_module_get (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  write_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static struct sbp2_lu *sbp2_alloc_device(struct unit_directory *ud)
{
	struct sbp2_fwhost_info *hi;
	struct Scsi_Host *shost = NULL;
	struct sbp2_lu *lu = NULL;
	unsigned long flags;

	lu = kzalloc(sizeof(*lu), GFP_KERNEL);
	if (!lu) {
		SBP2_ERR("failed to create lu");
		goto failed_alloc;
	}

	lu->ne = ud->ne;
	lu->ud = ud;
	lu->speed_code = IEEE1394_SPEED_100;
	lu->max_payload_size = sbp2_speedto_max_payload[IEEE1394_SPEED_100];
	lu->status_fifo_addr = CSR1212_INVALID_ADDR_SPACE;
	INIT_LIST_HEAD(&lu->cmd_orb_inuse);
	INIT_LIST_HEAD(&lu->cmd_orb_completed);
	INIT_LIST_HEAD(&lu->lu_list);
	spin_lock_init(&lu->cmd_orb_lock);
	atomic_set(&lu->state, SBP2LU_STATE_RUNNING);
	INIT_WORK(&lu->protocol_work, NULL);

	dev_set_drvdata(&ud->device, lu);

	hi = hpsb_get_hostinfo(&sbp2_highlevel, ud->ne->host);
	if (!hi) {
		hi = hpsb_create_hostinfo(&sbp2_highlevel, ud->ne->host,
					  sizeof(*hi));
		if (!hi) {
			SBP2_ERR("failed to allocate hostinfo");
			goto failed_alloc;
		}
		hi->host = ud->ne->host;
		INIT_LIST_HEAD(&hi->logical_units);

#ifdef CONFIG_IEEE1394_SBP2_PHYS_DMA
		/* Handle data movement if physical dma is not
		 * enabled or not supported on host controller */
		if (!hpsb_register_addrspace(&sbp2_highlevel, ud->ne->host,
					     &sbp2_physdma_ops,
					     0x0ULL, 0xfffffffcULL)) {
			SBP2_ERR("failed to register lower 4GB address range");
			goto failed_alloc;
		}
#endif
	}

	if (dma_get_max_seg_size(hi->host->device.parent) > SBP2_MAX_SEG_SIZE)
		BUG_ON(dma_set_max_seg_size(hi->host->device.parent,
					    SBP2_MAX_SEG_SIZE));

	/* Prevent unloading of the 1394 host */
	if (!try_module_get(hi->host->driver->owner)) {
		SBP2_ERR("failed to get a reference on 1394 host driver");
		goto failed_alloc;
	}

	lu->hi = hi;

	write_lock_irqsave(&sbp2_hi_logical_units_lock, flags);
	list_add_tail(&lu->lu_list, &hi->logical_units);
	write_unlock_irqrestore(&sbp2_hi_logical_units_lock, flags);

	/* Register the status FIFO address range. We could use the same FIFO
	 * for targets at different nodes. However we need different FIFOs per
	 * target in order to support multi-unit devices.
	 * The FIFO is located out of the local host controller's physical range
	 * but, if possible, within the posted write area. Status writes will
	 * then be performed as unified transactions. This slightly reduces
	 * bandwidth usage, and some Prolific based devices seem to require it.
	 */
	lu->status_fifo_addr = hpsb_allocate_and_register_addrspace(
			&sbp2_highlevel, ud->ne->host, &sbp2_ops,
			sizeof(struct sbp2_status_block), sizeof(quadlet_t),
			ud->ne->host->low_addr_space, CSR1212_ALL_SPACE_END);
	if (lu->status_fifo_addr == CSR1212_INVALID_ADDR_SPACE) {
		SBP2_ERR("failed to allocate status FIFO address range");
		goto failed_alloc;
	}

	shost = scsi_host_alloc(&sbp2_shost_template, sizeof(unsigned long));
	if (!shost) {
		SBP2_ERR("failed to register scsi host");
		goto failed_alloc;
	}

	shost->hostdata[0] = (unsigned long)lu;
	shost->max_cmd_len = SBP2_MAX_CDB_SIZE;

	if (!scsi_add_host(shost, &ud->device)) {
		lu->shost = shost;
		return lu;
	}

	SBP2_ERR("failed to add scsi host");
	scsi_host_put(shost);

failed_alloc:
	sbp2_remove_device(lu);
	return NULL;
}