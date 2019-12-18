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
struct viosrp_crq {scalar_t__ format; int /*<<< orphan*/  IU_length; int /*<<< orphan*/  IU_data_ptr; } ;
struct vio_port {int /*<<< orphan*/  liobn; int /*<<< orphan*/  riobn; } ;
struct srp_target {int dummy; } ;
struct iu_entry {TYPE_1__* sbuf; int /*<<< orphan*/  remote_token; } ;
struct TYPE_2__ {int /*<<< orphan*/  dma; } ;

/* Variables and functions */
 long H_SUCCESS ; 
 scalar_t__ VIOSRP_MAD_FORMAT ; 
 int /*<<< orphan*/  eprintk (char*,long,...) ; 
 long h_copy_rdma (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int process_mad_iu (struct iu_entry*) ; 
 int process_srp_iu (struct iu_entry*) ; 
 struct iu_entry* srp_iu_get (struct srp_target*) ; 
 int /*<<< orphan*/  srp_iu_put (struct iu_entry*) ; 
 struct vio_port* target_to_port (struct srp_target*) ; 

__attribute__((used)) static void process_iu(struct viosrp_crq *crq, struct srp_target *target)
{
	struct vio_port *vport = target_to_port(target);
	struct iu_entry *iue;
	long err;
	int done = 1;

	iue = srp_iu_get(target);
	if (!iue) {
		eprintk("Error getting IU from pool, %p\n", target);
		return;
	}

	iue->remote_token = crq->IU_data_ptr;

	err = h_copy_rdma(crq->IU_length, vport->riobn,
			  iue->remote_token, vport->liobn, iue->sbuf->dma);

	if (err != H_SUCCESS) {
		eprintk("%ld transferring data error %p\n", err, iue);
		goto out;
	}

	if (crq->format == VIOSRP_MAD_FORMAT)
		done = process_mad_iu(iue);
	else
		done = process_srp_iu(iue);
out:
	if (done)
		srp_iu_put(iue);
}