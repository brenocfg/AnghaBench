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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {unsigned char* u8; } ;
struct TYPE_5__ {int type; int rows; int cols; int refcount; TYPE_1__ data; int /*<<< orphan*/  step; int /*<<< orphan*/  sig; scalar_t__ reserved0; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GARBAGE ; 
 int CCV_GET_CHANNEL (int) ; 
 int CCV_GET_DATA_TYPE (int) ; 
 int /*<<< orphan*/  CCV_GET_STEP (int,int) ; 
 int CCV_MATRIX_DENSE ; 
 int CCV_NO_DATA_ALLOC ; 
 int CCV_UNMANAGED ; 

ccv_dense_matrix_t ccv_dense_matrix(int rows, int cols, int type, void* data, uint64_t sig)
{
	ccv_dense_matrix_t mat;
	mat.reserved0 = 0;
	mat.sig = sig;
	mat.type = (CCV_GET_CHANNEL(type) | CCV_GET_DATA_TYPE(type) | CCV_MATRIX_DENSE | CCV_NO_DATA_ALLOC | CCV_UNMANAGED) & ~CCV_GARBAGE;
	mat.rows = rows;
	mat.cols = cols;
	mat.step = CCV_GET_STEP(cols, type);
	mat.refcount = 1;
#if CCV_NNC_TENSOR_TFB
	mat.reserved0 = 0;
	mat.resides = CCV_TENSOR_CPU_MEMORY;
	mat.format = CCV_TENSOR_FORMAT_NHWC | CCV_GET_DATA_TYPE(type);
	mat.channels = CCV_GET_CHANNEL(type);
	mat.reserved1 = 0;
#endif
	mat.data.u8 = (unsigned char*)data;
	return mat;
}