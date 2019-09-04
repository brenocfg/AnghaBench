#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int flags; int const tensor_symbol_info_size; int exec_idx; TYPE_3__* alloc_prep; TYPE_1__* p; TYPE_7__* tensor_blocks; } ;
typedef  TYPE_4__ ccv_nnc_symbolic_graph_prep_t ;
struct TYPE_13__ {int* p_refs; } ;
struct TYPE_12__ {int* p_refs; } ;
struct TYPE_10__ {int* vt_blocks; TYPE_6__* buffers; TYPE_2__* blocks; } ;
struct TYPE_9__ {int const block_ref; int buffer_ref; } ;
struct TYPE_8__ {int exec_symbol_info; } ;

/* Variables and functions */
 int CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 scalar_t__ READ_ONLY ; 
 scalar_t__ TENSOR_EXPECT_UNASSIGNED (TYPE_7__) ; 
 scalar_t__ TENSOR_READ_WRITE (TYPE_6__) ; 
 int _ccv_nnc_is_symbolic_graph_exec_input_or_output (int const,int) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int _ccv_nnc_tensor_block_check_preserve(const ccv_nnc_symbolic_graph_prep_t* const graph_prep, const int block_ref)
{
	// No need to check whether to preserve if this is not a while loop.
	if (!(graph_prep->flags & CCV_NNC_GRAPH_EXEC_P_WHILE))
		return 0;
	assert(block_ref >= 0 && block_ref < graph_prep->tensor_symbol_info_size);
	// If it is unassigned, no need to preserve.
	if (TENSOR_EXPECT_UNASSIGNED(graph_prep->tensor_blocks[block_ref]))
		return 0;
	const int p_ref = graph_prep->tensor_blocks[block_ref].p_refs[0] - 1;
	// If p is not input, no need to preserve at all.
	if (-1 != _ccv_nnc_is_symbolic_graph_exec_input_or_output(p_ref, graph_prep->p->exec_symbol_info + (graph_prep->exec_idx - 1)))
		return 0;
	const int vt_ref = graph_prep->alloc_prep->vt_blocks[block_ref];
	assert(vt_ref >= 0);
	assert(block_ref == graph_prep->alloc_prep->blocks[vt_ref].block_ref);
	const int buffer_ref = graph_prep->alloc_prep->blocks[vt_ref].buffer_ref;
	// If the buffer is a truly read-only one, no need to preserve.
	if (TENSOR_READ_WRITE(graph_prep->alloc_prep->buffers[buffer_ref]) == READ_ONLY)
		return 0;
	/* This needs detailed explanation, what does preserve mean?
	 * For a parameterized loop, such as while { y = x + 1 } (y => x), if tensor x is
	 * also used outside of the while loop, we cannot reuse the memory region of x for
	 * the for loop, otherwise we will destroy x when doing y = x + 1 computation (assuming
	 * y uses the same memory region as x). The way to workaround this is by using a different
	 * memory region for y = x + 1, but for the first iteration, having x pointing to the
	 * original. During the allocation process, the way to identify whether x should preserve
	 * its value or not by looking up its parent tensor. If the symbol (tensor_block)'s input
	 * parent tensor is the same as the memory region it plans to use in the buffer, then we are
	 * good (buffer.p_refs[0] == p_refs[0]). A buffer can only point to one parent tensor, and
	 * it is the input tensor whenever that is possible. A tensor block can point to two parent
	 * tensors, one is input tensor, one is the output tensor. p_refs[0] should be the input
	 * tensor whenever that is possible. */
	if (graph_prep->alloc_prep->buffers[buffer_ref].p_refs[0] - 1 == p_ref)
		return 0;
	// Otherwise, return 1 because we now need to preserve.
	return 1;
}