#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_3__ {int size; } ;
struct TYPE_4__ {TYPE_1__ tuple; } ;
typedef  TYPE_2__ ccv_cnnp_batch_context_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ ** const) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_cnnp_batching_deinit(void* const self, void* const context)
{
	ccv_cnnp_batch_context_t* const batch = (ccv_cnnp_batch_context_t*)context;
	ccv_nnc_tensor_t** const tensors = (ccv_nnc_tensor_t**)self;
	const int size = batch->tuple.size;
	int i;
	for (i = 0; i < size; i++)
		ccv_nnc_tensor_free(tensors[i]);
	ccfree(tensors);
}