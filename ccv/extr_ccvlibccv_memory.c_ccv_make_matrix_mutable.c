#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_2__ {int /*<<< orphan*/  type; scalar_t__ sig; } ;
typedef  TYPE_1__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_MATRIX_DENSE ; 
 int /*<<< orphan*/  CCV_REUSABLE ; 

void ccv_make_matrix_mutable(ccv_matrix_t* mat)
{
	int type = *(int*)mat;
	if (type & CCV_MATRIX_DENSE)
	{
		ccv_dense_matrix_t* dmt = (ccv_dense_matrix_t*)mat;
		dmt->sig = 0;
		dmt->type &= ~CCV_REUSABLE;
	}
}