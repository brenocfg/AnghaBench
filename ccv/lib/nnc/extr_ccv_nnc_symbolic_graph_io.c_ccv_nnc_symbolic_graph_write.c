#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  tensor_symbol_insert_qs ;
typedef  int /*<<< orphan*/  tensor_bind_insert_qs ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  graph_insert_qs ;
typedef  int /*<<< orphan*/  exec_symbol_insert_qs ;
struct TYPE_23__ {void* u8; } ;
struct TYPE_30__ {int const type; int const format; int const datatype; void* dim; } ;
struct TYPE_25__ {TYPE_2__ data; TYPE_9__ info; } ;
typedef  TYPE_4__ ccv_nnc_tensor_t ;
struct TYPE_22__ {int const type; int const format; int const datatype; void* dim; } ;
struct TYPE_26__ {TYPE_1__ info; } ;
typedef  TYPE_5__ ccv_nnc_tensor_symbol_info_t ;
struct TYPE_24__ {int const d; int /*<<< orphan*/  graph; } ;
struct TYPE_27__ {TYPE_3__ symbol; TYPE_4__* tensor; } ;
typedef  TYPE_6__ ccv_nnc_tensor_bind_t ;
struct TYPE_28__ {TYPE_8__* const tensor_symbol_info; } ;
typedef  TYPE_7__ ccv_nnc_symbolic_graph_t ;
struct TYPE_29__ {int rnum; } ;
typedef  TYPE_8__ ccv_array_t ;

/* Variables and functions */
 int /*<<< orphan*/  CCV_IS_TENSOR_VIEW (TYPE_4__ const* const) ; 
 int /*<<< orphan*/  CCV_TENSOR_CPU_MEMORY ; 
 scalar_t__ CCV_TENSOR_GET_MEMORY (int const) ; 
 scalar_t__ CCV_TENSOR_GPU_MEMORY ; 
 int /*<<< orphan*/  SQLITE_ENFORCE (int) ; 
 scalar_t__ SQLITE_OK ; 
 int _ccv_nnc_symbolic_graph_index_in_repo (int /*<<< orphan*/ ,TYPE_8__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_push_repo (TYPE_7__ const* const,TYPE_8__* const) ; 
 int /*<<< orphan*/  _ccv_nnc_symbolic_graph_write (TYPE_7__*,TYPE_8__* const,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_8__* const) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  ccfree (void*) ; 
 void* ccmalloc (size_t const) ; 
 void* ccrealloc (void*,size_t const) ; 
 int /*<<< orphan*/  ccv_array_free (TYPE_8__* const) ; 
 scalar_t__ ccv_array_get (TYPE_8__* const,int) ; 
 TYPE_8__* ccv_array_new (int,int,int /*<<< orphan*/ ) ; 
 size_t ccv_nnc_tensor_data_size (TYPE_9__) ; 
 int /*<<< orphan*/  cumemcpy (void*,int /*<<< orphan*/ ,void*,int const,size_t const) ; 
 int /*<<< orphan*/  sqlite3_bind_blob (int /*<<< orphan*/ *,int,void*,size_t const,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int (int /*<<< orphan*/ *,int,int const) ; 
 int /*<<< orphan*/  sqlite3_clear_bindings (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_open (char const* const,int /*<<< orphan*/ **) ; 
 scalar_t__ sqlite3_prepare_v2 (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

void ccv_nnc_symbolic_graph_write(const ccv_nnc_symbolic_graph_t* const graph, const ccv_nnc_tensor_bind_t* const tensor_binds, const int tensor_bind_size, const char* const fn)
{
	sqlite3* conn = 0;
	if (SQLITE_OK != sqlite3_open(fn, &conn))
		return;
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, "BEGIN", 0, 0, 0));
	const char tensor_symbol_create_table_qs[] = "CREATE TABLE IF NOT EXISTS tensor_symbol "
		"(id INTEGER, graph INTEGER, assign_ref INTEGER, r_assign_ref INTEGER, "
		"bypass_ref INTEGER, r_bypass_ref INTEGER, p_ref INTEGER, alias_ref INTEGER, pair_ref INTEGER, "
		"flags INTEGER, ofs BLOB, inc BLOB, s_ref BLOB, name TEXT, type INTEGER, format INTEGER, "
		"datatype INTEGER, dim BLOB, PRIMARY KEY (id, graph))";
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, tensor_symbol_create_table_qs, 0, 0, 0));
	const char tensor_symbol_insert_qs[] = 
		"REPLACE INTO tensor_symbol "
		"(id, graph, assign_ref, r_assign_ref, bypass_ref, r_bypass_ref, p_ref, alias_ref, pair_ref, flags, "
		"ofs, inc, s_ref, name, type, format, datatype, dim) VALUES "
		"($id, $graph, $assign_ref, $r_assign_ref, $bypass_ref, $r_bypass_ref, $p_ref, $alias_ref, $pair_ref, "
		"$flags, $ofs, $inc, $s_ref, $name, $type, $format, $datatype, $dim)";
	sqlite3_stmt* tensor_symbol_insert_stmt = 0;
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_prepare_v2(conn, tensor_symbol_insert_qs, sizeof(tensor_symbol_insert_qs), &tensor_symbol_insert_stmt, 0));

	const char exec_symbol_create_table_qs[] = "CREATE TABLE IF NOT EXISTS graph_exec_symbol "
		"(id INTEGER, graph INTEGER, input_size INTEGER, output_size INTEGER, graph_ref_size INTEGER, "
		"flags INTEGER, pair_ref INTEGER, inputs BLOB, outputs BLOB, outgoings BLOB, name TEXT, "
		"cmd_cmd INTEGER, cmd_backend INTEGER, cmd_algorithm INTEGER, cmd_info BLOB, hint BLOB, graph_ref BLOB, "
		"case_of_expr INTEGER, case_of_flags INTEGER, case_of_argument_offset INTEGER, case_of_argument_size INTEGER, "
		"p_while_expr INTEGER, p_while_input_size INTEGER, p_while_inputs BLOB, PRIMARY KEY (id, graph))";
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, exec_symbol_create_table_qs, 0, 0, 0));
	const char exec_symbol_insert_qs[] = 
		"REPLACE INTO graph_exec_symbol "
		"(id, graph, input_size, output_size, graph_ref_size, flags, pair_ref, inputs, outputs, outgoings, "
		"name, cmd_cmd, cmd_backend, cmd_algorithm, cmd_info, hint, graph_ref, case_of_expr, case_of_flags, "
		"case_of_argument_offset, case_of_argument_size, p_while_expr, p_while_input_size, p_while_inputs) "
		"VALUES ($id, $graph, $input_size, $output_size, $graph_ref_size, $flags, $pair_ref, $inputs, $outputs, "
		"$outgoings, $name, $cmd_cmd, $cmd_backend, $cmd_algorithm, $cmd_info, $hint, $graph_ref, $case_of_expr, "
		"$case_of_flags, $case_of_argument_offset, $case_of_argument_size, $p_while_expr, $p_while_input_size, "
		"$p_while_inputs)";
	sqlite3_stmt* exec_symbol_insert_stmt = 0;
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_prepare_v2(conn, exec_symbol_insert_qs, sizeof(exec_symbol_insert_qs), &exec_symbol_insert_stmt, 0));

	const char graph_create_table_qs[] = "CREATE TABLE IF NOT EXISTS graph "
		"(graph INTEGER PRIMARY KEY, tensor_symbol_size INTEGER, exec_symbol_size INTEGER, sources BLOB, "
		"destinations BLOB, sub_graphs BLOB, pair INTEGER, p INTEGER, p_idx INTEGER, exec_idx INTEGER, "
		"breakpoint_size INTEGER, breakpoints BLOB, backward_tensor_symbol_size INTEGER, "
		"backward_tensor_symbol_idx BLOB, backward_exec_symbol_size INTEGER, backward_exec_symbol_idx BLOB, "
		"parallel_count INTEGER, parallel_tensor_symbol_size INTEGER, parallel_tensor_symbol_idx BLOB, "
		"parallel_exec_symbol_size INTEGER, parallel_exec_symbol_idx BLOB)";
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, graph_create_table_qs, 0, 0, 0));
	const char graph_insert_qs[] = 
		"REPLACE INTO graph "
		"(graph, tensor_symbol_size, exec_symbol_size, sources, destinations, sub_graphs, pair, p, p_idx, "
		"exec_idx, breakpoint_size, breakpoints, backward_tensor_symbol_size, "
		"backward_tensor_symbol_idx, backward_exec_symbol_size, backward_exec_symbol_idx, "
		"parallel_count, parallel_tensor_symbol_size, parallel_tensor_symbol_idx, "
		"parallel_exec_symbol_size, parallel_exec_symbol_idx) VALUES "
		"($graph, $tensor_symbol_size, $exec_symbol_size, $sources, $destinations, $sub_graphs, $pair, $p, $p_idx, "
		"$exec_idx, $breakpoint_size, $breakpoints, $backward_tensor_symbol_size, "
		"$backward_tensor_symbol_idx, $backward_exec_symbol_size, $backward_exec_symbol_idx, "
		"$parallel_count, $parallel_tensor_symbol_size, $parallel_tensor_symbol_idx, "
		"$parallel_exec_symbol_size, $parallel_exec_symbol_idx)";
	sqlite3_stmt* graph_insert_stmt = 0;
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_prepare_v2(conn, graph_insert_qs, sizeof(graph_insert_qs), &graph_insert_stmt, 0));
	ccv_array_t* const repo = ccv_array_new(sizeof(ccv_nnc_symbolic_graph_t*), 1, 0);
	_ccv_nnc_symbolic_graph_push_repo(graph, repo);
	ccv_array_t* const ws = ccv_array_new(sizeof(int), 1, 0);
	int i;
	for (i = 0; i < repo->rnum; i++)
		_ccv_nnc_symbolic_graph_write(*(ccv_nnc_symbolic_graph_t**)ccv_array_get(repo, i), repo, i,
			tensor_symbol_insert_stmt, exec_symbol_insert_stmt, graph_insert_stmt, ws);
	ccv_array_free(ws);
	sqlite3_finalize(tensor_symbol_insert_stmt);
	sqlite3_finalize(exec_symbol_insert_stmt);
	sqlite3_finalize(graph_insert_stmt);
	// Write tensor binds.
	const char tensor_bind_create_table_qs[] = "CREATE TABLE IF NOT EXISTS tensor_bind "
		"(id INTEGER, graph INTEGER, type INTEGER, format INTEGER, datatype INTEGER, "
		"dim BLOB, data BLOB, PRIMARY KEY (id, graph))";
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, tensor_bind_create_table_qs, 0, 0, 0));
	// Remove everything in that table.
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, "DELETE FROM tensor_bind", 0, 0, 0));
	const char tensor_bind_insert_qs[] =
		"REPLACE INTO tensor_bind "
		"(id, graph, type, format, datatype, dim, data) VALUES ("
		"$id, $graph, $type, $format, $datatype, $dim, $data)";
	sqlite3_stmt* tensor_bind_insert_stmt = 0;
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_prepare_v2(conn, tensor_bind_insert_qs, sizeof(tensor_bind_insert_qs), &tensor_bind_insert_stmt, 0));
#ifdef HAVE_CUDA
	size_t workspace_size = 0;
	void* workspace = 0;
#endif
	for (i = 0; i < tensor_bind_size; i++)
	{
		const int graph_idx = _ccv_nnc_symbolic_graph_index_in_repo(tensor_binds[i].symbol.graph, repo);
		if (graph_idx < 0)
			continue;
		sqlite3_bind_int(tensor_bind_insert_stmt, 1, tensor_binds[i].symbol.d);
		sqlite3_bind_int(tensor_bind_insert_stmt, 2, graph_idx);
		if (tensor_binds[i].tensor)
		{
			const ccv_nnc_tensor_t* const tensor = tensor_binds[i].tensor;
			assert(!CCV_IS_TENSOR_VIEW(tensor));
			sqlite3_bind_int(tensor_bind_insert_stmt, 3, tensor->info.type);
			sqlite3_bind_int(tensor_bind_insert_stmt, 4, tensor->info.format);
			sqlite3_bind_int(tensor_bind_insert_stmt, 5, tensor->info.datatype);
			sqlite3_bind_blob(tensor_bind_insert_stmt, 6, tensor->info.dim, sizeof(tensor->info.dim), 0);
			const size_t data_size = ccv_nnc_tensor_data_size(tensor->info);
#ifdef HAVE_CUDA
			if (CCV_TENSOR_GET_MEMORY(tensor->info.type) == CCV_TENSOR_GPU_MEMORY)
			{
				if (!workspace)
				{
					workspace = ccmalloc(data_size);
					workspace_size = data_size;
				} else if (data_size > workspace_size) {
					workspace = ccrealloc(workspace, data_size);
					workspace_size = data_size;
				}
				cumemcpy(workspace, CCV_TENSOR_CPU_MEMORY, tensor->data.u8, tensor->info.type, data_size);
				sqlite3_bind_blob(tensor_bind_insert_stmt, 7, workspace, data_size, 0);
			} else
				sqlite3_bind_blob(tensor_bind_insert_stmt, 7, tensor->data.u8, data_size, 0);
#else
			sqlite3_bind_blob(tensor_bind_insert_stmt, 7, tensor->data.u8, data_size, 0);
#endif
		} else {
			assert(tensor_binds[i].symbol.d >= 0);
			const ccv_nnc_tensor_symbol_info_t* const symbol_info = (ccv_nnc_tensor_symbol_info_t*)ccv_array_get(graph->tensor_symbol_info, tensor_binds[i].symbol.d);
			sqlite3_bind_int(tensor_bind_insert_stmt, 3, symbol_info->info.type);
			sqlite3_bind_int(tensor_bind_insert_stmt, 4, symbol_info->info.format);
			sqlite3_bind_int(tensor_bind_insert_stmt, 5, symbol_info->info.datatype);
			sqlite3_bind_blob(tensor_bind_insert_stmt, 6, symbol_info->info.dim, sizeof(symbol_info->info.dim), 0);
		}
		sqlite3_step(tensor_bind_insert_stmt);
		sqlite3_reset(tensor_bind_insert_stmt);
		sqlite3_clear_bindings(tensor_bind_insert_stmt);
	}
	sqlite3_finalize(tensor_bind_insert_stmt);
#ifdef HAVE_CUDA
	if (workspace)
		ccfree(workspace);
#endif
	ccv_array_free(repo);
	SQLITE_ENFORCE(SQLITE_OK == sqlite3_exec(conn, "COMMIT", 0, 0, 0));
	sqlite3_close(conn);
}