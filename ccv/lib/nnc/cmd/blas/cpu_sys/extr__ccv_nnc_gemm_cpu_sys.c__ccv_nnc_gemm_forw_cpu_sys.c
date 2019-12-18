#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  u8; int /*<<< orphan*/  f32; } ;
struct TYPE_19__ {scalar_t__* dim; } ;
struct TYPE_17__ {TYPE_2__ data; TYPE_5__ info; } ;
typedef  TYPE_3__ const ccv_nnc_tensor_view_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_15__ {scalar_t__ f32; } ;
struct TYPE_18__ {TYPE_1__ data; } ;
typedef  TYPE_4__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_32F ; 
 int /*<<< orphan*/  CCV_B_TRANSPOSE ; 
 int CCV_C1 ; 
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_3__ const* const) ; 
 int CCV_NNC_EXEC_INVALID ; 
 int CCV_NNC_EXEC_SUCCESS ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__ ccv_dense_matrix (int const,int const,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_gemm (TYPE_4__*,TYPE_4__*,int,TYPE_4__*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int ccv_max (int,int) ; 
 int const ccv_nnc_tensor_count (TYPE_5__) ; 
 int ccv_nnc_tensor_nd (scalar_t__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 

int _ccv_nnc_gemm_forw_cpu_sys(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_view_t* const w, const ccv_nnc_tensor_view_t* const bias, ccv_nnc_tensor_view_t* const b)
{
#if (defined HAVE_CBLAS || defined HAVE_ACCELERATE_FRAMEWORK)
	assert(!CCV_IS_TENSOR_VIEW(a));
	assert(!CCV_IS_TENSOR_VIEW(b));
	assert(!CCV_IS_TENSOR_VIEW(w));
	assert(!bias || !CCV_IS_TENSOR_VIEW(bias));
	assert(a->info.dim[2] == 0); // It is a 2-d array.
	assert(b->info.dim[2] == 0); // It is a 2-d array.
	// Copy the most of parameters, but reshape the dimension of a to a vector.
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	const int* adim = (a_nd == 1) ? a->info.dim : a->info.dim + 1;
	const int b_nd = ccv_nnc_tensor_nd(b->info.dim);
	const int* bdim = (b_nd == 1) ? b->info.dim : b->info.dim + 1;
	const int batch_size = a_nd == 1 ? 1 : ccv_max(1, a->info.dim[0]);
	ccv_dense_matrix_t am = ccv_dense_matrix(batch_size, adim[0], CCV_32F | CCV_C1, a->data.u8, 0);
	assert(!bias || bdim[0] == ccv_nnc_tensor_count(bias->info));
	assert(batch_size == (b_nd == 1) ? 1 : ccv_max(1, b->info.dim[0]));
	ccv_dense_matrix_t bm = ccv_dense_matrix(batch_size, bdim[0], CCV_32F | CCV_C1, b->data.u8, 0);
	ccv_dense_matrix_t* dbm = &bm;
	// copy bias into each row.
	if (bias)
	{
		int i;
		for (i = 0; i < batch_size; i++)
			memcpy(bm.data.f32 + i * bdim[0], bias->data.f32, sizeof(float) * bdim[0]);
	} else
		memset(bm.data.f32, 0, sizeof(float) * bdim[0] * batch_size);
	assert(bdim[0] == w->info.dim[0]);
	assert(adim[0] == w->info.dim[1]);
	ccv_dense_matrix_t wm = ccv_dense_matrix(bdim[0], adim[0], CCV_32F | CCV_C1, w->data.u8, 0);
	ccv_gemm(&am, &wm, 1, dbm, 1, CCV_B_TRANSPOSE, (ccv_matrix_t**)&dbm, 0); // supply b as matrix C is allowed
	return CCV_NNC_EXEC_SUCCESS;
#else
	return CCV_NNC_EXEC_INVALID;
#endif
}