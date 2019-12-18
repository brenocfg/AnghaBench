#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct cgraph_varpool_node {scalar_t__ externally_visible; scalar_t__ output; scalar_t__ finalized; scalar_t__ analyzed; scalar_t__ needed; int /*<<< orphan*/  decl; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ DECL_INITIAL (int /*<<< orphan*/ ) ; 
 char** availability_names ; 
 scalar_t__ cgraph_function_flags_ready ; 
 size_t cgraph_variable_initializer_availability (struct cgraph_varpool_node*) ; 
 char* cgraph_varpool_node_name (struct cgraph_varpool_node*) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

void
dump_cgraph_varpool_node (FILE *f, struct cgraph_varpool_node *node)
{
  fprintf (f, "%s:", cgraph_varpool_node_name (node));
  fprintf (f, " availability:%s",
	   cgraph_function_flags_ready
	   ? availability_names[cgraph_variable_initializer_availability (node)]
	   : "not-ready");
  if (DECL_INITIAL (node->decl))
    fprintf (f, " initialized");
  if (node->needed)
    fprintf (f, " needed");
  if (node->analyzed)
    fprintf (f, " analyzed");
  if (node->finalized)
    fprintf (f, " finalized");
  if (node->output)
    fprintf (f, " output");
  if (node->externally_visible)
    fprintf (f, " externally_visible");
  fprintf (f, "\n");
}