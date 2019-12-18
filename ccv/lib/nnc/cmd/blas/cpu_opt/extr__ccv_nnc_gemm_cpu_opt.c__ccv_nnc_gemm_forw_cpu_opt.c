#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int* dim; } ;
struct TYPE_16__ {TYPE_1__ info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int CCV_NNC_EXEC_INVALID ; 
 int _ccv_nnc_gemm_forw_neon (TYPE_2__ const* const,TYPE_2__ const* const,TYPE_2__ const* const,TYPE_2__* const) ; 
 int _ccv_nnc_gemm_forw_sse2 (TYPE_2__ const* const,TYPE_2__ const* const,TYPE_2__ const* const,TYPE_2__* const) ; 
 int ccv_nnc_tensor_nd (int*) ; 

int _ccv_nnc_gemm_forw_cpu_opt(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_view_t* const w, const ccv_nnc_tensor_view_t* const bias, ccv_nnc_tensor_view_t* const b)
{
#if defined(HAVE_SSE2) || defined(HAVE_NEON)
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	const int adim = (a_nd == 1) ? a->info.dim[0] : a->info.dim[1];
#endif
#if defined(HAVE_SSE2)
	if (adim % 8 == 0)
		return _ccv_nnc_gemm_forw_sse2(a, w, bias, b);
#elif defined(HAVE_NEON)
	if (adim % 8 == 0)
		return _ccv_nnc_gemm_forw_neon(a, w, bias, b);
#endif
	return CCV_NNC_EXEC_INVALID;
}