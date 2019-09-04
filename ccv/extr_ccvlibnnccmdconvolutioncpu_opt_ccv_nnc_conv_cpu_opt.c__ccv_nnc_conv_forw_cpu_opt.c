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
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;

/* Variables and functions */
 int CCV_NNC_EXEC_INVALID ; 

int _ccv_nnc_conv_forw_cpu_opt(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_t* const w, const ccv_nnc_tensor_t* const bias, const ccv_nnc_hint_t hint, ccv_nnc_tensor_view_t* const b)
{
#if defined(HAVE_SSE2)
	if (w->info.dim[0] % 4 == 0)
		return _ccv_nnc_conv_forw_sse2(a, w, bias, hint, b);
#elif defined(HAVE_NEON)
	if (w->info.dim[0] % 4 == 0)
		return _ccv_nnc_conv_forw_neon(a, w, bias, hint, b);
#endif
	return CCV_NNC_EXEC_INVALID;
}