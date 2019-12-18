#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_7__ {int ifbit; int i; } ;
typedef  TYPE_1__ ccv_sparse_matrix_vector_t ;
struct TYPE_8__ {int prime_index; int size; TYPE_1__* vector; TYPE_1__* index; } ;
typedef  TYPE_2__ ccv_sparse_matrix_t ;
typedef  TYPE_1__ ccv_sparse_matrix_index_t ;
typedef  int /*<<< orphan*/  _ccv_sparse_prime ;

/* Variables and functions */
 int _ccv_sparse_matrix_index_for_hash (int,int const) ; 
 int _ccv_sparse_matrix_index_next_size_over (int const) ; 
 int _ccv_sparse_matrix_size_for_index (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ ccrealloc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__* const,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void _ccv_sparse_matrix_inc_size(ccv_sparse_matrix_t* mat)
{
	assert(mat->prime_index >= 0 && mat->prime_index < sizeof(_ccv_sparse_prime) / sizeof(int));
	const uint32_t size = mat->size;
	const int prime_index = mat->prime_index = _ccv_sparse_matrix_index_next_size_over(size * 2);
	const uint32_t new_size = mat->size = _ccv_sparse_matrix_size_for_index(mat->prime_index);
	assert(mat->prime_index >= 0 && mat->prime_index < sizeof(_ccv_sparse_prime) / sizeof(int));
	ccv_sparse_matrix_index_t* const index = mat->index = (ccv_sparse_matrix_index_t*)ccrealloc(mat->index, sizeof(ccv_sparse_matrix_index_t) * new_size);
	memset(index + size, 0, sizeof(ccv_sparse_matrix_index_t) * (new_size - size));
	ccv_sparse_matrix_vector_t* const vector = mat->vector = (ccv_sparse_matrix_vector_t*)ccrealloc(mat->vector, sizeof(ccv_sparse_matrix_vector_t) * new_size);
	uint32_t i;
	for (i = 0; i < size; i++)
		index[i].ifbit = !!index[i].ifbit; // Mark this as need to be moved around.
	for (i = 0; i < size; i++)
		if (index[i].ifbit == 1) // Encountered one need to be moved.
		{
			index[i].ifbit = 0;
			// This item is from old hash table, need to find a new location for it.
			uint32_t key = index[i].i;
			ccv_sparse_matrix_vector_t val = vector[i];
			uint32_t k = 2;
			uint32_t idx = _ccv_sparse_matrix_index_for_hash(key, prime_index);
			for (; k < 255; ++idx, ++k)
			{
				if (idx >= new_size)
					idx = 0;
				uint32_t j = index[idx].ifbit;
				if (!j)
				{
					index[idx].ifbit = k;
					index[idx].i = key;
					vector[idx] = val;
					break;
				}
				if (k <= j) // j could be either a valid one or 1, in any case, this will pass.
					continue;
				index[idx].ifbit = k;
				uint32_t old_key = index[idx].i;
				index[idx].i = key;
				key = old_key;
				ccv_sparse_matrix_vector_t old_val = vector[idx];
				vector[idx] = val;
				val = old_val;
				if (j != 1)
					k = j;
				else { // In this case, I cannot keep going with the idx, need to recompute idx as well restart k.
					idx = _ccv_sparse_matrix_index_for_hash(key, prime_index) - 1;
					k = 1; // Restart.
				}
			}
			if (k < 255)
				continue;
			for (;; ++idx, ++k)
			{
				if (idx >= new_size)
					idx = 0;
				uint32_t j = index[idx].ifbit;
				if (!j)
				{
					index[idx].ifbit = k > 0xff ? 0xff : k;
					index[idx].i = key;
					vector[idx] = val;
					break;
				}
				if (j == 0xff)
					j = _ccv_sparse_matrix_index_for_hash((index[idx].i + new_size - idx), prime_index) + 2; // This is valid because on overflow, unsigned is well defined.
				if (k <= j) // j could be either a valid one or 1, in any case, this will pass.
					continue;
				index[idx].ifbit = k > 0xff ? 0xff : k;
				uint32_t old_key = index[idx].i;
				index[idx].i = key;
				key = old_key;
				ccv_sparse_matrix_vector_t old_val = vector[idx];
				vector[idx] = val;
				val = old_val;
				if (j != 1)
					k = j;
				else { // In this case, I cannot keep going with the idx, need to recompute idx as well restart k.
					idx = _ccv_sparse_matrix_index_for_hash(key, prime_index) - 1;
					k = 1; // Restart.
				}
			}
		}
}