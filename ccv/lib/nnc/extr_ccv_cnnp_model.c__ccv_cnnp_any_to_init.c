#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int d; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_t ;
struct TYPE_6__ {unsigned int* v; } ;
struct TYPE_8__ {TYPE_1__ tensors_init; TYPE_4__* retainables; TYPE_4__* trainables; } ;
typedef  TYPE_3__ ccv_cnnp_compiled_data_t ;
struct TYPE_9__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_4__*,int) ; 

__attribute__((used)) static int _ccv_cnnp_any_to_init(const ccv_cnnp_compiled_data_t* const compiled_data)
{
	int i;
	for (i = 0; i < compiled_data->trainables->rnum; i++)
	{
		const int d = ((ccv_nnc_tensor_symbol_t*)ccv_array_get(compiled_data->trainables, i))->d;
		if (!(compiled_data->tensors_init.v[d >> 5] & (1u << (d & 0x1f))))
			return 1;
	}
	for (i = 0; i < compiled_data->retainables->rnum; i++)
	{
		const int d = ((ccv_nnc_tensor_symbol_t*)ccv_array_get(compiled_data->retainables, i))->d;
		if (!(compiled_data->tensors_init.v[d >> 5] & (1u << (d & 0x1f))))
			return 1;
	}
	return 0;
}