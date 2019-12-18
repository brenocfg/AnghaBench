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
struct TYPE_8__ {int /*<<< orphan*/  u8; } ;
struct TYPE_7__ {int /*<<< orphan*/  u8; } ;
struct TYPE_9__ {int rows; int cols; int type; TYPE_2__ data; TYPE_1__ tb; int /*<<< orphan*/  sig; int /*<<< orphan*/  refcount; int /*<<< orphan*/  step; } ;
typedef  TYPE_3__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GARBAGE ; 
 int CCV_GET_CHANNEL (int) ; 
 int CCV_GET_DATA_TYPE (int) ; 
 int CCV_MATRIX_DENSE ; 
 int CCV_NO_DATA_ALLOC ; 
 int CCV_UNMANAGED ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccv_get_dense_matrix_cell (TYPE_3__*,int,int,int /*<<< orphan*/ ) ; 

ccv_dense_matrix_t ccv_reshape(ccv_dense_matrix_t* a, int y, int x, int rows, int cols)
{
	assert(y + rows <= a->rows);
	assert(x + cols <= a->cols);
	assert(x >= 0 && y >= 0);
	ccv_dense_matrix_t b = {
		.type = (CCV_UNMANAGED | CCV_GET_DATA_TYPE(a->type) | CCV_GET_CHANNEL(a->type) | CCV_NO_DATA_ALLOC | CCV_MATRIX_DENSE) & ~CCV_GARBAGE,
		.rows = rows,
		.cols = cols,
		.step = a->step,
		.refcount = 0,
		.sig = 0,
		.tb.u8 = 0,
		.data.u8 = ccv_get_dense_matrix_cell(a, y, x, 0),
	};
	return b;
}