#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_3__* u8; } ;
struct TYPE_9__ {int size; scalar_t__ refcount; struct TYPE_9__* vector; TYPE_2__ data; TYPE_1__* index; } ;
typedef  TYPE_3__ ccv_sparse_matrix_t ;
typedef  int /*<<< orphan*/  ccv_matrix_t ;
typedef  TYPE_3__ ccv_dense_matrix_t ;
typedef  TYPE_3__ ccv_compressed_sparse_matrix_t ;
struct TYPE_7__ {scalar_t__ ifbit; } ;

/* Variables and functions */
 int CCV_MATRIX_CSC ; 
 int CCV_MATRIX_CSR ; 
 int CCV_MATRIX_DENSE ; 
 int CCV_MATRIX_SPARSE ; 
 int CCV_UNMANAGED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (TYPE_3__*) ; 

void ccv_matrix_free_immediately(ccv_matrix_t* mat)
{
	int type = *(int*)mat;
	assert(!(type & CCV_UNMANAGED));
	if (type & CCV_MATRIX_DENSE)
	{
		ccv_dense_matrix_t* dmt = (ccv_dense_matrix_t*)mat;
		dmt->refcount = 0;
		ccfree(dmt);
	} else if (type & CCV_MATRIX_SPARSE) {
		ccv_sparse_matrix_t* smt = (ccv_sparse_matrix_t*)mat;
		int i;
		for (i = 0; i < smt->size; i++)
			if (smt->index[i].ifbit)
				ccfree(smt->vector[i].data.u8);
		ccfree(smt->vector);
		ccfree(smt);
	} else if ((type & CCV_MATRIX_CSR) || (type & CCV_MATRIX_CSC)) {
		ccv_compressed_sparse_matrix_t* csm = (ccv_compressed_sparse_matrix_t*)mat;
		csm->refcount = 0;
		ccfree(csm);
	}
}