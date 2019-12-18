#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int* dim; int /*<<< orphan*/  datatype; int /*<<< orphan*/  format; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_nnc_tensor_param_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;
struct TYPE_8__ {int /*<<< orphan*/  transpose_b; int /*<<< orphan*/  transpose_a; } ;
struct TYPE_10__ {TYPE_1__ blas; } ;
typedef  TYPE_3__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_get_matrix_params (TYPE_2__ const,int*,int /*<<< orphan*/ ,int*,int*,int*,int*,int*,int*) ; 
 int ccv_nnc_tensor_nd (int*) ; 

__attribute__((used)) static void _ccv_nnc_gemm_tensor_auto_forw(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t* const inputs, const int input_size, const ccv_nnc_hint_t hint, ccv_nnc_tensor_param_t* const outputs, const int output_size)
{
	assert(output_size == 1);
	int a_batch_size, a_rows, a_cols, a_batch_inc, a_rows_inc, a_cols_inc;
	int w_batch_size, w_rows, w_cols, w_batch_inc, w_rows_inc, w_cols_inc;
	const int a_nd = ccv_nnc_tensor_nd(inputs[0].dim);
	ccv_nnc_tensor_get_matrix_params(inputs[0], inputs[0].dim, cmd.blas.transpose_a, &a_batch_size, &a_rows, &a_cols, &a_batch_inc, &a_rows_inc, &a_cols_inc);
	ccv_nnc_tensor_get_matrix_params(inputs[1], inputs[1].dim, cmd.blas.transpose_b, &w_batch_size, &w_rows, &w_cols, &w_batch_inc, &w_rows_inc, &w_cols_inc);
	outputs[0].type = inputs[0].type;
	outputs[0].format = inputs[0].format;
	outputs[0].datatype = inputs[0].datatype;
	int b_rows = a_rows, b_cols = w_cols;
	if (a_nd == 1) {
		outputs[0].dim[0] = b_cols;
	} else if (a_nd == 2) {
		outputs[0].dim[0] = b_rows;
		outputs[0].dim[1] = b_cols;
	} else {
		assert(a_nd == 3);
		outputs[0].dim[0] = a_batch_size;
		outputs[0].dim[1] = b_rows;
		outputs[0].dim[2] = b_cols;
	}
}