#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_view_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ * const) ; 

void ccv_nnc_tensor_view_free(ccv_nnc_tensor_view_t* const tensor_view)
{
	ccfree(tensor_view);
}