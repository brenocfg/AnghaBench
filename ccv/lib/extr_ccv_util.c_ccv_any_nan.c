#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_matrix_t ;
struct TYPE_4__ {int /*<<< orphan*/ * f64; int /*<<< orphan*/ * f32; } ;
struct TYPE_5__ {int type; int rows; int cols; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_32F ; 
 int CCV_64F ; 
 int CCV_GET_CHANNEL (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* ccv_get_dense_matrix (int /*<<< orphan*/ *) ; 
 scalar_t__ isnan (int /*<<< orphan*/ ) ; 
 scalar_t__ isnanf (int /*<<< orphan*/ ) ; 

int ccv_any_nan(ccv_matrix_t *a)
{
	ccv_dense_matrix_t* da = ccv_get_dense_matrix(a);
	assert((da->type & CCV_32F) || (da->type & CCV_64F));
	int ch = CCV_GET_CHANNEL(da->type);
	int i;
	if (da->type & CCV_32F)
	{
		for (i = 0; i < da->rows * da->cols * ch; i++)
#ifdef isnanf
			if (isnanf(da->data.f32[i]))
#else
			if (isnan(da->data.f32[i]))
#endif
				return i + 1;
	} else {
		for (i = 0; i < da->rows * da->cols * ch; i++)
			if (isnan(da->data.f64[i]))
				return i + 1;
	}
	return 0;
}