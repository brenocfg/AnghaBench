#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  ccv_point_t ;
struct TYPE_7__ {int structs; int features; int /*<<< orphan*/ * fern; } ;
typedef  TYPE_2__ ccv_ferns_t ;
struct TYPE_6__ {unsigned char* u8; } ;
struct TYPE_8__ {int /*<<< orphan*/  type; TYPE_1__ data; } ;
typedef  TYPE_3__ ccv_dense_matrix_t ;

/* Variables and functions */
 scalar_t__ CCV_C1 ; 
 scalar_t__ CCV_GET_CHANNEL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_matrix_getter (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  for_block ; 

void ccv_ferns_feature(ccv_ferns_t* ferns, ccv_dense_matrix_t* a, int scale, uint32_t* fern)
{
	ccv_point_t* fern_feature = ferns->fern + scale * ferns->structs * ferns->features * 2;
	int i, j;
	unsigned char* a_ptr = a->data.u8;
	assert(CCV_GET_CHANNEL(a->type) == CCV_C1);
#define for_block(_, _for_get) \
	for (i = 0; i < ferns->structs; i++) \
	{ \
		uint32_t leaf = 0; \
		for (j = 0; j < ferns->features; j++) \
		{ \
			if (_for_get(a_ptr + fern_feature[0].y * a->step, fern_feature[0].x, 0) > _for_get(a_ptr + fern_feature[1].y * a->step, fern_feature[1].x, 0)) \
				leaf = (leaf << 1) | 1; \
			else \
				leaf = leaf << 1; \
			fern_feature += 2; \
		} \
		fern[i] = leaf; \
	}
	ccv_matrix_getter(a->type, for_block);
#undef for_block
}