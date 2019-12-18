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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct viosrp_crq {int valid; int reserved; int timeout; int status; int /*<<< orphan*/  IU_data_ptr; int /*<<< orphan*/  IU_length; int /*<<< orphan*/  format; } ;
struct vio_port {TYPE_4__* dma_dev; int /*<<< orphan*/  riobn; int /*<<< orphan*/  liobn; } ;
struct srp_target {int dummy; } ;
struct iu_entry {int /*<<< orphan*/  remote_token; TYPE_1__* sbuf; struct srp_target* target; } ;
struct TYPE_7__ {int /*<<< orphan*/  tag; } ;
struct TYPE_8__ {TYPE_2__ rsp; } ;
struct TYPE_10__ {TYPE_3__ srp; } ;
struct TYPE_9__ {int /*<<< orphan*/  unit_address; } ;
struct TYPE_6__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  eprintk (char*,long) ; 
 long h_copy_rdma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 long h_send_crq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 
 TYPE_5__* vio_iu (struct iu_entry*) ; 

__attribute__((used)) static int send_iu(struct iu_entry *iue, uint64_t length, uint8_t format)
{
	struct srp_target *target = iue->target;
	struct vio_port *vport = target_to_port(target);
	long rc, rc1;
	union {
		struct viosrp_crq cooked;
		uint64_t raw[2];
	} crq;

	/* First copy the SRP */
	rc = h_copy_rdma(length, vport->liobn, iue->sbuf->dma,
			 vport->riobn, iue->remote_token);

	if (rc)
		eprintk("Error %ld transferring data\n", rc);

	crq.cooked.valid = 0x80;
	crq.cooked.format = format;
	crq.cooked.reserved = 0x00;
	crq.cooked.timeout = 0x00;
	crq.cooked.IU_length = length;
	crq.cooked.IU_data_ptr = vio_iu(iue)->srp.rsp.tag;

	if (rc == 0)
		crq.cooked.status = 0x99;	/* Just needs to be non-zero */
	else
		crq.cooked.status = 0x00;

	rc1 = h_send_crq(vport->dma_dev->unit_address, crq.raw[0], crq.raw[1]);

	if (rc1) {
		eprintk("%ld sending response\n", rc1);
		return rc1;
	}

	return rc;
}