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
struct TYPE_4__ {unsigned char* u8; } ;
struct TYPE_5__ {int rows; int cols; int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 TYPE_2__* ccv_get_dense_matrix (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ccv_matrix_getter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_block ; 

double ccv_variance(ccv_matrix_t* mat)
{
	ccv_dense_matrix_t* dmt = ccv_get_dense_matrix(mat);
	double mean = 0, variance = 0;
	unsigned char* m_ptr = dmt->data.u8;
	int i, j, ch = CCV_GET_CHANNEL(dmt->type);
#define for_block(_, _for_get) \
	for (i = 0; i < dmt->rows; i++) \
	{ \
		for (j = 0; j < dmt->cols * ch; j++) \
		{ \
			mean += _for_get(m_ptr, j, 0); \
			variance += _for_get(m_ptr, j, 0) * _for_get(m_ptr, j, 0); \
		} \
		m_ptr += dmt->step; \
	}
	ccv_matrix_getter(dmt->type, for_block);
#undef for_block
	mean = mean / (dmt->rows * dmt->cols * ch);
	variance = variance / (dmt->rows * dmt->cols * ch);
	return variance - mean * mean;
}