#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* exec_data; void* tensor_data; } ;
typedef  TYPE_1__ ccv_nnc_tensor_tape_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tape_tensor_data_array_t ;
typedef  int /*<<< orphan*/  ccv_nnc_tape_exec_data_array_t ;

/* Variables and functions */
 scalar_t__ ccmalloc (int) ; 
 void* ccv_array_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ccv_nnc_tensor_tape_t* ccv_nnc_tensor_tape_new(void)
{
	ccv_nnc_tensor_tape_t* tape = (ccv_nnc_tensor_tape_t*)ccmalloc(sizeof(ccv_nnc_tensor_tape_t));
	tape->tensor_data = ccv_array_new(sizeof(ccv_nnc_tape_tensor_data_array_t), 0, 0);
	tape->exec_data = ccv_array_new(sizeof(ccv_nnc_tape_exec_data_array_t), 0, 0);
	return tape;
}