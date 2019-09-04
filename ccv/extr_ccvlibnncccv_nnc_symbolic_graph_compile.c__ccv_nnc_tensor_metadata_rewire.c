#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int kind; int repeat; TYPE_3__* sp; struct TYPE_10__* p; struct TYPE_10__* alias_ref; } ;
typedef  TYPE_1__ ccv_nnc_tensor_t ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
struct TYPE_11__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ CCV_IS_TENSOR_MULTIVIEW (TYPE_1__* const) ; 
 scalar_t__ CCV_NNC_IS_METADATA_POS (TYPE_1__* const) ; 
 TYPE_1__** CCV_NNC_MULTIVIEW_DATA (TYPE_1__*) ; 
 void* _ccv_nnc_tensor_metadata_get (int /*<<< orphan*/  const* const,int const) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 

__attribute__((used)) static ccv_nnc_tensor_t* _ccv_nnc_tensor_metadata_rewire(const ccv_array_t* const tensor_metadata, ccv_nnc_tensor_t* const vt_tensor)
{
	// If the low bit is not 1, this is not a position (but a normal tensor pointer), just return directly.
	if (!CCV_NNC_IS_METADATA_POS(vt_tensor))
		return vt_tensor;
	ccv_nnc_tensor_t* const tensor = _ccv_nnc_tensor_metadata_get(tensor_metadata, (int)(intptr_t)vt_tensor);
	if (tensor->alias_ref && CCV_NNC_IS_METADATA_POS(tensor->alias_ref))
	{
		const int alias_ref = tensor->alias_ref;
		tensor->alias_ref = (uintptr_t)_ccv_nnc_tensor_metadata_get(tensor_metadata, (int)tensor->alias_ref);
		_ccv_nnc_tensor_metadata_rewire(tensor_metadata, (ccv_nnc_tensor_t*)(intptr_t)alias_ref);
	}
	if (CCV_IS_TENSOR_MULTIVIEW(tensor))
	{
		ccv_nnc_tensor_multiview_t* mv = (ccv_nnc_tensor_multiview_t*)tensor;
		int i;
		const int count = mv->kind + mv->repeat;
		for (i = 0; i < count; i++)
		{
			if (CCV_NNC_IS_METADATA_POS(CCV_NNC_MULTIVIEW_DATA(mv)[i]))
			{
				const int pos = (int)(intptr_t)CCV_NNC_MULTIVIEW_DATA(mv)[i];
				CCV_NNC_MULTIVIEW_DATA(mv)[i] = _ccv_nnc_tensor_metadata_get(tensor_metadata, (int)(intptr_t)CCV_NNC_MULTIVIEW_DATA(mv)[i]);
				_ccv_nnc_tensor_metadata_rewire(tensor_metadata, (ccv_nnc_tensor_t*)(intptr_t)pos);
			}
		}
		// No need to recursively do parent pointer, otherwise we are in deep rewire.
		if (mv->p && CCV_NNC_IS_METADATA_POS(mv->p))
			mv->p = (ccv_nnc_tensor_multiview_t*)_ccv_nnc_tensor_metadata_get(tensor_metadata, (int)(intptr_t)mv->p);
		if (mv->sp)
			for (i = 0; i < mv->sp->rnum; i++)
			{
				ccv_nnc_tensor_t** const tensor = (ccv_nnc_tensor_t**)ccv_array_get(mv->sp, i);
				if (CCV_NNC_IS_METADATA_POS(*tensor))
				{
					const int pos = (int)(intptr_t)*tensor;
					*tensor = _ccv_nnc_tensor_metadata_get(tensor_metadata, pos);
					assert(!CCV_IS_TENSOR_MULTIVIEW(*tensor));
					_ccv_nnc_tensor_metadata_rewire(tensor_metadata, (ccv_nnc_tensor_t*)(intptr_t)pos);
				}
			}
	}
	return tensor;
}