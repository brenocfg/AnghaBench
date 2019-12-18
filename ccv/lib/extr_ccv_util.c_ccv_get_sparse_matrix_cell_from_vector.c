#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct TYPE_9__ {int /*<<< orphan*/ * u8; } ;
struct TYPE_10__ {int size; int prime_index; scalar_t__ index; TYPE_1__ data; } ;
typedef  TYPE_2__ ccv_sparse_matrix_vector_t ;
struct TYPE_11__ {int type; } ;
typedef  TYPE_3__ ccv_sparse_matrix_t ;
struct TYPE_12__ {int ifbit; int i; } ;
typedef  TYPE_4__ ccv_sparse_matrix_index_t ;
struct TYPE_13__ {int /*<<< orphan*/ * u8; } ;
typedef  TYPE_5__ ccv_numeric_data_t ;

/* Variables and functions */
 int CCV_DENSE_VECTOR ; 
 int CCV_GET_CHANNEL (int) ; 
 int CCV_GET_DATA_TYPE_SIZE (int) ; 
 int _ccv_sparse_matrix_index_for_hash (int const,int const) ; 

ccv_numeric_data_t ccv_get_sparse_matrix_cell_from_vector(const ccv_sparse_matrix_t* mat, ccv_sparse_matrix_vector_t* vector, int vidx)
{
	ccv_numeric_data_t cell = {}; // zero-init.
	const size_t cell_size = CCV_GET_DATA_TYPE_SIZE(mat->type) * CCV_GET_CHANNEL(mat->type);
	if (mat->type & CCV_DENSE_VECTOR)
	{
		cell.u8 = vector->data.u8 + cell_size * vidx;
		return cell;
	}
	const size_t cell_size_aligned = (CCV_GET_DATA_TYPE_SIZE(mat->type) * CCV_GET_CHANNEL(mat->type) + 3) & -4;
	const size_t index_size = sizeof(ccv_sparse_matrix_index_t) + cell_size_aligned;
	const uint32_t size = vector->size;
	uint8_t* const index = (uint8_t*)vector->index;
	const int prime_index = vector->prime_index;
	uint32_t idx = _ccv_sparse_matrix_index_for_hash(vidx, prime_index);
	uint32_t k = 2;
	for (; k < 255; ++idx, ++k)
	{
		if (idx >= size)
			idx = 0;
		ccv_sparse_matrix_index_t* const index_idx = (ccv_sparse_matrix_index_t*)(index + index_size * idx);
		if (k > index_idx->ifbit)
			return cell;
		if (index_idx->i == vidx)
		{
			cell.u8 = (uint8_t*)(index_idx + 1);
			return cell;
		}
	}
	// Above or equal to 255, we need to fetch the key to recompute the distance every time now.
	for (;; ++idx, ++k)
	{
		if (idx >= size)
			idx = 0;
		ccv_sparse_matrix_index_t* const index_idx = (ccv_sparse_matrix_index_t*)(index + index_size * idx);
		uint32_t j = index_idx->ifbit;
		if (j == 0xff)
			j = _ccv_sparse_matrix_index_for_hash(index_idx->i + size - idx, prime_index) + 2;
		if (k > j)
			return cell;
		if (index_idx->i == vidx)
		{
			cell.u8 = (uint8_t*)(index_idx + 1);
			return cell;
		}
	}
}