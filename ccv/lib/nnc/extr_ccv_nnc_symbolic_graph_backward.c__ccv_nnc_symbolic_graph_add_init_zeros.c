#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_8__ ;
typedef  struct TYPE_30__   TYPE_7__ ;
typedef  struct TYPE_29__   TYPE_6__ ;
typedef  struct TYPE_28__   TYPE_5__ ;
typedef  struct TYPE_27__   TYPE_4__ ;
typedef  struct TYPE_26__   TYPE_3__ ;
typedef  struct TYPE_25__   TYPE_2__ ;
typedef  struct TYPE_24__   TYPE_1__ ;
typedef  struct TYPE_23__   TYPE_16__ ;

/* Type definitions */
struct TYPE_25__ {int d; } ;
typedef  TYPE_2__ ccv_nnc_tensor_symbol_t ;
struct TYPE_26__ {int /*<<< orphan*/  p_ref; } ;
typedef  TYPE_3__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_27__ {int d; } ;
typedef  TYPE_4__ ccv_nnc_tensor_ref_t ;
struct TYPE_28__ {int /*<<< orphan*/  tensor_symbol_info; } ;
typedef  TYPE_5__ ccv_nnc_symbolic_graph_t ;
struct TYPE_29__ {TYPE_1__* tensor_symbol_info; int /*<<< orphan*/  autograd_tensor_symbols; TYPE_7__* autograd_tensor_versions; } ;
typedef  TYPE_6__ ccv_nnc_symbolic_graph_backward_prep_t ;
struct TYPE_30__ {int /*<<< orphan*/  ref_version; } ;
typedef  TYPE_7__ ccv_nnc_autograd_tensor_version_t ;
struct TYPE_23__ {int const d; } ;
struct TYPE_31__ {TYPE_16__ symbol; } ;
typedef  TYPE_8__ ccv_nnc_autograd_tensor_symbol_t ;
typedef  int /*<<< orphan*/  ccv_array_t ;
struct TYPE_24__ {int alias_ref; int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_NNC_TENSOR_SYMBOL_INIT_ZEROS ; 
 int _ccv_nnc_tensor_ref_version_find_init (TYPE_7__ const* const) ; 
 scalar_t__ ccv_array_get (int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  ccv_array_push (int /*<<< orphan*/ * const,TYPE_2__*) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_hookup (TYPE_5__* const,TYPE_5__* const,TYPE_2__,TYPE_16__) ; 
 TYPE_2__ ccv_nnc_tensor_symbol_new (TYPE_5__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ccv_nnc_tensor_symbol_set_flags (TYPE_5__* const,TYPE_2__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_add_init_zeros(const ccv_nnc_symbolic_graph_backward_prep_t* const sub_prep, const ccv_nnc_tensor_symbol_t* const wrt_symbols, const int wrt_symbol_size, ccv_nnc_symbolic_graph_t* const graph, ccv_nnc_symbolic_graph_t* const sub_graph, ccv_array_t* const symbols)
{
	int i;
	for (i = 0; i < wrt_symbol_size; i++)
	{
		const int d = wrt_symbols[i].d;
		if (d < 0)
			continue;
		const int ref_d = (!sub_prep->tensor_symbol_info[d].alias_ref) ? d : sub_prep->tensor_symbol_info[d].alias_ref - 1;
		const ccv_nnc_autograd_tensor_version_t* const tensor_ver = sub_prep->autograd_tensor_versions + ref_d;
		const int init_ref_ver = _ccv_nnc_tensor_ref_version_find_init(tensor_ver);
		if (init_ref_ver >= 0)
		{
			// Need de-dup logic.
			const int init_d = ((ccv_nnc_tensor_ref_t*)ccv_array_get(tensor_ver->ref_version, init_ref_ver))->d;
			ccv_nnc_autograd_tensor_symbol_t* const init_autograd_symbol = (ccv_nnc_autograd_tensor_symbol_t*)ccv_array_get(sub_prep->autograd_tensor_symbols, init_d);
			const ccv_nnc_tensor_symbol_info_t* const sub_init_symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(sub_graph->tensor_symbol_info, init_autograd_symbol->symbol.d);
			// If it doesn't have a parent ref yet, create one.
			if (!sub_init_symbol_info->p_ref)
			{
				ccv_nnc_tensor_symbol_t new_symbol = ccv_nnc_tensor_symbol_new(graph, sub_prep->tensor_symbol_info[ref_d].info, 0);
				ccv_nnc_tensor_symbol_set_flags(graph, new_symbol, CCV_NNC_TENSOR_SYMBOL_INIT_ZEROS);
				ccv_array_push(symbols, &new_symbol);
				ccv_nnc_tensor_symbol_hookup(graph, sub_graph, new_symbol, init_autograd_symbol->symbol);
			}
		}
	}
}