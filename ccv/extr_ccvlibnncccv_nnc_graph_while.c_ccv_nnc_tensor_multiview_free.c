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
struct TYPE_3__ {scalar_t__ _heap_data; scalar_t__ sp; } ;
typedef  TYPE_1__ ccv_nnc_tensor_multiview_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (scalar_t__) ; 
 int /*<<< orphan*/  ccv_array_free (scalar_t__) ; 

void ccv_nnc_tensor_multiview_free(const ccv_nnc_tensor_multiview_t tensor_multiview)
{
	if (tensor_multiview.sp)
		ccv_array_free(tensor_multiview.sp);
	if (tensor_multiview._heap_data)
		ccfree(tensor_multiview._heap_data);
}