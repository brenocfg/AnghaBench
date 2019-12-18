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
struct vio_port {int dummy; } ;
struct vio_dev {int /*<<< orphan*/  dev; } ;
struct srp_target {struct vio_port* ldata; struct Scsi_Host* shost; } ;
struct Scsi_Host {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  crq_queue_destroy (struct srp_target*) ; 
 struct srp_target* dev_get_drvdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (struct vio_port*) ; 
 int /*<<< orphan*/  scsi_host_put (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  scsi_tgt_free_queue (struct Scsi_Host*) ; 
 int /*<<< orphan*/  srp_remove_host (struct Scsi_Host*) ; 
 int /*<<< orphan*/  srp_target_free (struct srp_target*) ; 

__attribute__((used)) static int ibmvstgt_remove(struct vio_dev *dev)
{
	struct srp_target *target = dev_get_drvdata(&dev->dev);
	struct Scsi_Host *shost = target->shost;
	struct vio_port *vport = target->ldata;

	crq_queue_destroy(target);
	srp_remove_host(shost);
	scsi_remove_host(shost);
	scsi_tgt_free_queue(shost);
	srp_target_free(target);
	kfree(vport);
	scsi_host_put(shost);
	return 0;
}