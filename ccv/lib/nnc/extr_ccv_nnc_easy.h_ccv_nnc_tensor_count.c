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
struct TYPE_3__ {int /*<<< orphan*/  dim; } ;
typedef  TYPE_1__ ccv_nnc_tensor_param_t ;

/* Variables and functions */
 size_t ccv_nnc_dimension_count (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline size_t ccv_nnc_tensor_count(const ccv_nnc_tensor_param_t params)
{
	return ccv_nnc_dimension_count(params.dim);
}