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
typedef  int /*<<< orphan*/  uint16_t ;
struct vio_port {int /*<<< orphan*/  riobn; int /*<<< orphan*/  liobn; } ;
struct srp_target {int /*<<< orphan*/  dev; struct Scsi_Host* shost; } ;
struct mad_adapter_info_data {int mad_version; int os_type; int* port_max_txu; int /*<<< orphan*/  partition_number; int /*<<< orphan*/  partition_name; int /*<<< orphan*/  srp_version; } ;
struct iu_entry {struct srp_target* target; } ;
struct Scsi_Host {TYPE_1__* hostt; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;
struct TYPE_2__ {int max_sectors; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int H_SUCCESS ; 
 struct mad_adapter_info_data* dma_alloc_coherent (int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dma_free_coherent (int /*<<< orphan*/ ,int,struct mad_adapter_info_data*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eprintk (char*,...) ; 
 int h_copy_rdma (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct mad_adapter_info_data*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  partition_name ; 
 int /*<<< orphan*/  partition_number ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 

int send_adapter_info(struct iu_entry *iue,
		      dma_addr_t remote_buffer, uint16_t length)
{
	struct srp_target *target = iue->target;
	struct vio_port *vport = target_to_port(target);
	struct Scsi_Host *shost = target->shost;
	dma_addr_t data_token;
	struct mad_adapter_info_data *info;
	int err;

	info = dma_alloc_coherent(target->dev, sizeof(*info), &data_token,
				  GFP_KERNEL);
	if (!info) {
		eprintk("bad dma_alloc_coherent %p\n", target);
		return 1;
	}

	/* Get remote info */
	err = h_copy_rdma(sizeof(*info), vport->riobn, remote_buffer,
			  vport->liobn, data_token);
	if (err == H_SUCCESS) {
		dprintk("Client connect: %s (%d)\n",
			info->partition_name, info->partition_number);
	}

	memset(info, 0, sizeof(*info));

	strcpy(info->srp_version, "16.a");
	strncpy(info->partition_name, partition_name,
		sizeof(info->partition_name));
	info->partition_number = partition_number;
	info->mad_version = 1;
	info->os_type = 2;
	info->port_max_txu[0] = shost->hostt->max_sectors << 9;

	/* Send our info to remote */
	err = h_copy_rdma(sizeof(*info), vport->liobn, data_token,
			  vport->riobn, remote_buffer);

	dma_free_coherent(target->dev, sizeof(*info), info, data_token);

	if (err != H_SUCCESS) {
		eprintk("Error sending adapter info %d\n", err);
		return 1;
	}

	return 0;
}