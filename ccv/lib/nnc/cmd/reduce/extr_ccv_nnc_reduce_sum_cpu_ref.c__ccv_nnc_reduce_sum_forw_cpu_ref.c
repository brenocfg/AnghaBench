#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {float* f32; } ;
struct TYPE_10__ {scalar_t__* dim; } ;
struct TYPE_12__ {TYPE_2__ data; TYPE_1__ info; } ;
typedef  TYPE_3__ ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM ; 
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_nnc_tensor_view_check_broadcast_dim (TYPE_3__* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_dim (TYPE_3__* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_view_get_inc (TYPE_3__* const,int*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_zero (TYPE_3__* const) ; 

void _ccv_nnc_reduce_sum_forw_cpu_ref(ccv_nnc_tensor_view_t* const a, ccv_nnc_tensor_view_t* const b)
{
	assert(a->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
	assert(b->info.dim[CCV_NNC_MAX_DIM + 2] == 0);
	// Assuming this is float 32.
	int adim[CCV_NNC_MAX_DIM_ALLOC];
	int bdim[CCV_NNC_MAX_DIM_ALLOC];
	ccv_nnc_tensor_view_get_dim(a, adim);
	ccv_nnc_tensor_view_get_dim(b, bdim);
	assert(ccv_nnc_tensor_view_check_broadcast_dim(b, adim));
	int ainc[CCV_NNC_MAX_DIM_ALLOC];
	int binc[CCV_NNC_MAX_DIM_ALLOC];
	assert(CCV_NNC_MAX_DIM == 2); // Need to change this logic for CCV_NNC_MAX_DIM == other number.
	ccv_nnc_tensor_view_get_inc(a, ainc);
	ccv_nnc_tensor_view_get_inc(b, binc);
	int i[CCV_NNC_MAX_DIM + 2];
	int x;
	ccv_nnc_tensor_zero(b);
	float* ap = a->data.f32;
	float* const bp = b->data.f32;
	// Non-optimal case, need to do skip if needed.
	for (i[0] = 0; i[0] < adim[0]; i[0]++)
	{
		float* const bp0 = bdim[0] == 1 ? bp : bp + i[0] * binc[1] * binc[2] * binc[3];
		for (i[1] = 0; i[1] < adim[1]; i[1]++)
		{
			float* const bp1 = bdim[1] == 1 ? bp0 : bp0 + i[1] * binc[2] * binc[3];
			for (i[2] = 0; i[2] < adim[2]; i[2]++)
			{
				float* const bp2 = bdim[2] == 1 ? bp1 : bp1 + i[2] * binc[3];
				if (bdim[3] == 1)
					for (x = 0; x < adim[3]; x++)
						bp2[0] += ap[x];
				else
					for (x = 0; x < adim[3]; x++)
						bp2[x] += ap[x];
				ap += ainc[3];
			}
			ap += (ainc[2] - adim[2]) * ainc[3];
		}
		ap += (ainc[1] - adim[1]) * ainc[2] * ainc[3];
	}
}