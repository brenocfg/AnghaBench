#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  cmd; } ;
struct TYPE_5__ {char* name; TYPE_1__ cmd; } ;
typedef  TYPE_2__ ccv_nnc_graph_exec_symbol_info_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int const CCV_NNC_LONG_DOT_GRAPH ; 
 char* ccv_nnc_cmd_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int const) ; 
 int /*<<< orphan*/  fputc (char,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _ccv_nnc_symbolic_graph_dot_exec_symbol(const int index, const ccv_nnc_graph_exec_symbol_info_t* const symbol_info, const int flags, FILE* out)
{
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
		fputc('{', out);
	if (symbol_info->name)
		fputs(symbol_info->name, out);
	else
		fprintf(out, "node%d", index);
	if (flags == CCV_NNC_LONG_DOT_GRAPH)
	{
		fputs("|Command: ", out);
		fputs(ccv_nnc_cmd_name(symbol_info->cmd.cmd), out);
		fputc('}', out);
	}
}