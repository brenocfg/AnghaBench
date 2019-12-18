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
typedef  int /*<<< orphan*/  ccv_nnc_graph_tensor_wrap_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void _ccv_nnc_graph_tensor_wrap_free(ccv_nnc_graph_tensor_wrap_t* const tensor_wrap)
{
	ccfree(tensor_wrap);
}