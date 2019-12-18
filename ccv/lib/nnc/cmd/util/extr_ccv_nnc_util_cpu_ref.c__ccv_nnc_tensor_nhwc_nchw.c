#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* f32; } ;
struct TYPE_7__ {int* dim; } ;
struct TYPE_9__ {TYPE_2__ data; TYPE_1__ info; } ;
typedef  TYPE_3__ const ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_nd (int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_inc (TYPE_3__ const*,int*) ; 

__attribute__((used)) static void _ccv_nnc_tensor_nhwc_nchw(const ccv_nnc_tensor_view_t* a, ccv_nnc_tensor_view_t* b)
{
	// Assuming this is float 32.
	int ainc[CCV_NNC_MAX_DIM + 2];
	int binc[CCV_NNC_MAX_DIM + 2];
	int k;
	// In case it is Toll-free bridged matrix object (NHWC format is possible).
	const int a_nd = ccv_nnc_tensor_nd(a->info.dim);
	const int b_nd = ccv_nnc_tensor_nd(b->info.dim);
	const int a_offset = CCV_NNC_MAX_DIM + 2 - a_nd;
	assert(a_offset == 0 || a_offset == 1);
	const int b_offset = CCV_NNC_MAX_DIM + 2 - b_nd;
	assert(b_offset == 0 || b_offset == 1);
	ccv_nnc_tensor_view_get_inc(a, ainc);
	ccv_nnc_tensor_view_get_inc(b, binc);
	// Comparing N
	assert((a_offset == 0 ? a->info.dim[0] : 1) == (b_offset == 0 ? b->info.dim[0] : 1));
	const int n = (a_offset == 0 ? a->info.dim[0] : 1);
	// Comparing C
	assert(a->info.dim[a_nd - 1] == b->info.dim[1 - b_offset]);
	const int c = a->info.dim[a_nd - 1];
	// Comparing HW
	int hw[CCV_NNC_MAX_DIM];
	for (k = 0; k < CCV_NNC_MAX_DIM; k++)
	{
		assert(a->info.dim[k + 1 - a_offset] == b->info.dim[k + 2 - b_offset]);
		hw[k] = a->info.dim[k + 1 - a_offset];
	}
	assert(CCV_NNC_MAX_DIM == 2); // Need to change this logic for CCV_NNC_MAX_DIM == other number.
	int i[CCV_NNC_MAX_DIM + 2];
	float* ap = a->data.f32;
	float* bp = b->data.f32;
	// Non-optimal case, need to do skip copy.
	for (i[0] = 0; i[0] < n; i[0]++)
	{
		for (i[3] = 0; i[3] < c; i[3]++)
		{
			float* apu = ap + i[3];
			for (i[1] = 0; i[1] < hw[0]; i[1]++)
			{
				for (i[2] = 0; i[2] < hw[1]; i[2]++)
					bp[i[2]] = apu[i[2] * ainc[3]];
				apu += ainc[2] * ainc[3];
				bp += binc[3];
			}
			bp += (binc[2] - hw[0]) * binc[3];
		}
		ap += ainc[1] * ainc[2] * ainc[3];
		bp += (binc[1] - c) * binc[2] * binc[3];
	}
}