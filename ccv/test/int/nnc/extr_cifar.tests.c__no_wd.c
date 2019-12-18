#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ decay; } ;
struct TYPE_10__ {TYPE_2__ sgd; } ;
struct TYPE_11__ {TYPE_3__ info; } ;
typedef  TYPE_4__ ccv_nnc_cmd_t ;
struct TYPE_8__ {scalar_t__ cmd; } ;
struct TYPE_12__ {int index; TYPE_1__ cmd; } ;
typedef  TYPE_5__ ccv_cnnp_trainable_index_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_model_t ;

/* Variables and functions */
 scalar_t__ CCV_NNC_BATCH_NORM_FORWARD ; 
 scalar_t__ CCV_NNC_CONVOLUTION_FORWARD ; 
 scalar_t__ CCV_NNC_GEMM_FORWARD ; 

__attribute__((used)) static ccv_nnc_cmd_t _no_wd(const ccv_cnnp_model_t* const model, const ccv_cnnp_trainable_index_t* const trainable_indexes, const int trainable_index_size, const void* const context)
{
	int i;
	ccv_nnc_cmd_t cmd = *(const ccv_nnc_cmd_t*)context;
	for (i = 0; i < trainable_index_size; i++)
	{
		if (trainable_indexes[i].cmd.cmd == CCV_NNC_BATCH_NORM_FORWARD &&
			(trainable_indexes[i].index == 1 ||  trainable_indexes[i].index == 2)) // If it is scale / bias of batch norm, remove weight decay.
			cmd.info.sgd.decay = 0;
		if (trainable_indexes[i].cmd.cmd == CCV_NNC_GEMM_FORWARD &&
			trainable_indexes[i].index == 2) // bias in gemm.
			cmd.info.sgd.decay = 0;
		if (trainable_indexes[i].cmd.cmd == CCV_NNC_CONVOLUTION_FORWARD &&
			trainable_indexes[i].index == 2) // bias in convolution.
			cmd.info.sgd.decay = 0;
	}
	return cmd;
}