#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_7__* const alias_registry; TYPE_7__* const exec_registry; } ;
typedef  TYPE_1__ ccv_nnc_tensor_ref_t ;
struct TYPE_13__ {int exec_symbol_info_size; int tensor_symbol_info_size; int sub_prep_size; struct TYPE_13__* const sub_preps; struct TYPE_13__* const tensor_symbol_info; struct TYPE_13__* const exec_symbol_info; int /*<<< orphan*/  forward_visit; int /*<<< orphan*/  backward_visit; struct TYPE_13__* const input_bitmasks; TYPE_7__* const outgoings; struct TYPE_13__* backward_info; TYPE_7__* sum_or_set_execs; TYPE_7__* const autograd_tensor_symbols; TYPE_7__* const ref_version; struct TYPE_13__* autograd_tensor_versions; struct TYPE_13__* const inputs; struct TYPE_13__* autograd_execs; } ;
typedef  TYPE_2__ ccv_nnc_symbolic_graph_backward_prep_t ;
struct TYPE_14__ {TYPE_7__* const outgoings; TYPE_2__* const inputs; } ;
typedef  TYPE_3__ ccv_nnc_sum_or_set_graph_exec_symbol_t ;
typedef  TYPE_2__ ccv_nnc_graph_backward_info_t ;
typedef  TYPE_2__ ccv_nnc_autograd_tensor_version_t ;
typedef  TYPE_2__ ccv_nnc_autograd_graph_exec_symbol_t ;
struct TYPE_15__ {int rnum; } ;
typedef  TYPE_7__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  ccfree (TYPE_2__* const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_7__* const) ; 
 scalar_t__ ccv_array_get (TYPE_7__* const,int) ; 
 int /*<<< orphan*/  ccv_nnc_graph_visit_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_backward_prep_free(const ccv_nnc_symbolic_graph_backward_prep_t backward_prep)
{
	int i, j;
	const int exec_symbol_info_size = backward_prep.exec_symbol_info_size;
	const int tensor_symbol_info_size = backward_prep.tensor_symbol_info_size;
	ccv_nnc_autograd_graph_exec_symbol_t* const autograd_execs = backward_prep.autograd_execs;
	if (autograd_execs)
	{
		for (i = 0; i < exec_symbol_info_size; i++)
		{
			if (autograd_execs[i].inputs)
				ccfree(autograd_execs[i].inputs);
			if (autograd_execs[i].outgoings)
				ccv_array_free(autograd_execs[i].outgoings);
		}
		ccfree(autograd_execs);
	}
	ccv_nnc_autograd_tensor_version_t* const autograd_tensor_versions = backward_prep.autograd_tensor_versions;
	if (autograd_tensor_versions)
	{
		for (i = 0; i < tensor_symbol_info_size; i++)
		{
			if (autograd_tensor_versions[i].ref_version)
			{
				for (j = 0; j < autograd_tensor_versions[i].ref_version->rnum; j++)
				{
					ccv_nnc_tensor_ref_t* ref_version = (ccv_nnc_tensor_ref_t*)ccv_array_get(autograd_tensor_versions[i].ref_version, j);
					if (ref_version->exec_registry)
						ccv_array_free(ref_version->exec_registry);
					if (ref_version->alias_registry)
						ccv_array_free(ref_version->alias_registry);
				}
				ccv_array_free(autograd_tensor_versions[i].ref_version);
			}
		}
		ccfree(autograd_tensor_versions);
	}
	if (backward_prep.autograd_tensor_symbols)
		ccv_array_free(backward_prep.autograd_tensor_symbols);
	ccv_array_t* const sum_or_set_execs = backward_prep.sum_or_set_execs;
	if (sum_or_set_execs)
	{
		for (i = 0; i < sum_or_set_execs->rnum; i++)
		{
			ccv_nnc_sum_or_set_graph_exec_symbol_t* sum_or_set = (ccv_nnc_sum_or_set_graph_exec_symbol_t*)ccv_array_get(sum_or_set_execs, i);
			if (sum_or_set->inputs)
				ccfree(sum_or_set->inputs);
			if (sum_or_set->outgoings)
				ccv_array_free(sum_or_set->outgoings);
		}
		ccv_array_free(sum_or_set_execs);
	}
	// Now afterwards, these are mandatory.
	ccv_nnc_graph_backward_info_t* const backward_info = backward_prep.backward_info;
	for (i = 0; i < exec_symbol_info_size; i++)
	{
		if (backward_info[i].outgoings)
			ccv_array_free(backward_info[i].outgoings);
		if (backward_info[i].input_bitmasks)
			ccfree(backward_info[i].input_bitmasks);
	}
	ccfree(backward_info);
	ccv_nnc_graph_visit_free(backward_prep.backward_visit);
	ccv_nnc_graph_visit_free(backward_prep.forward_visit);
	ccfree(backward_prep.exec_symbol_info);
	ccfree(backward_prep.tensor_symbol_info);
	for (i = 0; i < backward_prep.sub_prep_size; i++)
		_ccv_nnc_symbolic_graph_backward_prep_free(backward_prep.sub_preps[i]);
	if (backward_prep.sub_preps)
		ccfree(backward_prep.sub_preps);
}