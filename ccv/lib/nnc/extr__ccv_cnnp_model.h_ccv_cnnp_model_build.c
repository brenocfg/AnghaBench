#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
struct TYPE_7__ {int const output_size; int /*<<< orphan*/ * const outputs; TYPE_1__* isa; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
struct TYPE_6__ {int /*<<< orphan*/  (* build ) (TYPE_2__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ * const,int const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ * const,int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ * const,int const) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const* const,int const,int /*<<< orphan*/ * const,int const) ; 

__attribute__((used)) static inline void ccv_cnnp_model_build(ccv_cnnp_model_t* const self, ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_symbol_t* const inputs, const int input_size, ccv_nnc_tensor_symbol_t* const outputs, const int output_size)
{
	if (outputs && output_size)
	{
		assert(output_size == self->output_size);
		self->isa->build(self, graph, inputs, input_size, outputs, output_size);
		memcpy(self->outputs, outputs, sizeof(ccv_nnc_tensor_symbol_t) * output_size);
	} else
		self->isa->build(self, graph, inputs, input_size, self->outputs, self->output_size);
}