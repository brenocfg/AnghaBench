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
struct vio_port {unsigned int liobn; unsigned int riobn; int /*<<< orphan*/  crq_queue; int /*<<< orphan*/  crq_work; struct srp_target* target; struct vio_dev* dma_dev; } ;
struct vio_device_id {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct srp_target {int /*<<< orphan*/  dev; struct vio_port* ldata; struct Scsi_Host* shost; } ;
struct Scsi_Host {int /*<<< orphan*/  transportt; } ;

/* Variables and functions */
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INITIAL_SRP_LIMIT ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SRP_MAX_IU_LEN ; 
 int crq_queue_create (int /*<<< orphan*/ *,struct srp_target*) ; 
 int /*<<< orphan*/  eprintk (char*,unsigned int) ; 
 int /*<<< orphan*/  handle_crq ; 
 struct srp_target* host_to_srp_target (struct Scsi_Host*) ; 
 int /*<<< orphan*/  ibmvstgt_sht ; 
 int /*<<< orphan*/  ibmvstgt_transport_template ; 
 int /*<<< orphan*/  kfree (struct vio_port*) ; 
 struct vio_port* kzalloc (int,int /*<<< orphan*/ ) ; 
 int scsi_add_host (struct Scsi_Host*,int /*<<< orphan*/ ) ; 
 struct Scsi_Host* scsi_host_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int scsi_tgt_alloc_queue (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_tgt_free_queue (struct Scsi_Host*) ; 
 int srp_target_alloc (struct srp_target*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  srp_target_free (struct srp_target*) ; 
 scalar_t__ vio_get_attribute (struct vio_dev*,char*,unsigned int*) ; 

__attribute__((used)) static int ibmvstgt_probe(struct vio_dev *dev, const struct vio_device_id *id)
{
	struct Scsi_Host *shost;
	struct srp_target *target;
	struct vio_port *vport;
	unsigned int *dma, dma_size;
	int err = -ENOMEM;

	vport = kzalloc(sizeof(struct vio_port), GFP_KERNEL);
	if (!vport)
		return err;
	shost = scsi_host_alloc(&ibmvstgt_sht, sizeof(struct srp_target));
	if (!shost)
		goto free_vport;
	shost->transportt = ibmvstgt_transport_template;

	target = host_to_srp_target(shost);
	target->shost = shost;
	vport->dma_dev = dev;
	target->ldata = vport;
	vport->target = target;
	err = srp_target_alloc(target, &dev->dev, INITIAL_SRP_LIMIT,
			       SRP_MAX_IU_LEN);
	if (err)
		goto put_host;

	dma = (unsigned int *) vio_get_attribute(dev, "ibm,my-dma-window",
						 &dma_size);
	if (!dma || dma_size != 40) {
		eprintk("Couldn't get window property %d\n", dma_size);
		err = -EIO;
		goto free_srp_target;
	}
	vport->liobn = dma[0];
	vport->riobn = dma[5];

	INIT_WORK(&vport->crq_work, handle_crq);

	err = scsi_add_host(shost, target->dev);
	if (err)
		goto free_srp_target;

	err = scsi_tgt_alloc_queue(shost);
	if (err)
		goto remove_host;

	err = crq_queue_create(&vport->crq_queue, target);
	if (err)
		goto free_queue;

	return 0;
free_queue:
	scsi_tgt_free_queue(shost);
remove_host:
	scsi_remove_host(shost);
free_srp_target:
	srp_target_free(target);
put_host:
	scsi_host_put(shost);
free_vport:
	kfree(vport);
	return err;
}