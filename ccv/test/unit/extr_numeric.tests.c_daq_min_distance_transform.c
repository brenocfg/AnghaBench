#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned char* u8; float* f32; } ;
struct TYPE_8__ {int rows; int cols; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_32F ; 
 int CCV_C1 ; 
 scalar_t__ calloc (int,int) ; 
 TYPE_2__* ccv_dense_matrix_new (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_2__*) ; 
 int /*<<< orphan*/  ccv_matrix_getter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_min1d (float*,float*,int*,int,int,double,double) ; 
 int /*<<< orphan*/  for_block ; 
 int /*<<< orphan*/  free (int*) ; 

void daq_min_distance_transform(ccv_dense_matrix_t* a, ccv_dense_matrix_t** b, double dx, double dy, double dxx, double dyy)
{
	ccv_dense_matrix_t* dc = ccv_dense_matrix_new(a->rows, a->cols, CCV_32F | CCV_C1, 0, 0);
	ccv_dense_matrix_t* db = *b = ccv_dense_matrix_new(a->rows, a->cols, CCV_32F | CCV_C1, 0, 0);
	unsigned char* a_ptr = a->data.u8;
	float* b_ptr = db->data.f32;
	int i, j;
#define for_block(_, _for_get) \
	for (i = 0; i < a->rows; i++) \
	{ \
		for (j = 0; j < a->cols; j++) \
			b_ptr[j] = _for_get(a_ptr, j, 0); \
		b_ptr += db->cols; \
		a_ptr += a->step; \
	}
	ccv_matrix_getter(a->type, for_block);
#undef for_block
	int* ix = (int*)calloc(a->cols * a->rows, sizeof(int));
	int* iy = (int*)calloc(a->cols * a->rows, sizeof(int));
	b_ptr = db->data.f32;
	float* c_ptr = dc->data.f32;
	for (i = 0; i < a->rows; i++)
		dt_min1d(b_ptr + i * a->cols, c_ptr + i * a->cols, ix + i * a->cols, 1, a->cols, dxx, dx);
	for (j = 0; j < a->cols; j++)
		dt_min1d(c_ptr + j, b_ptr + j, iy + j, a->cols, a->rows, dyy, dy);
	free(ix);
	free(iy);
	ccv_matrix_free(dc);
}