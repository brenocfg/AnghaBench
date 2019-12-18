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
typedef  void* u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct scu_task_context {void* task_type; int /*<<< orphan*/  transfer_length_bytes; } ;
struct isci_request {struct scu_task_context* tc; } ;
typedef  enum dma_data_direction { ____Placeholder_dma_data_direction } dma_data_direction ;

/* Variables and functions */
 int DMA_TO_DEVICE ; 
 void* SCU_TASK_TYPE_DMA_IN ; 
 void* SCU_TASK_TYPE_DMA_OUT ; 
 int /*<<< orphan*/  sci_request_build_sgl (struct isci_request*) ; 
 int /*<<< orphan*/  scu_sata_reqeust_construct_task_context (struct isci_request*,struct scu_task_context*) ; 

__attribute__((used)) static void sci_stp_optimized_request_construct(struct isci_request *ireq,
						     u8 optimized_task_type,
						     u32 len,
						     enum dma_data_direction dir)
{
	struct scu_task_context *task_context = ireq->tc;

	/* Build the STP task context structure */
	scu_sata_reqeust_construct_task_context(ireq, task_context);

	/* Copy over the SGL elements */
	sci_request_build_sgl(ireq);

	/* Copy over the number of bytes to be transfered */
	task_context->transfer_length_bytes = len;

	if (dir == DMA_TO_DEVICE) {
		/*
		 * The difference between the DMA IN and DMA OUT request task type
		 * values are consistent with the difference between FPDMA READ
		 * and FPDMA WRITE values.  Add the supplied task type parameter
		 * to this difference to set the task type properly for this
		 * DATA OUT (WRITE) case. */
		task_context->task_type = optimized_task_type + (SCU_TASK_TYPE_DMA_OUT
								 - SCU_TASK_TYPE_DMA_IN);
	} else {
		/*
		 * For the DATA IN (READ) case, simply save the supplied
		 * optimized task type. */
		task_context->task_type = optimized_task_type;
	}
}