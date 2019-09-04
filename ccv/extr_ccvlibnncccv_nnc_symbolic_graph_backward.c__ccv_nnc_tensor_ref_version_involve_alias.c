#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {scalar_t__ alias_ref; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_13__ {TYPE_4__ const* const alias_registry; } ;
typedef  TYPE_2__ ccv_nnc_tensor_ref_t ;
struct TYPE_14__ {int d; } ;
typedef  TYPE_3__ ccv_nnc_autograd_tensor_symbol_t ;
struct TYPE_15__ {int rnum; } ;
typedef  TYPE_4__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_4__ const* const,int const) ; 
 scalar_t__ ccv_nnc_over_tensor_symbol_aliases (TYPE_1__ const* const,TYPE_1__ const* const) ; 

__attribute__((used)) static int _ccv_nnc_tensor_ref_version_involve_alias(const ccv_nnc_tensor_ref_t* const tensor_ref, const ccv_array_t* const autograd_tensor_symbols, const ccv_nnc_tensor_symbol_info_t* const tensor_symbol_info, const ccv_nnc_tensor_symbol_info_t* const alias)
{
	assert(alias->alias_ref > 0);
	// No alias_registry, must conflict (owns the whole band).
	if (!tensor_ref->alias_registry)
		return 1;
	int i;
	for (i = 0; i < tensor_ref->alias_registry->rnum; i++)
	{
		const int d = *(int*)ccv_array_get(tensor_ref->alias_registry, i);
		assert(d < autograd_tensor_symbols->rnum);
		ccv_nnc_autograd_tensor_symbol_t* autograd = (ccv_nnc_autograd_tensor_symbol_t*)ccv_array_get(autograd_tensor_symbols, d);
		if (ccv_nnc_over_tensor_symbol_aliases(tensor_symbol_info + autograd->d, alias))
			return 1;
	}
	// All aliases referenced by this ref_version doesn't overlap with the provided one, thus, there is no conflict at all.
	return 0;
}