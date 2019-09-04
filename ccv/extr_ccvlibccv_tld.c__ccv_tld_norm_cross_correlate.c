#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned char* u8; } ;
struct TYPE_6__ {int rows; int cols; int /*<<< orphan*/  step; TYPE_1__ data; int /*<<< orphan*/  type; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 scalar_t__ CCV_8U ; 
 scalar_t__ CCV_C1 ; 
 scalar_t__ CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 scalar_t__ CCV_GET_DATA_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 float sqrtf (float) ; 

__attribute__((used)) static float _ccv_tld_norm_cross_correlate(ccv_dense_matrix_t* r0, ccv_dense_matrix_t* r1)
{
	assert(CCV_GET_CHANNEL(r0->type) == CCV_C1 && CCV_GET_DATA_TYPE(r0->type) == CCV_8U);
	assert(CCV_GET_CHANNEL(r1->type) == CCV_C1 && CCV_GET_DATA_TYPE(r1->type) == CCV_8U);
	assert(r0->rows == r1->rows && r0->cols == r1->cols);
	int x, y;
	int sum0 = 0, sum1 = 0;
	unsigned char* r0_ptr = r0->data.u8;
	unsigned char* r1_ptr = r1->data.u8;
	for (y = 0; y < r0->rows; y++)
	{
		for (x = 0; x < r0->cols; x++)
		{
			sum0 += r0_ptr[x];
			sum1 += r1_ptr[x];
		}
		r0_ptr += r0->step;
		r1_ptr += r1->step;
	}
	r0_ptr = r0->data.u8;
	r1_ptr = r1->data.u8;
	float mr0 = (float)sum0 / (r0->rows * r0->cols);
	float mr1 = (float)sum1 / (r1->rows * r1->cols);
	float r0r1 = 0, r0r0 = 0, r1r1 = 0;
	for (y = 0; y < r0->rows; y++)
	{
		for (x = 0; x < r0->cols; x++)
		{
			float r0f = r0_ptr[x] - mr0;
			float r1f = r1_ptr[x] - mr1;
			r0r1 += r0f * r1f;
			r0r0 += r0f * r0f;
			r1r1 += r1f * r1f;
		}
		r0_ptr += r0->step;
		r1_ptr += r1->step;
	}
	if (r0r0 * r1r1 < 1e-6)
		return 0;
	return r0r1 / sqrtf(r0r0 * r1r1);
}