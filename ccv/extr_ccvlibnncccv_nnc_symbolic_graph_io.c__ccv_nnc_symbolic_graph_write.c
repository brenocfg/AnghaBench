#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_13__ ;
typedef  struct TYPE_25__   TYPE_12__ ;
typedef  struct TYPE_24__   TYPE_11__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_27__ {int const type; int const format; int const datatype; int const* dim; } ;
struct TYPE_35__ {int const assign_ref; int const r_assign_ref; int const bypass_ref; int const r_bypass_ref; int const p_ref; int const alias_ref; int const peer_ref; int const flags; int const* ofs; int const* inc; TYPE_1__ info; scalar_t__ name; TYPE_13__* s_ref; } ;
typedef  TYPE_9__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_34__ {int const count; int const tensor_symbol_size; int const* tensor_symbol_idx; int const exec_symbol_size; int const* exec_symbol_idx; } ;
struct TYPE_33__ {int const tensor_symbol_size; int const* tensor_symbol_idx; int const exec_symbol_size; int const* exec_symbol_idx; } ;
struct TYPE_23__ {int breakpoint_size; int const p_idx; int const exec_idx; TYPE_8__ data_parallel; TYPE_7__ backward; TYPE_6__* breakpoints; struct TYPE_23__* p; struct TYPE_23__* peer; TYPE_13__* sub_graphs; TYPE_13__* destinations; TYPE_13__* sources; TYPE_13__* exec_symbol_info; TYPE_13__* tensor_symbol_info; } ;
typedef  TYPE_10__ ccv_nnc_symbolic_graph_t ;
struct TYPE_24__ {int const d; } ;
typedef  TYPE_11__ ccv_nnc_graph_exec_symbol_t ;
struct TYPE_31__ {int const input_size; int const* inputs; } ;
struct TYPE_29__ {int const offset; int const size; } ;
struct TYPE_30__ {int const flags; TYPE_3__ argument; } ;
struct TYPE_28__ {int const cmd; int const backend; int const algorithm; int const info; } ;
struct TYPE_25__ {int const input_size; int const output_size; int const graph_ref_size; int const flags; int const peer_ref; int const* inputs; int const* outputs; int const hint; TYPE_5__ p_while; TYPE_4__ case_of; TYPE_2__ cmd; scalar_t__ name; TYPE_13__* outgoings; } ;
typedef  TYPE_12__ ccv_nnc_graph_exec_symbol_info_t ;
struct TYPE_26__ {int rnum; } ;
typedef  TYPE_13__ ccv_array_t ;
struct TYPE_32__ {int const d; } ;

/* Variables and functions */
 int CCV_NNC_GRAPH_EXEC_CASE_OF ; 
 int CCV_NNC_GRAPH_EXEC_P_WHILE ; 
 int const* CCV_NNC_GRAPH_REF (TYPE_12__ const* const) ; 
 scalar_t__ SQLITE_DONE ; 
 int /*<<< orphan*/  SQLITE_ENFORCE (int) ; 
 int const _ccv_nnc_symbolic_graph_index_in_repo (TYPE_10__*,TYPE_13__ const* const) ; 
 int /*<<< orphan*/  ccv_array_clear (TYPE_13__* const) ; 
 int const* ccv_array_get (TYPE_13__* const,int) ; 
 int /*<<< orphan*/  ccv_array_push (TYPE_13__* const,int const*) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ * const,int,int const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ * const,int,int const) ; 
 int /*<<< orphan*/  sqlite3_bind_null (int /*<<< orphan*/ * const,int) ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ * const,int,scalar_t__,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ * const) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ * const) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ * const) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_write(const ccv_nnc_symbolic_graph_t* const graph, const ccv_array_t* const repo, const int graph_idx, sqlite3_stmt* const tensor_symbol_insert_stmt, sqlite3_stmt* const exec_symbol_insert_stmt, sqlite3_stmt* const graph_insert_stmt, ccv_array_t* const ws)
{
	int i;
	for (i = 0; i < graph->tensor_symbol_info->rnum; i++)
	{
		const ccv_nnc_tensor_symbol_info_t* const symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, i);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 1, i);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 2, graph_idx);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 3, symbol_info->assign_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 4, symbol_info->r_assign_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 5, symbol_info->bypass_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 6, symbol_info->r_bypass_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 7, symbol_info->p_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 8, symbol_info->alias_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 9, symbol_info->peer_ref);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 10, symbol_info->flags);
		sqlite3_bind_blob(tensor_symbol_insert_stmt, 11, symbol_info->ofs, sizeof(symbol_info->ofs), 0);
		sqlite3_bind_blob(tensor_symbol_insert_stmt, 12, symbol_info->inc, sizeof(symbol_info->inc), 0);
		if (symbol_info->s_ref)
			sqlite3_bind_blob(tensor_symbol_insert_stmt, 13, ccv_array_get(symbol_info->s_ref, 0), sizeof(int) * symbol_info->s_ref->rnum, 0);
		else
			sqlite3_bind_null(tensor_symbol_insert_stmt, 13);
		if (symbol_info->name)
			sqlite3_bind_text(tensor_symbol_insert_stmt, 14, symbol_info->name, -1, 0);
		else
			sqlite3_bind_null(tensor_symbol_insert_stmt, 14);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 15, symbol_info->info.type);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 16, symbol_info->info.format);
		sqlite3_bind_int(tensor_symbol_insert_stmt, 17, symbol_info->info.datatype);
		sqlite3_bind_blob(tensor_symbol_insert_stmt, 18, symbol_info->info.dim, sizeof(symbol_info->info.dim), 0);
		SQLITE_ENFORCE(SQLITE_DONE == sqlite3_step(tensor_symbol_insert_stmt));
		sqlite3_reset(tensor_symbol_insert_stmt);
		sqlite3_clear_bindings(tensor_symbol_insert_stmt);
	}
	for (i = 0; i < graph->exec_symbol_info->rnum; i++)
	{
		const ccv_nnc_graph_exec_symbol_info_t* const symbol_info = (ccv_nnc_graph_exec_symbol_info_t*)ccv_array_get(graph->exec_symbol_info, i);
		sqlite3_bind_int(exec_symbol_insert_stmt, 1, i);
		sqlite3_bind_int(exec_symbol_insert_stmt, 2, graph_idx);
		sqlite3_bind_int(exec_symbol_insert_stmt, 3, symbol_info->input_size);
		sqlite3_bind_int(exec_symbol_insert_stmt, 4, symbol_info->output_size);
		sqlite3_bind_int(exec_symbol_insert_stmt, 5, symbol_info->graph_ref_size);
		sqlite3_bind_int(exec_symbol_insert_stmt, 6, symbol_info->flags);
		sqlite3_bind_int(exec_symbol_insert_stmt, 7, symbol_info->peer_ref);
		if (symbol_info->input_size)
			sqlite3_bind_blob(exec_symbol_insert_stmt, 8, symbol_info->inputs, sizeof(int) * symbol_info->input_size, 0);
		if (symbol_info->output_size)
			sqlite3_bind_blob(exec_symbol_insert_stmt, 9, symbol_info->outputs, sizeof(int) * symbol_info->output_size, 0);
		if (symbol_info->outgoings && symbol_info->outgoings->rnum)
			sqlite3_bind_blob(exec_symbol_insert_stmt, 10, ccv_array_get(symbol_info->outgoings, 0), sizeof(int) * symbol_info->outgoings->rnum, 0);
		if (symbol_info->name)
			sqlite3_bind_text(exec_symbol_insert_stmt, 11, symbol_info->name, -1, 0);
		sqlite3_bind_int(exec_symbol_insert_stmt, 12, symbol_info->cmd.cmd);
		sqlite3_bind_int(exec_symbol_insert_stmt, 13, symbol_info->cmd.backend);
		sqlite3_bind_int(exec_symbol_insert_stmt, 14, symbol_info->cmd.algorithm);
		sqlite3_bind_blob(exec_symbol_insert_stmt, 15, &symbol_info->cmd.info, sizeof(symbol_info->cmd.info), 0);
		sqlite3_bind_blob(exec_symbol_insert_stmt, 16, &symbol_info->hint, sizeof(symbol_info->hint), 0);
		if (symbol_info->graph_ref_size)
			sqlite3_bind_blob(exec_symbol_insert_stmt, 17, CCV_NNC_GRAPH_REF(symbol_info), sizeof(int) * symbol_info->graph_ref_size, 0);
		if (symbol_info->flags & CCV_NNC_GRAPH_EXEC_CASE_OF)
		{
			sqlite3_bind_int(exec_symbol_insert_stmt, 18, 0);
			sqlite3_bind_int(exec_symbol_insert_stmt, 19, symbol_info->case_of.flags);
			sqlite3_bind_int(exec_symbol_insert_stmt, 20, symbol_info->case_of.argument.offset);
			sqlite3_bind_int(exec_symbol_insert_stmt, 21, symbol_info->case_of.argument.size);
		}
		if (symbol_info->flags & CCV_NNC_GRAPH_EXEC_P_WHILE)
		{
			sqlite3_bind_int(exec_symbol_insert_stmt, 22, 0);
			sqlite3_bind_int(exec_symbol_insert_stmt, 23, symbol_info->p_while.input_size);
			if (symbol_info->p_while.input_size)
				sqlite3_bind_blob(exec_symbol_insert_stmt, 24, symbol_info->p_while.inputs, sizeof(int) * symbol_info->p_while.input_size, 0);
		}
		SQLITE_ENFORCE(SQLITE_DONE == sqlite3_step(exec_symbol_insert_stmt));
		sqlite3_reset(exec_symbol_insert_stmt);
		sqlite3_clear_bindings(exec_symbol_insert_stmt);
	}
	ccv_array_clear(ws);
	sqlite3_bind_int(graph_insert_stmt, 1, graph_idx);
	sqlite3_bind_int(graph_insert_stmt, 2, graph->tensor_symbol_info->rnum);
	sqlite3_bind_int(graph_insert_stmt, 3, graph->exec_symbol_info->rnum);
	if (graph->sources && graph->sources->rnum)
		for (i = 0; i < graph->sources->rnum; i++)
			ccv_array_push(ws, &((ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->sources, i))->d);
	if (graph->destinations && graph->destinations->rnum)
		for (i = 0; i < graph->destinations->rnum; i++)
			ccv_array_push(ws, &((ccv_nnc_graph_exec_symbol_t*)ccv_array_get(graph->destinations, i))->d);
	if (graph->sub_graphs && graph->sub_graphs->rnum)
		for (i = 0; i < graph->sub_graphs->rnum; i++)
		{
			const int sub_graph_idx = _ccv_nnc_symbolic_graph_index_in_repo(*(ccv_nnc_symbolic_graph_t**)ccv_array_get(graph->sub_graphs, i), repo);
			ccv_array_push(ws, &sub_graph_idx);
		}
	if (graph->breakpoint_size && graph->breakpoints)
		for (i = 0; i < graph->breakpoint_size; i++)
			ccv_array_push(ws, &graph->breakpoints[i].d);
	const int* pos = (int*)ccv_array_get(ws, 0);
	if (graph->sources && graph->sources->rnum)
	{
		sqlite3_bind_blob(graph_insert_stmt, 4, pos, sizeof(int) * graph->sources->rnum, 0);
		pos += graph->sources->rnum;
	}
	if (graph->destinations && graph->destinations->rnum)
	{
		sqlite3_bind_blob(graph_insert_stmt, 5, pos, sizeof(int) * graph->destinations->rnum, 0);
		pos += graph->destinations->rnum;
	}
	if (graph->sub_graphs && graph->sub_graphs->rnum)
	{
		sqlite3_bind_blob(graph_insert_stmt, 6, pos, sizeof(int) * graph->sub_graphs->rnum, 0);
		pos += graph->sub_graphs->rnum;
	}
	sqlite3_bind_int(graph_insert_stmt, 7, _ccv_nnc_symbolic_graph_index_in_repo(graph->peer, repo));
	sqlite3_bind_int(graph_insert_stmt, 8, _ccv_nnc_symbolic_graph_index_in_repo(graph->p, repo));
	sqlite3_bind_int(graph_insert_stmt, 9, graph->p_idx);
	sqlite3_bind_int(graph_insert_stmt, 10, graph->exec_idx);
	sqlite3_bind_int(graph_insert_stmt, 11, graph->breakpoint_size);
	if (graph->breakpoint_size && graph->breakpoints)
		sqlite3_bind_blob(graph_insert_stmt, 12, pos, sizeof(int) * graph->breakpoint_size, 0);
	sqlite3_bind_int(graph_insert_stmt, 13, graph->backward.tensor_symbol_size);
	if (graph->backward.tensor_symbol_size)
		sqlite3_bind_blob(graph_insert_stmt, 14, graph->backward.tensor_symbol_idx, sizeof(int) * graph->backward.tensor_symbol_size, 0);
	sqlite3_bind_int(graph_insert_stmt, 15, graph->backward.exec_symbol_size);
	if (graph->backward.exec_symbol_size)
		sqlite3_bind_blob(graph_insert_stmt, 16, graph->backward.exec_symbol_idx, sizeof(int) * graph->backward.exec_symbol_size, 0);
	sqlite3_bind_int(graph_insert_stmt, 17, graph->data_parallel.count);
	sqlite3_bind_int(graph_insert_stmt, 18, graph->data_parallel.tensor_symbol_size);
	if (graph->data_parallel.tensor_symbol_idx)
		sqlite3_bind_blob(graph_insert_stmt, 19, graph->data_parallel.tensor_symbol_idx, sizeof(int) * graph->data_parallel.tensor_symbol_size, 0);
	sqlite3_bind_int(graph_insert_stmt, 20, graph->data_parallel.exec_symbol_size);
	if (graph->data_parallel.exec_symbol_idx)
		sqlite3_bind_blob(graph_insert_stmt, 21, graph->data_parallel.exec_symbol_idx, sizeof(int) * graph->data_parallel.exec_symbol_size, 0);
	SQLITE_ENFORCE(SQLITE_DONE == sqlite3_step(graph_insert_stmt));
	sqlite3_reset(graph_insert_stmt);
	sqlite3_clear_bindings(graph_insert_stmt);
}