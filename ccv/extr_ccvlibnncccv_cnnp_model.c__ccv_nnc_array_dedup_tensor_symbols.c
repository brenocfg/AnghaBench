#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ d; scalar_t__ graph; } ;
typedef  TYPE_1__ ccv_nnc_tensor_symbol_t ;
struct TYPE_6__ {int rnum; } ;
typedef  TYPE_2__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_2__* const,int) ; 

__attribute__((used)) static void _ccv_nnc_array_dedup_tensor_symbols(ccv_array_t* const tensor_symbols)
{
	int i, j;
	for (i = 0; i < tensor_symbols->rnum; i++)
	{
		ccv_nnc_tensor_symbol_t* const tensor_symbol = (ccv_nnc_tensor_symbol_t*)ccv_array_get(tensor_symbols, i);
		// Check whether this tensor symbol has any duplicate.
		for (j = i + 1; j < tensor_symbols->rnum;)
		{
			ccv_nnc_tensor_symbol_t* const other_symbol = (ccv_nnc_tensor_symbol_t*)ccv_array_get(tensor_symbols, j);
			// If there is a same tensor symbol, remove it.
			if (other_symbol->d == tensor_symbol->d && other_symbol->graph == tensor_symbol->graph)
			{
				if (j + 1 < tensor_symbols->rnum)
					*other_symbol = *(ccv_nnc_tensor_symbol_t*)ccv_array_get(tensor_symbols, tensor_symbols->rnum - 1);
				--tensor_symbols->rnum;
				continue;
			}
			++j;
		}
	}
}