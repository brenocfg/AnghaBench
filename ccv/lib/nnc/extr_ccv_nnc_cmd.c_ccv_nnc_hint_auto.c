#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ format; int* dim; } ;
typedef  TYPE_4__ ccv_nnc_tensor_param_t ;
struct TYPE_14__ {int* begin; int* end; } ;
struct TYPE_12__ {int* dim; } ;
struct TYPE_16__ {TYPE_3__ border; TYPE_1__ stride; } ;
typedef  TYPE_5__ ccv_nnc_hint_t ;
struct TYPE_13__ {int* dim; } ;
struct TYPE_17__ {TYPE_2__ size; } ;
typedef  TYPE_6__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM ; 
 scalar_t__ CCV_TENSOR_FORMAT_CHWN ; 
 scalar_t__ CCV_TENSOR_FORMAT_NCHW ; 
 scalar_t__ CCV_TENSOR_FORMAT_NHWC ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_5__ ccv_nnc_no_hint ; 
 int ccv_nnc_tensor_nd (int*) ; 

ccv_nnc_hint_t ccv_nnc_hint_auto(const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t a, const ccv_nnc_tensor_param_t b)
{
	int i;
	if (a.format != b.format)
		return ccv_nnc_no_hint;
	assert(a.format == b.format);
	const int a_nd = ccv_nnc_tensor_nd(a.dim);
	const int b_nd = ccv_nnc_tensor_nd(b.dim);
	// Is not auto hint deducible dimensions.
	if (a_nd != b_nd || (a_nd != CCV_NNC_MAX_DIM + 1 && a_nd != CCV_NNC_MAX_DIM + 2))
		return ccv_nnc_no_hint;
	int hw;
	if ((a.format == CCV_TENSOR_FORMAT_CHWN) ||
		(a.format == CCV_TENSOR_FORMAT_NHWC && a_nd == CCV_NNC_MAX_DIM + 1))
		hw = 0;
	else if ((a.format == CCV_TENSOR_FORMAT_NHWC && a_nd == CCV_NNC_MAX_DIM + 2) ||
			 (a.format == CCV_TENSOR_FORMAT_NCHW && a_nd == CCV_NNC_MAX_DIM + 1))
		hw = 1;
	else if (a.format == CCV_TENSOR_FORMAT_NCHW && a_nd == CCV_NNC_MAX_DIM + 2)
		hw = 2;
	else
		assert(0 && "unknown format");
	ccv_nnc_hint_t hint_auto = {};
	// 0-dim is reserved for channels
	for (i = 0; i < CCV_NNC_MAX_DIM; i++)
	{
		// Cannot have one of the dim is zero, we cannot auto the hint, return no hint.
		assert(a.dim[i + hw] && b.dim[i + hw]);
		// This is guessed by having a stride that will approximately match the scale.
		int stride = (a.dim[i + hw] + b.dim[i + hw] / 2) / b.dim[i + hw];
		hint_auto.stride.dim[i] = stride;
		int border = (b.dim[i + hw] - 1) * stride - a.dim[i + hw] + cmd.size.dim[i];
		hint_auto.border.begin[i] = (border + 1) / 2; // Always prefer to have more padding in the beginning, this matches CUDNN behavior.
		hint_auto.border.end[i] = border - hint_auto.border.begin[i];
	}
	return hint_auto;
}