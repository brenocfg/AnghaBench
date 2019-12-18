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
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_4__ {unsigned char* u8; } ;
struct TYPE_5__ {int type; int refcount; int datatype; int channels; int rows; int cols; int /*<<< orphan*/  step; scalar_t__ reserved1; int /*<<< orphan*/  format; int /*<<< orphan*/  resides; scalar_t__ reserved0; scalar_t__ sig; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_dense_matrix_t ;

/* Variables and functions */
 int CCV_GARBAGE ; 
 int CCV_GET_CHANNEL (int) ; 
 int CCV_GET_DATA_TYPE (int) ; 
 int /*<<< orphan*/  CCV_GET_STEP (int,int) ; 
 int CCV_MATRIX_DENSE ; 
 int CCV_NO_DATA_ALLOC ; 
 int CCV_REUSABLE ; 
 int /*<<< orphan*/  CCV_TENSOR_CPU_MEMORY ; 
 int /*<<< orphan*/  CCV_TENSOR_FORMAT_NHWC ; 
 int CCV_UNMANAGED ; 
 int /*<<< orphan*/  assert (int) ; 
 void* ccmalloc (int) ; 
 int /*<<< orphan*/  ccv_cache ; 
 scalar_t__ ccv_cache_opt ; 
 scalar_t__ ccv_cache_out (int /*<<< orphan*/ *,scalar_t__,scalar_t__*) ; 
 int ccv_compute_dense_matrix_size (int,int,int) ; 

ccv_dense_matrix_t* ccv_dense_matrix_new(int rows, int cols, int type, void* data, uint64_t sig)
{
	ccv_dense_matrix_t* mat;
	if (ccv_cache_opt && sig != 0 && !data && !(type & CCV_NO_DATA_ALLOC))
	{
		uint8_t type;
		mat = (ccv_dense_matrix_t*)ccv_cache_out(&ccv_cache, sig, &type);
		if (mat)
		{
			assert(type == 0);
			mat->type |= CCV_GARBAGE; // set the flag so the upper level function knows this is from recycle-bin
			mat->refcount = 1;
			return mat;
		}
	}
	if (type & CCV_NO_DATA_ALLOC)
	{
		mat = (ccv_dense_matrix_t*)ccmalloc(sizeof(ccv_dense_matrix_t));
		mat->type = (CCV_GET_CHANNEL(type) | CCV_GET_DATA_TYPE(type) | CCV_MATRIX_DENSE | CCV_NO_DATA_ALLOC) & ~CCV_GARBAGE;
		mat->data.u8 = data;
	} else {
		const size_t hdr_size = (sizeof(ccv_dense_matrix_t) + 15) & -16;
		mat = (ccv_dense_matrix_t*)(data ? data : ccmalloc(ccv_compute_dense_matrix_size(rows, cols, type)));
		mat->type = (CCV_GET_CHANNEL(type) | CCV_GET_DATA_TYPE(type) | CCV_MATRIX_DENSE) & ~CCV_GARBAGE;
		mat->type |= data ? CCV_UNMANAGED : CCV_REUSABLE; // it still could be reusable because the signature could be derived one.
		mat->data.u8 = (unsigned char*)mat + hdr_size;
	}
	mat->sig = sig;
#if CCV_NNC_TENSOR_TFB
	mat->reserved0 = 0;
	mat->resides = CCV_TENSOR_CPU_MEMORY;
	mat->format = CCV_TENSOR_FORMAT_NHWC;
	mat->datatype = CCV_GET_DATA_TYPE(type);
	mat->channels = CCV_GET_CHANNEL(type);
	mat->reserved1 = 0;
#endif
	mat->rows = rows;
	mat->cols = cols;
	mat->step = CCV_GET_STEP(cols, type);
	mat->refcount = 1;
	return mat;
}