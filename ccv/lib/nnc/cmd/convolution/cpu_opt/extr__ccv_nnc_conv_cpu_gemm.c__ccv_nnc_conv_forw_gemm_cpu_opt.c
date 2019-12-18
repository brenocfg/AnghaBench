#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;

/* Type definitions */
struct TYPE_24__ {int /*<<< orphan*/  u8; int /*<<< orphan*/  f32; } ;
struct TYPE_20__ {int* dim; } ;
struct TYPE_25__ {TYPE_5__ data; TYPE_1__ info; } ;
typedef  TYPE_6__ const ccv_nnc_tensor_view_t ;
typedef  TYPE_6__ ccv_nnc_tensor_t ;
struct TYPE_22__ {int* dim; } ;
struct TYPE_21__ {scalar_t__* begin; scalar_t__* end; } ;
struct TYPE_26__ {TYPE_3__ stride; TYPE_2__ border; } ;
typedef  TYPE_8__ ccv_nnc_hint_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_23__ {scalar_t__ f32; } ;
struct TYPE_27__ {int rows; TYPE_4__ data; } ;
typedef  TYPE_9__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_32F ; 
 int /*<<< orphan*/  CCV_B_TRANSPOSE ; 
 int CCV_C1 ; 
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_6__ const* const) ; 
 int CCV_NNC_EXEC_SUCCESS ; 
 int CCV_NNC_MAX_DIM ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_9__ ccv_dense_matrix (int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_gemm (TYPE_9__*,TYPE_9__*,int,TYPE_9__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ccv_nnc_tensor_nd (int*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 

int _ccv_nnc_conv_forw_gemm_cpu_opt(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_t* const w, const ccv_nnc_tensor_t* const bias, const ccv_nnc_hint_t hint, ccv_nnc_tensor_view_t* const b)
{
	assert(!CCV_IS_TENSOR_VIEW(a));
	assert(!CCV_IS_TENSOR_VIEW(w));
	assert(!bias || !CCV_IS_TENSOR_VIEW(bias));
	assert(!CCV_IS_TENSOR_VIEW(b));
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	assert(a_nd == CCV_NNC_MAX_DIM + 1 || a_nd == CCV_NNC_MAX_DIM + 2);
	const int* adim = (a_nd == CCV_NNC_MAX_DIM + 1) ? a->info.dim : a->info.dim + 1;
	const int b_nd = ccv_nnc_tensor_nd(b->info.dim);
	assert(b_nd == CCV_NNC_MAX_DIM + 1 || b_nd == CCV_NNC_MAX_DIM + 2);
	const int* bdim = (b_nd == CCV_NNC_MAX_DIM + 1) ? b->info.dim : b->info.dim + 1;
	assert(hint.border.begin[0] == 0 && hint.border.begin[1] == 0);
	assert(hint.border.end[0] == 0 && hint.border.end[1] == 0);
	assert(adim[0] == bdim[0]);
	assert(adim[1] == bdim[1]);
	assert(hint.stride.dim[0] <= 1 && hint.stride.dim[1] <= 1);
	ccv_dense_matrix_t am = ccv_dense_matrix(adim[0] * adim[1], adim[2], CCV_32F | CCV_C1, a->data.u8, 0);
	ccv_dense_matrix_t bm = ccv_dense_matrix(bdim[0] * bdim[1], bdim[2], CCV_32F | CCV_C1, b->data.u8, 0);
	// copy bias into each row.
	int i;
	if (bias)
		for (i = 0; i < bm.rows; i++)
			memcpy(bm.data.f32 + i * bdim[2], bias->data.f32, sizeof(float) * bdim[2]);
	ccv_dense_matrix_t* dbm = &bm;
	ccv_dense_matrix_t wm = ccv_dense_matrix(bdim[2], adim[2], CCV_32F | CCV_C1, w->data.u8, 0);
	if (bias)
		ccv_gemm(&am, &wm, 1, dbm, 1, CCV_B_TRANSPOSE, (ccv_matrix_t**)&dbm, 0); // supply b as matrix C is allowed
	else
		ccv_gemm(&am, &wm, 1, 0, 0, CCV_B_TRANSPOSE, (ccv_matrix_t**)&dbm, 0); // supply b as matrix C is allowed
	return CCV_NNC_EXEC_SUCCESS;
}