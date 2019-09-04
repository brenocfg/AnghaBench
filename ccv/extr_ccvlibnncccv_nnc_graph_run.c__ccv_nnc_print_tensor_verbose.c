#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int datatype; int /*<<< orphan*/ * dim; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__* u8; scalar_t__* i64; int /*<<< orphan*/ * i32; int /*<<< orphan*/ * f64; int /*<<< orphan*/ * f32; } ;
struct TYPE_6__ {TYPE_3__ info; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;

/* Variables and functions */
#define  CCV_32F 132 
#define  CCV_32S 131 
#define  CCV_64F 130 
#define  CCV_64S 129 
#define  CCV_8U 128 
 int /*<<< orphan*/  CCV_CLI_VERBOSE ; 
 scalar_t__ CCV_TENSOR_CPU_MEMORY ; 
 scalar_t__ CCV_TENSOR_GET_MEMORY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PRINT (int /*<<< orphan*/ ,char*,...) ; 
 int ccv_min (int /*<<< orphan*/ ,int) ; 
 int ccv_nnc_tensor_count (TYPE_3__) ; 

__attribute__((used)) static void _ccv_nnc_print_tensor_verbose(const ccv_nnc_tensor_t* const tensor)
{
	if (CCV_TENSOR_GET_MEMORY(tensor->info.type) != CCV_TENSOR_CPU_MEMORY)
		return;
	int i;
	switch (tensor->info.datatype)
	{
		case CCV_32F:
			for (i = 0; i < ccv_min(tensor->info.dim[0], 3); i++)
				PRINT(CCV_CLI_VERBOSE, " %f", tensor->data.f32[i]);
			break;
		case CCV_64F:
			for (i = 0; i < ccv_min(tensor->info.dim[0], 3); i++)
				PRINT(CCV_CLI_VERBOSE, " %f", tensor->data.f64[i]);
			break;
		case CCV_32S:
			for (i = 0; i < ccv_min(tensor->info.dim[0], 3); i++)
				PRINT(CCV_CLI_VERBOSE, " %d", tensor->data.i32[i]);
			break;
		case CCV_64S:
			for (i = 0; i < ccv_min(tensor->info.dim[0], 3); i++)
				PRINT(CCV_CLI_VERBOSE, " %lld", (long long)tensor->data.i64[i]);
			break;
		case CCV_8U:
			for (i = 0; i < ccv_min(tensor->info.dim[0], 3); i++)
				PRINT(CCV_CLI_VERBOSE, " %d", (int)tensor->data.u8[i]);
			break;
	}
	if (ccv_nnc_tensor_count(tensor->info) > 3)
		PRINT(CCV_CLI_VERBOSE, " ..");
}