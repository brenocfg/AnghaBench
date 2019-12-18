#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {unsigned char* u8; } ;
struct TYPE_10__ {int rows; int cols; int step; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_8U ; 
 int CCV_C1 ; 
 int /*<<< orphan*/  ccfree (int*) ; 
 scalar_t__ ccmalloc (int) ; 
 size_t ccv_clamp (int,int /*<<< orphan*/ ,int) ; 
 TYPE_2__* ccv_dense_matrix_new (int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int ccv_get_dense_matrix_cell_value (TYPE_2__*,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_free (TYPE_2__*) ; 

__attribute__((used)) static void _ccv_filter_direct_8u(ccv_dense_matrix_t* a, ccv_dense_matrix_t* b, ccv_dense_matrix_t* d, int padding_pattern)
{
	int i, j, y, x, k;
	int nz = b->rows * b->cols;
	int* coeff = (int*)ccmalloc(nz * sizeof(int));
	int* cx = (int*)ccmalloc(nz * sizeof(int));
	int* cy = (int*)ccmalloc(nz * sizeof(int));
	int scale = 1 << 14;
	nz = 0;
	for (i = 0; i < b->rows; i++)
		for (j = 0; j < b->cols; j++)
		{
			coeff[nz] = (int)(ccv_get_dense_matrix_cell_value(b, i, j, 0) * scale + 0.5);
			if (coeff[nz] == 0)
				continue;
			cy[nz] = i;
			cx[nz] = j;
			nz++;
		}
	ccv_dense_matrix_t* pa = ccv_dense_matrix_new(a->rows + b->rows / 2 * 2, a->cols + b->cols / 2 * 2, CCV_8U | CCV_C1, 0, 0);
	/* the padding pattern is different from FFT: |aa{BORDER}|abcd|{BORDER}dd| */
	for (i = 0; i < pa->rows; i++)
		for (j = 0; j < pa->cols; j++)
			pa->data.u8[i * pa->step + j] = a->data.u8[ccv_clamp(i - b->rows / 2, 0, a->rows - 1) * a->step + ccv_clamp(j - b->cols / 2, 0, a->cols - 1)];
	unsigned char* m_ptr = d->data.u8;
	unsigned char* a_ptr = pa->data.u8;
	/* 0.5 denote the overhead for indexing x and y */
	if (nz < b->rows * b->cols * 0.75)
	{
		for (i = 0; i < d->rows; i++)
		{
			for (j = 0; j < d->cols; j++)
			{
				int z = 0;
				for (k = 0; k < nz; k++)
					z += a_ptr[cy[k] * pa->step + j + cx[k]] * coeff[k];
				m_ptr[j] = ccv_clamp(z >> 14, 0, 255);
			}
			m_ptr += d->step;
			a_ptr += pa->step;
		}
	} else {
		k = 0;
		for (i = 0; i < b->rows; i++)
			for (j = 0; j < b->cols; j++)
			{
				coeff[k] = (int)(ccv_get_dense_matrix_cell_value(b, i, j, 0) * scale + 0.5);
				k++;
			}
		for (i = 0; i < d->rows; i++)
		{
			for (j = 0; j < d->cols; j++)
			{
				int* c_ptr = coeff;
				int z = 0;
				for (y = 0; y < b->rows; y++)
				{
					int iyx = y * pa->step;
					for (x = 0; x < b->cols; x++)
					{
						z += a_ptr[iyx + j + x] * c_ptr[0];
						c_ptr++;
					}
				}
				m_ptr[j] = ccv_clamp(z >> 14, 0, 255);
			}
			m_ptr += d->step;
			a_ptr += pa->step;
		}
	}
	ccv_matrix_free(pa);
	ccfree(coeff);
	ccfree(cx);
	ccfree(cy);
}