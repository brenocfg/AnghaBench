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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 char* current_function_name () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,char*) ; 
 int graph_dump_format ; 
#define  no_graph 129 
#define  vcg 128 

__attribute__((used)) static void
start_fct (FILE *fp)
{
  switch (graph_dump_format)
    {
    case vcg:
      fprintf (fp, "\
graph: { title: \"%s\"\nfolding: 1\nhidden: 2\nnode: { title: \"%s.0\" }\n",
	       current_function_name (), current_function_name ());
      break;
    case no_graph:
      break;
    }
}