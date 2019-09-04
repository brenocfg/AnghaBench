#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_sparse_matrix_t ;
struct TYPE_4__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ ccv_nnc_tensor_block_t ;

/* Variables and functions */
 int _ccv_nnc_tensor_block_a_after_b_exclusively (int /*<<< orphan*/  const* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int _ccv_nnc_tensor_block_head_after_tail(const ccv_sparse_matrix_t* const exec_dep, const ccv_nnc_tensor_block_t a, const ccv_nnc_tensor_block_t b)
{
	return _ccv_nnc_tensor_block_a_after_b_exclusively(exec_dep, a.head, b.tail);
}