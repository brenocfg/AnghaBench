#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ major; int cols; int rows; } ;
typedef  TYPE_2__ ccv_sparse_matrix_t ;
struct TYPE_8__ {scalar_t__ u8; } ;
struct TYPE_10__ {int type; int* offset; int* index; TYPE_1__ data; int /*<<< orphan*/  cols; int /*<<< orphan*/  rows; } ;
typedef  TYPE_3__ ccv_compressed_sparse_matrix_t ;

/* Variables and functions */
 int CCV_GET_DATA_TYPE_SIZE (int) ; 
 int CCV_MATRIX_CSC ; 
 int CCV_MATRIX_CSR ; 
 scalar_t__ CCV_SPARSE_COL_MAJOR ; 
 scalar_t__ CCV_SPARSE_ROW_MAJOR ; 
 int /*<<< orphan*/  ccv_set_sparse_matrix_cell (TYPE_2__*,int,int,scalar_t__) ; 
 TYPE_2__* ccv_sparse_matrix_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__,int /*<<< orphan*/ ) ; 

void ccv_decompress_sparse_matrix(const ccv_compressed_sparse_matrix_t* csm, ccv_sparse_matrix_t** smt)
{
	ccv_sparse_matrix_t* mat = *smt = ccv_sparse_matrix_new(csm->rows, csm->cols, csm->type & ~CCV_MATRIX_CSR & ~CCV_MATRIX_CSC, (csm->type & CCV_MATRIX_CSR) ? CCV_SPARSE_ROW_MAJOR : CCV_SPARSE_COL_MAJOR, 0);
	int i, j;
	for (i = 0; i < ((mat->major == CCV_SPARSE_COL_MAJOR) ? mat->cols : mat->rows); i++)
		for (j = csm->offset[i]; j < csm->offset[i + 1]; j++)
			if (mat->major == CCV_SPARSE_COL_MAJOR)
				ccv_set_sparse_matrix_cell(mat, csm->index[j], i, csm->data.u8 + CCV_GET_DATA_TYPE_SIZE(csm->type) * j);
			else
				ccv_set_sparse_matrix_cell(mat, i, csm->index[j], csm->data.u8 + CCV_GET_DATA_TYPE_SIZE(csm->type) * j);
}