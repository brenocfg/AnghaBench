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
struct TYPE_6__ {int time_out_value; int srb_flags; } ;
struct vmscsi_request {scalar_t__ data_in; int /*<<< orphan*/  cdb_length; int /*<<< orphan*/  cdb; int /*<<< orphan*/  lun; int /*<<< orphan*/  target_id; int /*<<< orphan*/  path_id; int /*<<< orphan*/  port_number; TYPE_2__ win8_extension; } ;
struct TYPE_8__ {int offset; int* pfn_array; int /*<<< orphan*/  len; } ;
struct TYPE_5__ {struct vmscsi_request vm_srb; } ;
struct storvsc_cmd_request {int bounce_sgl_count; struct scatterlist* bounce_sgl; TYPE_4__ data_buffer; int /*<<< orphan*/  sense_buffer; TYPE_1__ vstor_packet; struct scsi_cmnd* cmd; } ;
struct stor_mem_pools {int /*<<< orphan*/  request_mempool; } ;
struct scsi_cmnd {void (* scsi_done ) (struct scsi_cmnd*) ;unsigned char* host_scribble; int sc_data_direction; int /*<<< orphan*/  sense_buffer; int /*<<< orphan*/  cmnd; int /*<<< orphan*/  cmd_len; TYPE_3__* device; } ;
struct scatterlist {int offset; } ;
struct hv_host_device {int /*<<< orphan*/  port; struct hv_device* dev; } ;
struct hv_device {int dummy; } ;
struct Scsi_Host {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/  lun; int /*<<< orphan*/  id; int /*<<< orphan*/  channel; struct stor_mem_pools* hostdata; struct Scsi_Host* host; } ;

/* Variables and functions */
 int ALIGN (int /*<<< orphan*/ ,int) ; 
#define  DMA_FROM_DEVICE 129 
#define  DMA_TO_DEVICE 128 
 int EAGAIN ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int PAGE_SHIFT ; 
 int PAGE_SIZE ; 
 scalar_t__ READ_TYPE ; 
 int SCSI_MLQUEUE_DEVICE_BUSY ; 
 int SCSI_MLQUEUE_HOST_BUSY ; 
 int SRB_FLAGS_DATA_IN ; 
 int SRB_FLAGS_DATA_OUT ; 
 int SRB_FLAGS_DISABLE_SYNCH_TRANSFER ; 
 int SRB_FLAGS_QUEUE_ACTION_ENABLE ; 
 scalar_t__ UNKNOWN_TYPE ; 
 scalar_t__ WRITE_TYPE ; 
 int /*<<< orphan*/  copy_to_bounce_buffer (struct scatterlist*,struct scatterlist*,int) ; 
 struct scatterlist* create_bounce_buffer (struct scatterlist*,int,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  destroy_bounce_buffer (struct scatterlist*,int) ; 
 int do_bounce_buffer (struct scatterlist*,int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct storvsc_cmd_request* mempool_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mempool_free (struct storvsc_cmd_request*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct storvsc_cmd_request*,int /*<<< orphan*/ ,int) ; 
 int page_to_pfn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scsi_bufflen (struct scsi_cmnd*) ; 
 int scsi_sg_count (struct scsi_cmnd*) ; 
 scalar_t__ scsi_sglist (struct scsi_cmnd*) ; 
 int /*<<< orphan*/  sg_page (struct scatterlist*) ; 
 struct hv_host_device* shost_priv (struct Scsi_Host*) ; 
 int storvsc_do_io (struct hv_device*,struct storvsc_cmd_request*) ; 
 int /*<<< orphan*/  storvsc_scsi_cmd_ok (struct scsi_cmnd*) ; 
 void stub1 (struct scsi_cmnd*) ; 
 int virt_to_phys (scalar_t__) ; 

__attribute__((used)) static int storvsc_queuecommand(struct scsi_cmnd *scmnd,
	void (*done)(struct scsi_cmnd *scmnd))
{
	struct Scsi_Host *host = scmnd->device->host;
	int ret;
	struct hv_host_device *host_dev = shost_priv(host);
	struct hv_device *dev = host_dev->dev;
	struct storvsc_cmd_request *cmd_request;
	unsigned int request_size = 0;
	int i;
	struct scatterlist *sgl;
	unsigned int sg_count = 0;
	struct vmscsi_request *vm_srb;
	struct stor_mem_pools *memp = scmnd->device->hostdata;

	scmnd->scsi_done = done;

	if (!storvsc_scsi_cmd_ok(scmnd)) {
		scmnd->scsi_done(scmnd);
		return 0;
	}

	request_size = sizeof(struct storvsc_cmd_request);

	cmd_request = mempool_alloc(memp->request_mempool,
				       GFP_ATOMIC);

	/*
	 * We might be invoked in an interrupt context; hence
	 * mempool_alloc() can fail.
	 */
	if (!cmd_request)
		return SCSI_MLQUEUE_DEVICE_BUSY;

	memset(cmd_request, 0, sizeof(struct storvsc_cmd_request));

	/* Setup the cmd request */
	cmd_request->cmd = scmnd;

	scmnd->host_scribble = (unsigned char *)cmd_request;

	vm_srb = &cmd_request->vstor_packet.vm_srb;
	vm_srb->win8_extension.time_out_value = 60;


	/* Build the SRB */
	switch (scmnd->sc_data_direction) {
	case DMA_TO_DEVICE:
		vm_srb->data_in = WRITE_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_OUT;
		vm_srb->win8_extension.srb_flags |=
			(SRB_FLAGS_QUEUE_ACTION_ENABLE |
			SRB_FLAGS_DISABLE_SYNCH_TRANSFER);
		break;
	case DMA_FROM_DEVICE:
		vm_srb->data_in = READ_TYPE;
		vm_srb->win8_extension.srb_flags |= SRB_FLAGS_DATA_IN;
		vm_srb->win8_extension.srb_flags |=
			(SRB_FLAGS_QUEUE_ACTION_ENABLE |
			SRB_FLAGS_DISABLE_SYNCH_TRANSFER);
		break;
	default:
		vm_srb->data_in = UNKNOWN_TYPE;
		vm_srb->win8_extension.srb_flags = 0;
		break;
	}


	vm_srb->port_number = host_dev->port;
	vm_srb->path_id = scmnd->device->channel;
	vm_srb->target_id = scmnd->device->id;
	vm_srb->lun = scmnd->device->lun;

	vm_srb->cdb_length = scmnd->cmd_len;

	memcpy(vm_srb->cdb, scmnd->cmnd, vm_srb->cdb_length);

	cmd_request->sense_buffer = scmnd->sense_buffer;


	cmd_request->data_buffer.len = scsi_bufflen(scmnd);
	if (scsi_sg_count(scmnd)) {
		sgl = (struct scatterlist *)scsi_sglist(scmnd);
		sg_count = scsi_sg_count(scmnd);

		/* check if we need to bounce the sgl */
		if (do_bounce_buffer(sgl, scsi_sg_count(scmnd)) != -1) {
			cmd_request->bounce_sgl =
				create_bounce_buffer(sgl, scsi_sg_count(scmnd),
						     scsi_bufflen(scmnd),
						     vm_srb->data_in);
			if (!cmd_request->bounce_sgl) {
				ret = SCSI_MLQUEUE_HOST_BUSY;
				goto queue_error;
			}

			cmd_request->bounce_sgl_count =
				ALIGN(scsi_bufflen(scmnd), PAGE_SIZE) >>
					PAGE_SHIFT;

			if (vm_srb->data_in == WRITE_TYPE)
				copy_to_bounce_buffer(sgl,
					cmd_request->bounce_sgl,
					scsi_sg_count(scmnd));

			sgl = cmd_request->bounce_sgl;
			sg_count = cmd_request->bounce_sgl_count;
		}

		cmd_request->data_buffer.offset = sgl[0].offset;

		for (i = 0; i < sg_count; i++)
			cmd_request->data_buffer.pfn_array[i] =
				page_to_pfn(sg_page((&sgl[i])));

	} else if (scsi_sglist(scmnd)) {
		cmd_request->data_buffer.offset =
			virt_to_phys(scsi_sglist(scmnd)) & (PAGE_SIZE-1);
		cmd_request->data_buffer.pfn_array[0] =
			virt_to_phys(scsi_sglist(scmnd)) >> PAGE_SHIFT;
	}

	/* Invokes the vsc to start an IO */
	ret = storvsc_do_io(dev, cmd_request);

	if (ret == -EAGAIN) {
		/* no more space */

		if (cmd_request->bounce_sgl_count) {
			destroy_bounce_buffer(cmd_request->bounce_sgl,
					cmd_request->bounce_sgl_count);

			ret = SCSI_MLQUEUE_DEVICE_BUSY;
			goto queue_error;
		}
	}

	return 0;

queue_error:
	mempool_free(cmd_request, memp->request_mempool);
	scmnd->host_scribble = NULL;
	return ret;
}