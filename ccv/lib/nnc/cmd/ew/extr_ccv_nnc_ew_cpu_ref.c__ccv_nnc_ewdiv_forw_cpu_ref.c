#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float* f32; } ;
struct TYPE_13__ {scalar_t__* dim; } ;
struct TYPE_12__ {TYPE_1__ data; TYPE_6__ info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_2__* const) ; 
 int CCV_NNC_MAX_DIM ; 
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_count (TYPE_6__) ; 
 int ccv_nnc_tensor_view_check_dim (TYPE_2__* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_dim (TYPE_2__* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_inc (TYPE_2__* const,int*) ; 

__attribute__((used)) static void _ccv_nnc_ewdiv_forw_cpu_ref(const float p, ccv_nnc_tensor_view_t* const a, ccv_nnc_tensor_view_t* const b, ccv_nnc_tensor_view_t* const c)
{
	// Assuming this is float 32.
	int dim[CCV_NNC_MAX_DIM_ALLOC];
	int ainc[CCV_NNC_MAX_DIM_ALLOC];
	int binc[CCV_NNC_MAX_DIM_ALLOC];
	int cinc[CCV_NNC_MAX_DIM_ALLOC];
	if (a == 0) // Take 0 as all ones tensor.
	{
		assert(b->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
		assert(c->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
		ccv_nnc_tensor_view_get_dim(b, dim);
		assert(ccv_nnc_tensor_view_check_dim(c, dim));
		int x;
		if (!CCV_IS_TENSOR_VIEW(b) && !CCV_IS_TENSOR_VIEW(c))
		{
			// Super optimal case, just do one for-loop for sum.
			const int tensor_count = ccv_nnc_tensor_count(b->info);
			for (x = 0; x < tensor_count; x++)
				c->data.f32[x] = p / b->data.f32[x];
			return;
		}
		assert(CCV_NNC_MAX_DIM == 2); // Need to change this logic for CCV_NNC_MAX_DIM == other number.
		ccv_nnc_tensor_view_get_inc(b, binc);
		ccv_nnc_tensor_view_get_inc(c, cinc);
		int i[CCV_NNC_MAX_DIM + 2];
		float* bp = b->data.f32;
		float* cp = c->data.f32;
		const int count = dim[2] * dim[3];
		if (binc[3] == dim[3] && cinc[3] == dim[3])
		{
			// Special casing if the ainc[3] is the same as dim[3]
			for (i[0] = 0; i[0] < dim[0]; i[0]++)
			{
				for (i[1] = 0; i[1] < dim[1]; i[1]++)
				{
					for (x = 0; x < count; x++)
						cp[x] = p / bp[x];
					bp += binc[2] * binc[3];
					cp += cinc[2] * cinc[3];
				}
				bp += (binc[1] - dim[1]) * binc[2] * binc[3];
				cp += (cinc[1] - dim[1]) * cinc[2] * cinc[3];
			}
			return;
		}
		// Non-optimal case, need to do skip copy.
		for (i[0] = 0; i[0] < dim[0]; i[0]++)
		{
			for (i[1] = 0; i[1] < dim[1]; i[1]++)
			{
				for (i[2] = 0; i[2] < dim[2]; i[2]++)
				{
					for (x = 0; x < dim[3]; x++)
						cp[x] = p / bp[x];
					bp += binc[3];
					cp += cinc[3];
				}
				bp += (binc[2] - dim[2]) * binc[3];
				cp += (cinc[2] - dim[2]) * cinc[3];
			}
			bp += (binc[1] - dim[1]) * binc[2] * binc[3];
			cp += (cinc[1] - dim[1]) * cinc[2] * cinc[3];
		}
	} else {
		assert(a->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
		assert(b->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
		assert(c->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
		ccv_nnc_tensor_view_get_dim(a, dim);
		assert(ccv_nnc_tensor_view_check_dim(b, dim));
		assert(ccv_nnc_tensor_view_check_dim(c, dim));
		int x;
		if (!CCV_IS_TENSOR_VIEW(a) && !CCV_IS_TENSOR_VIEW(b) && !CCV_IS_TENSOR_VIEW(c))
		{
			// Super optimal case, just do one for-loop for sum.
			const int tensor_count = ccv_nnc_tensor_count(a->info);
			for (x = 0; x < tensor_count; x++)
				c->data.f32[x] = p * a->data.f32[x] / b->data.f32[x];
			return;
		}
		assert(CCV_NNC_MAX_DIM == 2); // Need to change this logic for CCV_NNC_MAX_DIM == other number.
		ccv_nnc_tensor_view_get_inc(a, ainc);
		ccv_nnc_tensor_view_get_inc(b, binc);
		ccv_nnc_tensor_view_get_inc(c, cinc);
		int i[CCV_NNC_MAX_DIM + 2];
		float* ap = a->data.f32;
		float* bp = b->data.f32;
		float* cp = c->data.f32;
		const int count = dim[2] * dim[3];
		if (ainc[3] == dim[3] && binc[3] == dim[3] && cinc[3] == dim[3])
		{
			// Special casing if the ainc[3] is the same as dim[3]
			for (i[0] = 0; i[0] < dim[0]; i[0]++)
			{
				for (i[1] = 0; i[1] < dim[1]; i[1]++)
				{
					for (x = 0; x < count; x++)
						cp[x] = p * ap[x] / bp[x];
					ap += ainc[2] * ainc[3];
					bp += binc[2] * binc[3];
					cp += cinc[2] * cinc[3];
				}
				ap += (ainc[1] - dim[1]) * ainc[2] * ainc[3];
				bp += (binc[1] - dim[1]) * binc[2] * binc[3];
				cp += (cinc[1] - dim[1]) * cinc[2] * cinc[3];
			}
			return;
		}
		// Non-optimal case, need to do skip copy.
		for (i[0] = 0; i[0] < dim[0]; i[0]++)
		{
			for (i[1] = 0; i[1] < dim[1]; i[1]++)
			{
				for (i[2] = 0; i[2] < dim[2]; i[2]++)
				{
					for (x = 0; x < dim[3]; x++)
						cp[x] = p * ap[x] / bp[x];
					ap += ainc[3];
					bp += binc[3];
					cp += cinc[3];
				}
				ap += (ainc[2] - dim[2]) * ainc[3];
				bp += (binc[2] - dim[2]) * binc[3];
				cp += (cinc[2] - dim[2]) * cinc[3];
			}
			ap += (ainc[1] - dim[1]) * ainc[2] * ainc[3];
			bp += (binc[1] - dim[1]) * binc[2] * binc[3];
			cp += (cinc[1] - dim[1]) * cinc[2] * cinc[3];
		}
	}
}