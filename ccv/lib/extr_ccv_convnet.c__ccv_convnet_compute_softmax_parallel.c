#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float* f32; } ;
struct TYPE_9__ {int cols; int rows; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_32F ; 
 int CCV_C1 ; 
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (float*) ; 
 scalar_t__ ccmalloc (int) ; 
 TYPE_2__* ccv_dense_matrix_renew (TYPE_2__*,int,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_zero (TYPE_2__*) ; 
 float expf (float) ; 

__attribute__((used)) static void _ccv_convnet_compute_softmax_parallel(ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, int type)
{
	assert(CCV_GET_CHANNEL(a->type) == CCV_C1);
	assert(CCV_GET_DATA_TYPE(a->type) == CCV_32F);
	ccv_dense_matrix_t* db = *b = ccv_dense_matrix_renew(*b, 1, a->cols, CCV_32F | CCV_C1, CCV_32F | CCV_C1, 0);
	ccv_zero(db);
	int i, j;
	float* aptr = a->data.f32;
	float* bptr = db->data.f32;
	float* cptr = (float*)ccmalloc(sizeof(float) * a->cols);
	for (i = 0; i < a->rows; i++)
	{
		double max = aptr[0];
		for (j = 1; j < a->cols; j++)
			if (aptr[j] > max)
				max = aptr[j];
		double tt = 0;
		for (j = 0; j < a->cols; j++)
			tt += (cptr[j] = expf(aptr[j] - max));
		tt = 1.0 / tt;
		for (j = 0; j < a->cols; j++)
			bptr[j] += cptr[j] * tt;
		aptr += a->cols;
	}
	ccfree(cptr);
}