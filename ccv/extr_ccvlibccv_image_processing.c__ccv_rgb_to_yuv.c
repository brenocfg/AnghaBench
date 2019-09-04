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
struct TYPE_6__ {int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccv_matrix_getter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_matrix_setter_getter ; 
 int /*<<< orphan*/  for_block ; 

__attribute__((used)) static void _ccv_rgb_to_yuv(ccv_dense_matrix_t* a, ccv_dense_matrix_t* b)
{
	unsigned char* a_ptr = a->data.u8;
	unsigned char* b_ptr = b->data.u8;
	int i, j;
#define for_block(_for_get, _for_set_b, _for_get_b) \
	for (i = 0; i < a->rows; i++) \
	{ \
		for (j = 0; j < a->cols; j++) \
		{ \
			_for_set_b(b_ptr, j * 3, (_for_get(a_ptr, j * 3, 0) * 1225 + _for_get(a_ptr, j * 3 + 1, 0) * 2404 + _for_get(a_ptr, j * 3 + 2, 0) * 467) / 4096, 0); \
			_for_set_b(b_ptr, j * 3 + 1, (_for_get(a_ptr, j * 3 + 2, 0) - _for_get_b(b_ptr, j * 3, 0)) * 2015 / 4096 + 128, 0); \
			_for_set_b(b_ptr, j * 3 + 2, (_for_get(a_ptr, j * 3, 0) - _for_get_b(b_ptr, j * 3, 0)) * 3592 / 4096 + 128, 0); \
		} \
		a_ptr += a->step; \
		b_ptr += b->step; \
	}
	ccv_matrix_getter(a->type, ccv_matrix_setter_getter, b->type, for_block);
#undef for_block
}