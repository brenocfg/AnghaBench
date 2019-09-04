#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tape_tensor_data_array_t ;
struct TYPE_5__ {int rnum; } ;
typedef  TYPE_1__ ccv_array_t ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  ccv_array_resize (TYPE_1__* const,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _ccv_nnc_tape_tensor_data_array_pos_new(ccv_array_t* const tensor_data, int* const pos_ref, ccv_nnc_tape_tensor_data_array_t** const tape_tensor_data_ref)
{
	int pos = tensor_data->rnum;
	ccv_array_resize(tensor_data, pos + 1);
	*pos_ref = (pos << 1) | 1;
	ccv_nnc_tape_tensor_data_array_t* const tape_tensor_data = (ccv_nnc_tape_tensor_data_array_t*)ccv_array_get(tensor_data, pos);
	memset(tape_tensor_data, 0, sizeof(ccv_nnc_tape_tensor_data_array_t));
	*tape_tensor_data_ref = tape_tensor_data;
}