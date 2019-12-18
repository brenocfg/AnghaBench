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
typedef  int /*<<< orphan*/  rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CALL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_NOTE_INSN_NAME (scalar_t__) ; 
 char* GET_RTX_NAME (int /*<<< orphan*/ ) ; 
 scalar_t__ INSN_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  JUMP_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LABEL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  NONJUMP_INSN_P (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTE_LINE_NUMBER (int /*<<< orphan*/ ) ; 
 scalar_t__ NOTE_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PATTERN (int /*<<< orphan*/ ) ; 
 scalar_t__ PREV_INSN (int /*<<< orphan*/ ) ; 
 int XINT (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* current_function_name () ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int graph_dump_format ; 
#define  no_graph 129 
 int /*<<< orphan*/  print_rtl_single (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  vcg 128 

__attribute__((used)) static void
node_data (FILE *fp, rtx tmp_rtx)
{
  if (PREV_INSN (tmp_rtx) == 0)
    {
      /* This is the first instruction.  Add an edge from the starting
	 block.  */
      switch (graph_dump_format)
	{
	case vcg:
	  fprintf (fp, "\
edge: { sourcename: \"%s.0\" targetname: \"%s.%d\" }\n",
		   current_function_name (),
		   current_function_name (), XINT (tmp_rtx, 0));
	  break;
	case no_graph:
	  break;
	}
    }

  switch (graph_dump_format)
    {
    case vcg:
      fprintf (fp, "node: {\n  title: \"%s.%d\"\n  color: %s\n  \
label: \"%s %d\n",
	       current_function_name (), XINT (tmp_rtx, 0),
	       NOTE_P (tmp_rtx) ? "lightgrey"
	       : NONJUMP_INSN_P (tmp_rtx) ? "green"
	       : JUMP_P (tmp_rtx) ? "darkgreen"
	       : CALL_P (tmp_rtx) ? "darkgreen"
	       : LABEL_P (tmp_rtx) ?  "\
darkgrey\n  shape: ellipse" : "white",
	       GET_RTX_NAME (GET_CODE (tmp_rtx)), XINT (tmp_rtx, 0));
      break;
    case no_graph:
      break;
    }

  /* Print the RTL.  */
  if (NOTE_P (tmp_rtx))
    {
      const char *name = "";
      if (NOTE_LINE_NUMBER (tmp_rtx) < 0)
	name =  GET_NOTE_INSN_NAME (NOTE_LINE_NUMBER (tmp_rtx));
      fprintf (fp, " %s", name);
    }
  else if (INSN_P (tmp_rtx))
    print_rtl_single (fp, PATTERN (tmp_rtx));
  else
    print_rtl_single (fp, tmp_rtx);

  switch (graph_dump_format)
    {
    case vcg:
      fputs ("\"\n}\n", fp);
      break;
    case no_graph:
      break;
    }
}