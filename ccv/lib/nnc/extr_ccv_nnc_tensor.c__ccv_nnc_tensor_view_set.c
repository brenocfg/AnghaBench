#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int off_t ;
struct TYPE_9__ {int /*<<< orphan*/ * u8; } ;
struct TYPE_10__ {int /*<<< orphan*/  datatype; int /*<<< orphan*/  dim; } ;
struct TYPE_11__ {int off; TYPE_2__ data; int /*<<< orphan*/  inc; TYPE_3__ info; } ;
typedef  TYPE_4__ ccv_nnc_tensor_view_t ;
struct TYPE_8__ {int /*<<< orphan*/ * u8; } ;
struct TYPE_12__ {TYPE_1__ data; } ;
typedef  TYPE_5__ ccv_nnc_tensor_t ;

/* Variables and functions */
 int CCV_NNC_MAX_DIM_ALLOC ; 
 int ccv_nnc_tensor_view_offset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int const*,int) ; 

__attribute__((used)) static inline void _ccv_nnc_tensor_view_set(ccv_nnc_tensor_view_t* const tv, const ccv_nnc_tensor_t* const tensor, const int dim[CCV_NNC_MAX_DIM_ALLOC], const int ofs[CCV_NNC_MAX_DIM_ALLOC], const int inc[CCV_NNC_MAX_DIM_ALLOC])
{
	memcpy(tv->inc, inc, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC);
	memcpy(tv->info.dim, dim, sizeof(int) * CCV_NNC_MAX_DIM_ALLOC);
	uint8_t* const p = tensor->data.u8;
	const off_t off = tv->off = ccv_nnc_tensor_view_offset(tv->info.datatype, tv->inc, ofs);
	tv->data.u8 = p + off;
}