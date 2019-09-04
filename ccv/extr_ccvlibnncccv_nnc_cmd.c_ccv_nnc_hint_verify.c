#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {scalar_t__ format; int* dim; } ;
typedef  TYPE_4__ ccv_nnc_tensor_param_t ;
struct TYPE_13__ {int* dim; } ;
struct TYPE_11__ {int* begin; int* end; } ;
struct TYPE_15__ {TYPE_3__ stride; TYPE_1__ border; } ;
typedef  TYPE_5__ ccv_nnc_hint_t ;
struct TYPE_12__ {int* dim; } ;
struct TYPE_16__ {TYPE_2__ size; } ;
typedef  TYPE_6__ ccv_nnc_cmd_param_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM ; 
 scalar_t__ CCV_TENSOR_FORMAT_CHWN ; 
 scalar_t__ CCV_TENSOR_FORMAT_NCHW ; 
 scalar_t__ CCV_TENSOR_FORMAT_NHWC ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_nd (int*) ; 

int ccv_nnc_hint_verify(const ccv_nnc_hint_t hint, const ccv_nnc_cmd_param_t cmd, const ccv_nnc_tensor_param_t a, const ccv_nnc_tensor_param_t b)
{
	int i;
	assert(a.format == b.format);
	const int nd = ccv_nnc_tensor_nd(a.dim);
	assert(nd == CCV_NNC_MAX_DIM + 1 || nd == CCV_NNC_MAX_DIM + 2);
	int hw;
	if ((a.format == CCV_TENSOR_FORMAT_CHWN) ||
		(a.format == CCV_TENSOR_FORMAT_NHWC && nd == CCV_NNC_MAX_DIM + 1))
		hw = 0;
	else if ((a.format == CCV_TENSOR_FORMAT_NHWC && nd == CCV_NNC_MAX_DIM + 2) ||
			 (a.format == CCV_TENSOR_FORMAT_NCHW && nd == CCV_NNC_MAX_DIM + 1))
		hw = 1;
	else if (a.format == CCV_TENSOR_FORMAT_NCHW && nd == CCV_NNC_MAX_DIM + 2)
		hw = 2;
	else
		assert(0 && "unknown format");
	for (i = 0; i < CCV_NNC_MAX_DIM; i++)
	{
		if ((hint.border.begin[i] + hint.border.end[i] + a.dim[i] - cmd.size.dim[i]) % hint.stride.dim[i] != 0)
			return -1;
		int expected = (hint.border.begin[i] + hint.border.end[i] + a.dim[i + hw] - cmd.size.dim[i]) / hint.stride.dim[i] + 1;
		if (expected != b.dim[i + hw])
			return -1;
	}
	return 0;
}