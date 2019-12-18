#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ccv_nnc_symbolic_graph_t ;
typedef  int /*<<< orphan*/  ccv_cnnp_state_initializer_f ;
struct TYPE_6__ {TYPE_1__* isa; } ;
typedef  TYPE_2__ ccv_cnnp_model_t ;
struct TYPE_5__ {int /*<<< orphan*/  (* init_states ) (TYPE_2__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const,void* const) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_2__* const,int /*<<< orphan*/ * const,int /*<<< orphan*/  const,void* const) ; 

__attribute__((used)) static inline void ccv_cnnp_model_init_states(ccv_cnnp_model_t* const self, ccv_nnc_symbolic_graph_t* const graph, const ccv_cnnp_state_initializer_f initializer, void* const context)
{
	if (self->isa->init_states)
		self->isa->init_states(self, graph, initializer, context);
}