#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_13__ {TYPE_3__ data; } ;
typedef  TYPE_4__ ccv_nnc_tensor_t ;
struct TYPE_14__ {size_t d; scalar_t__ graph; } ;
typedef  TYPE_5__ ccv_nnc_tensor_symbol_t ;
struct TYPE_15__ {intptr_t graph_ref; size_t vt_tensor_size; TYPE_2__** vt_tensors; } ;
typedef  TYPE_6__ ccv_nnc_tensor_arena_t ;
struct TYPE_10__ {int /*<<< orphan*/  ptr; } ;
struct TYPE_11__ {TYPE_1__ data; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

void ccv_nnc_tensor_bind_symbol(const ccv_nnc_tensor_arena_t* const tensor_arena, const ccv_nnc_tensor_symbol_t symbol, const ccv_nnc_tensor_t* const tensor)
{
	assert(tensor_arena->graph_ref == (intptr_t)symbol.graph);
	assert(symbol.d < tensor_arena->vt_tensor_size);
	tensor_arena->vt_tensors[symbol.d]->data.ptr = tensor->data.ptr;
}