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
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int graph_dump_format ; 
#define  no_graph 129 
#define  vcg 128 

__attribute__((used)) static void
draw_edge (FILE *fp, int from, int to, int bb_edge, int class)
{
  const char * color;
  switch (graph_dump_format)
    {
    case vcg:
      color = "";
      if (class == 2)
	color = "color: red ";
      else if (bb_edge)
	color = "color: blue ";
      else if (class == 3)
	color = "color: green ";
      fprintf (fp,
	       "edge: { sourcename: \"%s.%d\" targetname: \"%s.%d\" %s",
	       current_function_name (), from,
	       current_function_name (), to, color);
      if (class)
	fprintf (fp, "class: %d ", class);
      fputs ("}\n", fp);
      break;
    case no_graph:
      break;
    }
}