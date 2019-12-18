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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  ccv_sparse_matrix_vector_t ;
struct TYPE_3__ {int rows; int cols; int type; int major; int prime_index; int size; int refcount; int /*<<< orphan*/ * vector; int /*<<< orphan*/ * index; scalar_t__ rnum; } ;
typedef  TYPE_1__ ccv_sparse_matrix_t ;
typedef  int /*<<< orphan*/  ccv_sparse_matrix_index_t ;

/* Variables and functions */
 int CCV_DENSE_VECTOR ; 
 int CCV_MATRIX_SPARSE ; 
 int CCV_SPARSE_VECTOR ; 
 scalar_t__ cccalloc (int,int) ; 
 scalar_t__ ccmalloc (int) ; 

ccv_sparse_matrix_t* ccv_sparse_matrix_new(int rows, int cols, int type, int major, uint64_t sig)
{
	ccv_sparse_matrix_t* mat;
	mat = (ccv_sparse_matrix_t*)ccmalloc(sizeof(ccv_sparse_matrix_t));
	mat->rows = rows;
	mat->cols = cols;
	mat->type = type | CCV_MATRIX_SPARSE | ((type & CCV_DENSE_VECTOR) ? CCV_DENSE_VECTOR : CCV_SPARSE_VECTOR);
	mat->major = major;
	mat->prime_index = 1; // See ccv_util.c to know why this is 1 and why size is 2.
	mat->size = 2;
	mat->rnum = 0;
	mat->refcount = 1;
	mat->index = (ccv_sparse_matrix_index_t*)cccalloc(sizeof(ccv_sparse_matrix_index_t), mat->size);
	mat->vector = (ccv_sparse_matrix_vector_t*)ccmalloc(sizeof(ccv_sparse_matrix_vector_t) * mat->size);
	return mat;
}