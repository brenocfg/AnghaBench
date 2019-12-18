#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {float* u8; float* f32; } ;
struct TYPE_12__ {scalar_t__ datatype; } ;
struct TYPE_11__ {TYPE_1__ data; TYPE_6__ info; } ;
typedef  TYPE_2__ const ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int CCV_GET_DATA_TYPE_SIZE (scalar_t__) ; 
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_2__ const* const) ; 
 int CCV_NNC_MAX_DIM ; 
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_count (TYPE_6__) ; 
 int ccv_nnc_tensor_view_check_dim (TYPE_2__ const* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_dim (TYPE_2__ const* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_inc (TYPE_2__ const* const,int*) ; 
 int /*<<< orphan*/  memcpy (float*,float*,int) ; 

void _ccv_nnc_tensor_transfer_cpu_ref(const ccv_nnc_tensor_view_t* const a, ccv_nnc_tensor_view_t* const b)
{
	// Assuming this is float 32.
	assert(a->info.datatype == b->info.datatype);
	if (!CCV_IS_TENSOR_VIEW(a) && !CCV_IS_TENSOR_VIEW(b))
	{
		// Super optimal case, just do memcpy.
		memcpy(b->data.u8, a->data.u8, ccv_nnc_tensor_count(a->info) * CCV_GET_DATA_TYPE_SIZE(a->info.datatype));
		return;
	}
	int dim[CCV_NNC_MAX_DIM_ALLOC];
	int ainc[CCV_NNC_MAX_DIM_ALLOC];
	int binc[CCV_NNC_MAX_DIM_ALLOC];
	ccv_nnc_tensor_view_get_dim(a, dim);
	assert(ccv_nnc_tensor_view_check_dim(b, dim));
	ccv_nnc_tensor_view_get_inc(a, ainc);
	ccv_nnc_tensor_view_get_inc(b, binc);
	assert(CCV_NNC_MAX_DIM == 2); // Need to change this logic for CCV_NNC_MAX_DIM == other number.
	int i[CCV_NNC_MAX_DIM + 2];
	float* ap = a->data.f32;
	float* bp = b->data.f32;
	if (ainc[3] == dim[3] && binc[3] == dim[3])
	{
		// Special casing if the ainc[3] is the same as dim[3] (do memcpy for the last two dim)
		for (i[0] = 0; i[0] < dim[0]; i[0]++)
		{
			for (i[1] = 0; i[1] < dim[1]; i[1]++)
			{
				memcpy(bp, ap, dim[2] * dim[3] * sizeof(float));
				ap += ainc[2] * ainc[3];
				bp += binc[2] * binc[3];
			}
			ap += (ainc[1] - dim[1]) * ainc[2] * ainc[3];
			bp += (binc[1] - dim[1]) * binc[2] * binc[3];
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
				memcpy(bp, ap, dim[3] * sizeof(float));
				ap += ainc[3];
				bp += binc[3];
			}
			ap += (ainc[2] - dim[2]) * ainc[3];
			bp += (binc[2] - dim[2]) * binc[3];
		}
		ap += (ainc[1] - dim[1]) * ainc[2] * ainc[3];
		bp += (binc[1] - dim[1]) * binc[2] * binc[3];
	}
}