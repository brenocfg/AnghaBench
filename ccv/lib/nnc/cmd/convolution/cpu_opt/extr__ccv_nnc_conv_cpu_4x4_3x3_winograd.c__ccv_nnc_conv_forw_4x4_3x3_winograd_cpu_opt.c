#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_view_t ;
struct TYPE_11__ {int* dim; } ;
struct TYPE_12__ {TYPE_1__ info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_t ;
typedef  int /*<<< orphan*/  ccv_nnc_stream_context_t ;
typedef  int /*<<< orphan*/  ccv_nnc_hint_t ;

/* Variables and functions */
 int _ccv_nnc_conv_forw_4x4_3x3_winograd_neon (int /*<<< orphan*/  const* const,TYPE_2__ const* const,TYPE_2__ const* const,int /*<<< orphan*/  const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int _ccv_nnc_conv_forw_4x4_3x3_winograd_ref (int /*<<< orphan*/  const* const,TYPE_2__ const* const,TYPE_2__ const* const,int /*<<< orphan*/  const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 
 int _ccv_nnc_conv_forw_4x4_3x3_winograd_sse2 (int /*<<< orphan*/  const* const,TYPE_2__ const* const,TYPE_2__ const* const,int /*<<< orphan*/  const,int /*<<< orphan*/ * const,int /*<<< orphan*/ * const) ; 

int _ccv_nnc_conv_forw_4x4_3x3_winograd_cpu_opt(const ccv_nnc_tensor_view_t* const a, const ccv_nnc_tensor_t* const w, const ccv_nnc_tensor_t* const bias, const ccv_nnc_hint_t hint, ccv_nnc_tensor_view_t* const b, ccv_nnc_stream_context_t* const stream_context)
{
#if defined(HAVE_SSE2)
	if (w->info.dim[0] % 4 == 0)
		return _ccv_nnc_conv_forw_4x4_3x3_winograd_sse2(a, w, bias, hint, b, stream_context);
#elif defined(HAVE_NEON)
	if (w->info.dim[0] % 4 == 0)
		return _ccv_nnc_conv_forw_4x4_3x3_winograd_neon(a, w, bias, hint, b, stream_context);
#endif
	return _ccv_nnc_conv_forw_4x4_3x3_winograd_ref(a, w, bias, hint, b, stream_context);
}