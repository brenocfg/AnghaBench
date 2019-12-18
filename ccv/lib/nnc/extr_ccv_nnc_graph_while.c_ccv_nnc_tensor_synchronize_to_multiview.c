#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_t ;
struct TYPE_3__ {scalar_t__ sp; } ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;

/* Variables and functions */
 scalar_t__ ccv_array_new (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_array_push (scalar_t__,int /*<<< orphan*/ * const*) ; 

void ccv_nnc_tensor_synchronize_to_multiview(ccv_nnc_tensor_multiview_t* const tensor_multiview, ccv_nnc_tensor_t* const tensor)
{
	if (!tensor_multiview->sp)
		tensor_multiview->sp = ccv_array_new(sizeof(ccv_nnc_tensor_t*), 0, 0);
	ccv_array_push(tensor_multiview->sp, &tensor);
}