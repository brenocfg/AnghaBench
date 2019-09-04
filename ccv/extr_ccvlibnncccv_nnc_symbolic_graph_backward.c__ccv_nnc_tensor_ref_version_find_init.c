#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ x; } ;
typedef  TYPE_1__ ccv_nnc_tensor_ref_t ;
struct TYPE_6__ {TYPE_3__* ref_version; } ;
typedef  TYPE_2__ ccv_nnc_autograd_tensor_version_t ;
struct TYPE_7__ {int rnum; } ;

/* Variables and functions */
 scalar_t__ ccv_array_get (TYPE_3__*,int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_ref_version_find_init(const ccv_nnc_autograd_tensor_version_t* const tensor_ver)
{
	int i;
	for (i = 0; i < tensor_ver->ref_version->rnum; i++)
		if (((ccv_nnc_tensor_ref_t*)ccv_array_get(tensor_ver->ref_version, i))->x < 0)
			return i;
	return -1;
}