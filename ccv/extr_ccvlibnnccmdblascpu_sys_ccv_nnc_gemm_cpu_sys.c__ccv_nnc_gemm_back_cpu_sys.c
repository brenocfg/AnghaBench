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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int CCV_NNC_EXEC_INVALID ; 

int _ccv_nnc_gemm_back_cpu_sys(const ccv_nnc_tensor_view_t* const g, const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_view_t* const w, ccv_nnc_tensor_view_t* const dw, ccv_nnc_tensor_view_t* const bias, ccv_nnc_tensor_view_t* const h, const int flags)
{
#if (defined HAVE_CBLAS || defined HAVE_ACCELERATE_FRAMEWORK)
	assert(!CCV_IS_TENSOR_VIEW(g));
	assert(!CCV_IS_TENSOR_VIEW(a));
	assert(!CCV_IS_TENSOR_VIEW(dw));
	assert(!bias || !CCV_IS_TENSOR_VIEW(bias));
	if (!(flags & CCV_NNC_ACCUMULATE_OUTPUT)) // reset the gradients to 0
	{
		memset(dw->data.u8, 0, sizeof(float) * ccv_nnc_tensor_count(w->info));
		if (bias)
			memset(bias->data.u8, 0, sizeof(float) * ccv_nnc_tensor_count(bias->info));
	}
	assert(a->info.dim[2] == 0); // It is a 2-d array.
	assert(g->info.dim[2] == 0); // It is a 2-d array.
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	assert(a_nd == 1 || a_nd == 2);
	const int* adim = (a_nd == 1) ? a->info.dim : a->info.dim + 1;
	const int g_nd = ccv_nnc_tensor_nd(g->info.dim);
	assert(g_nd == 1 || g_nd == 2);
	const int* gdim = (g_nd == 1) ? g->info.dim : g->info.dim + 1;
	const int batch_size = a_nd == 1 ? 1 : ccv_max(1, a->info.dim[0]);
	assert(batch_size == (g_nd == 1) ? 1 : ccv_max(1, g->info.dim[0]));
	assert(!bias || bias->info.dim[0] == gdim[0]);
	ccv_dense_matrix_t gm = ccv_dense_matrix(batch_size, gdim[0], CCV_32F | CCV_C1, g->data.u8, 0);
	ccv_dense_matrix_t am = ccv_dense_matrix(batch_size, adim[0], CCV_32F | CCV_C1, a->data.u8, 0);
	int i, j;
	float* gp = g->data.f32;
	if (bias)
	{
		float* bp = bias->data.f32;
		for (i = 0; i < batch_size; i++)
		{
			for (j = 0; j < gdim[0]; j++)
				bp[j] += gp[j];
			gp += gdim[0];
		}
	}
	assert(gdim[0] == w->info.dim[0]);
	assert(adim[0] == w->info.dim[1]);
	ccv_dense_matrix_t dwm = ccv_dense_matrix(gdim[0], adim[0], CCV_32F | CCV_C1, dw->data.u8, 0);
	ccv_dense_matrix_t* ddwm = &dwm;
	ccv_gemm(&gm, &am, 1, ddwm, 1, CCV_A_TRANSPOSE, (ccv_matrix_t**)&ddwm, 0);
	if (h && w)
	{
		assert(!CCV_IS_TENSOR_VIEW(h));
		assert(!CCV_IS_TENSOR_VIEW(w));
		assert(h->info.dim[2] == 0); // It is a 2-d array.
		assert(h->info.dim[0] == a->info.dim[0]);
		const int h_nd = ccv_nnc_tensor_nd(h->info.dim);
		assert(h_nd == 1 || h_nd == 2);
		const int* hdim = (h_nd == 1) ? h->info.dim : h->info.dim + 1;
		assert(hdim[0] == adim[0]);
		assert(batch_size == (h_nd == 1) ? 1 : ccv_max(1, h->info.dim[0]));
		ccv_dense_matrix_t wm = ccv_dense_matrix(gdim[0], hdim[0], CCV_32F | CCV_C1, w->data.u8, 0);
		ccv_dense_matrix_t hm = ccv_dense_matrix(batch_size, hdim[0], CCV_32F | CCV_C1, h->data.u8, 0);
		ccv_dense_matrix_t* dhm = &hm;
		ccv_gemm(&gm, &wm, 1, 0, 0, 0 /* No transpose */, (ccv_matrix_t**)&dhm, 0);
	}
	return CCV_NNC_EXEC_SUCCESS;
#else
	return CCV_NNC_EXEC_INVALID;
#endif
}