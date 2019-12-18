#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int* dim; int /*<<< orphan*/  datatype; } ;
struct TYPE_5__ {int /*<<< orphan*/ * u8; } ;
struct TYPE_6__ {int* inc; TYPE_3__ info; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_nnc_tensor_view_t ;

/* Variables and functions */
 size_t CCV_GET_DATA_TYPE_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_2__*) ; 
 int /*<<< orphan*/  CCV_NNC_MAX_DIM_ALLOC ; 
 int /*<<< orphan*/  assert (int) ; 
 int ccv_max (int,int) ; 
 size_t const ccv_nnc_tensor_count (TYPE_3__) ; 
 int ccv_nnc_tensor_nd (int*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t const) ; 

void ccv_nnc_tensor_zero(void* const tensor)
{
	ccv_nnc_tensor_view_t* tv = (ccv_nnc_tensor_view_t*)tensor;
	const size_t data_size = CCV_GET_DATA_TYPE_SIZE(tv->info.datatype);
	if (!CCV_IS_TENSOR_VIEW(tv))
	{
		memset(tv->data.u8, 0, data_size * ccv_nnc_tensor_count(tv->info));
		return;
	}
	const int nd = ccv_nnc_tensor_nd(tv->info.dim);
	assert(nd >= 1);
	const int* const tvinc = tv->inc;
	// reset it to 0.
	int c, x, y;
	int count = 1;
	int mod[CCV_NNC_MAX_DIM_ALLOC - 3];
	size_t mod_inc[CCV_NNC_MAX_DIM_ALLOC - 2];
	const size_t top_mod_inc = nd > 2 ? data_size * tvinc[nd - 3] * tvinc[nd - 2] * tvinc[nd - 1] : data_size;
	if (nd > 2)
		mod_inc[nd - 3] = top_mod_inc;
	for (c = nd - 4; c >= 0; c--)
	{
		// Compute the mod.
		mod[c] = c == nd - 4 ? tv->info.dim[c] : mod[c + 1] * tv->info.dim[c];
		mod_inc[c] = mod_inc[c + 1] * tvinc[c];
		count *= tv->info.dim[c];
	}
	for (c = 0; c < nd - 3; c++)
		mod_inc[c] = mod_inc[c + 1] * (tvinc[c] - tv->info.dim[c]);
	uint8_t* tvd = tv->data.u8;
	const size_t tvinc_1 = data_size * tvinc[nd - 1];
	const size_t tvinc_21 = tvinc_1 * (nd >= 2 ? tvinc[nd - 2] : 1);
	const size_t tvdim_1 = data_size * tv->info.dim[nd - 1];
	const int max_y = ccv_max(1, nd >= 3 ? tv->info.dim[nd - 3] : 1);
	const int max_x = ccv_max(1, nd >= 2 ? tv->info.dim[nd - 2] : 1);
	for (c = 0; c < count; c++)
	{
		for (y = 0; y < max_y; y++)
		{
			uint8_t* tvp = tvd + y * tvinc_21;
			for (x = 0; x < max_x; x++)
			{
				memset(tvp, 0, tvdim_1);
				tvp += tvinc_1;
			}
		}
		tvd += top_mod_inc;
		for (y = nd - 4; y >= 0; y--)
			if ((c + 1) % mod[y] != 0)
				break; // cannot be mod, break out.
			else
				tvd += mod_inc[y];
	}
}