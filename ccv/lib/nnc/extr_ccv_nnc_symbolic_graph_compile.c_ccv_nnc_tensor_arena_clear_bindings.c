#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int vt_tensor_size; int /*<<< orphan*/ * pb_vt_tensors; TYPE_1__** vt_tensors; } ;
typedef  TYPE_2__ ccv_nnc_tensor_arena_t ;
struct TYPE_4__ {int /*<<< orphan*/  data; } ;

/* Variables and functions */

void ccv_nnc_tensor_arena_clear_bindings(ccv_nnc_tensor_arena_t* const tensor_arena)
{
	if (!tensor_arena->pb_vt_tensors)
		return;
	int i;
	for (i = 0; i < tensor_arena->vt_tensor_size; i++)
		if (tensor_arena->vt_tensors[i])
			tensor_arena->vt_tensors[i]->data = tensor_arena->pb_vt_tensors[i];
}