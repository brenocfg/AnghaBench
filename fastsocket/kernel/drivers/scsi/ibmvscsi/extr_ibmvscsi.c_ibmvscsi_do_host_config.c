#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int length; int /*<<< orphan*/  type; } ;
struct viosrp_host_config {int /*<<< orphan*/  buffer; TYPE_3__ common; } ;
struct TYPE_5__ {struct viosrp_host_config host_config; } ;
struct TYPE_6__ {TYPE_1__ mad; } ;
struct srp_event_struct {int /*<<< orphan*/  comp; TYPE_2__ iu; } ;
struct ibmvscsi_host_data {int /*<<< orphan*/  dev; TYPE_4__* host; int /*<<< orphan*/  pool; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_8__ {int /*<<< orphan*/  host_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  DMA_BIDIRECTIONAL ; 
 int /*<<< orphan*/  FW_FEATURE_CMO ; 
 int /*<<< orphan*/  VIOSRP_HOST_CONFIG_TYPE ; 
 int /*<<< orphan*/  VIOSRP_MAD_FORMAT ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dma_map_single (int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ dma_mapping_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_unmap_single (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  firmware_has_feature (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_event_struct (int /*<<< orphan*/ *,struct srp_event_struct*) ; 
 struct srp_event_struct* get_event_struct (int /*<<< orphan*/ *) ; 
 int ibmvscsi_send_srp_event (struct srp_event_struct*,struct ibmvscsi_host_data*,int) ; 
 int info_timeout ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_event_struct (struct srp_event_struct*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct viosrp_host_config*,int,int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  sync_completion ; 
 int /*<<< orphan*/  wait_for_completion (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ibmvscsi_do_host_config(struct ibmvscsi_host_data *hostdata,
				   unsigned char *buffer, int length)
{
	struct viosrp_host_config *host_config;
	struct srp_event_struct *evt_struct;
	unsigned long flags;
	dma_addr_t addr;
	int rc;

	evt_struct = get_event_struct(&hostdata->pool);
	if (!evt_struct) {
		dev_err(hostdata->dev, "couldn't allocate event for HOST_CONFIG!\n");
		return -1;
	}

	init_event_struct(evt_struct,
			  sync_completion,
			  VIOSRP_MAD_FORMAT,
			  info_timeout);

	host_config = &evt_struct->iu.mad.host_config;

	/* Set up a lun reset SRP command */
	memset(host_config, 0x00, sizeof(*host_config));
	host_config->common.type = VIOSRP_HOST_CONFIG_TYPE;
	host_config->common.length = length;
	host_config->buffer = addr = dma_map_single(hostdata->dev, buffer,
						    length,
						    DMA_BIDIRECTIONAL);

	if (dma_mapping_error(hostdata->dev, host_config->buffer)) {
		if (!firmware_has_feature(FW_FEATURE_CMO))
			dev_err(hostdata->dev,
			        "dma_mapping error getting host config\n");
		free_event_struct(&hostdata->pool, evt_struct);
		return -1;
	}

	init_completion(&evt_struct->comp);
	spin_lock_irqsave(hostdata->host->host_lock, flags);
	rc = ibmvscsi_send_srp_event(evt_struct, hostdata, info_timeout * 2);
	spin_unlock_irqrestore(hostdata->host->host_lock, flags);
	if (rc == 0)
		wait_for_completion(&evt_struct->comp);
	dma_unmap_single(hostdata->dev, addr, length, DMA_BIDIRECTIONAL);

	return rc;
}