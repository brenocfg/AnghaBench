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
typedef  int /*<<< orphan*/  ccv_sparse_matrix_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;

/* Variables and functions */
 int CCV_MATRIX_SPARSE ; 

ccv_sparse_matrix_t* ccv_get_sparse_matrix(ccv_matrix_t* mat)
{
	int type = *(int*)mat;
	if (type & CCV_MATRIX_SPARSE)
		return (ccv_sparse_matrix_t*)mat;
	return 0;
}