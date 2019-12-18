#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_4__ {int /*<<< orphan*/  datatype; } ;
typedef  TYPE_1__ ccv_nnc_tensor_param_t ;

/* Variables and functions */
 int CCV_GET_DATA_TYPE_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ ccv_nnc_tensor_count (TYPE_1__ const) ; 

__attribute__((used)) static inline size_t ccv_nnc_tensor_data_size(const ccv_nnc_tensor_param_t params)
{
	return (CCV_GET_DATA_TYPE_SIZE(params.datatype) * (ssize_t)ccv_nnc_tensor_count(params) + 15) & -16;
}