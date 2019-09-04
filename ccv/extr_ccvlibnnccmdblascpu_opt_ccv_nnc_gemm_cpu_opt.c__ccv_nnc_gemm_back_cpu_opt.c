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

int _ccv_nnc_gemm_back_cpu_opt(const ccv_nnc_tensor_view_t* const g, const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_view_t* const w, ccv_nnc_tensor_view_t* const dw, ccv_nnc_tensor_view_t* const bias, ccv_nnc_tensor_view_t* const h, const int flags)
{
#if defined(HAVE_SSE2) || defined(HAVE_NEON)
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	const int adim = (a_nd == 1) ? a->info.dim[0] : a->info.dim[1];
	const int g_nd = ccv_nnc_tensor_nd(g->info.dim);
	const int gdim = (g_nd == 1) ? g->info.dim[0] : g->info.dim[1];
	const int h_nd = h ? ccv_nnc_tensor_nd(h->info.dim) : 0;
	const int hdim = h ? ((h_nd == 1) ? h->info.dim[0] : h->info.dim[1]) : 0;
#endif
#if defined(HAVE_SSE2)
	if (gdim % 4 == 0 && adim % 4 == 0 && (!h || hdim % 4 == 0))
		return _ccv_nnc_gemm_back_sse2(g, a, w, dw, bias, h, flags);
#elif defined(HAVE_NEON)
	if (gdim % 4 == 0 && adim % 4 == 0 && (!h || hdim % 4 == 0))
		return _ccv_nnc_gemm_back_neon(g, a, w, dw, bias, h, flags);
#endif
	return CCV_NNC_EXEC_INVALID;
}