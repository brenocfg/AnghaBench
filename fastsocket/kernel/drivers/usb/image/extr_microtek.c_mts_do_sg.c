#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct urb {int status; } ;
struct scatterlist {int /*<<< orphan*/  length; } ;
struct TYPE_5__ {size_t fragment; TYPE_1__* srb; int /*<<< orphan*/  data_pipe; } ;
struct TYPE_4__ {int result; } ;

/* Variables and functions */
 int DID_ABORT ; 
 int DID_ERROR ; 
 int ENOENT ; 
 int /*<<< orphan*/  MTS_DEBUG (char*,size_t,int) ; 
 int /*<<< orphan*/  MTS_INT_INIT () ; 
 TYPE_3__* context ; 
 void mts_data_done (struct urb*) ; 
 int /*<<< orphan*/  mts_int_submit_urb (struct urb*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void (*) (struct urb*)) ; 
 int /*<<< orphan*/  mts_transfer_cleanup (struct urb*) ; 
 int scsi_sg_count (TYPE_1__*) ; 
 struct scatterlist* scsi_sglist (TYPE_1__*) ; 
 int /*<<< orphan*/  sg_virt (struct scatterlist*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void mts_do_sg (struct urb* transfer)
{
	struct scatterlist * sg;
	int status = transfer->status;
	MTS_INT_INIT();

	MTS_DEBUG("Processing fragment %d of %d\n", context->fragment,
	                                          scsi_sg_count(context->srb));

	if (unlikely(status)) {
                context->srb->result = (status == -ENOENT ? DID_ABORT : DID_ERROR)<<16;
		mts_transfer_cleanup(transfer);
        }

	sg = scsi_sglist(context->srb);
	context->fragment++;
	mts_int_submit_urb(transfer,
			   context->data_pipe,
			   sg_virt(&sg[context->fragment]),
			   sg[context->fragment].length,
			   context->fragment + 1 == scsi_sg_count(context->srb) ?
			   mts_data_done : mts_do_sg);
	return;
}