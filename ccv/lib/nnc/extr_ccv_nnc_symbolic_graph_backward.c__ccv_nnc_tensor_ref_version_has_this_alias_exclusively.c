#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int* dim; } ;
struct TYPE_12__ {scalar_t__ alias_ref; int* inc; int* ofs; TYPE_1__ info; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_13__ {TYPE_5__ const* const alias_registry; } ;
typedef  TYPE_3__ ccv_nnc_tensor_ref_t ;
struct TYPE_14__ {size_t d; } ;
typedef  TYPE_4__ ccv_nnc_autograd_tensor_symbol_t ;
struct TYPE_15__ {int rnum; } ;
typedef  TYPE_5__ ccv_array_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccv_array_get (TYPE_5__ const* const,int const) ; 
 scalar_t__ memcmp (int const*,int*,int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_ref_version_has_this_alias_exclusively(const ccv_nnc_tensor_ref_t* const tensor_ref, const ccv_array_t* const autograd_tensor_symbols, const ccv_nnc_tensor_symbol_info_t* const tensor_symbol_info, const ccv_nnc_tensor_symbol_info_t* const alias)
{
	assert(alias->alias_ref > 0);
	// No alias_registry, thus, cannot find the exact matched alias.
	if (!tensor_ref->alias_registry)
		return 0;
	int i;
	for (i = 0; i < tensor_ref->alias_registry->rnum; i++)
	{
		const int d = *(int*)ccv_array_get(tensor_ref->alias_registry, i);
		assert(d < autograd_tensor_symbols->rnum);
		ccv_nnc_autograd_tensor_symbol_t* autograd = (ccv_nnc_autograd_tensor_symbol_t*)ccv_array_get(autograd_tensor_symbols, d);
		// This must reference to an alias.
		assert(tensor_symbol_info[autograd->d].alias_ref);
		const int* inc = tensor_symbol_info[autograd->d].inc;
		const int* ofs = tensor_symbol_info[autograd->d].ofs;
		const int* dim = tensor_symbol_info[autograd->d].info.dim;
		if (memcmp(inc, alias->inc, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC) != 0 ||
			memcmp(ofs, alias->ofs, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC) != 0 ||
			memcmp(dim, alias->info.dim, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC) != 0)
			return 0;
	}
	// If everything matches for every alias in registry, we can use any of the alias directly.
	return 1;
}