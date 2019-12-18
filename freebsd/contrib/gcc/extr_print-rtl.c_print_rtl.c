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
typedef  scalar_t__ rtx ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
#define  BARRIER 133 
#define  CALL_INSN 132 
#define  CODE_LABEL 131 
 int GET_CODE (scalar_t__) ; 
#define  INSN 130 
#define  JUMP_INSN 129 
 scalar_t__ NEXT_INSN (scalar_t__) ; 
#define  NOTE 128 
 int /*<<< orphan*/  NOTE_LINE_NUMBER (scalar_t__) ; 
 int /*<<< orphan*/  NOTE_P (scalar_t__) ; 
 int /*<<< orphan*/  flag_dump_unnumbered ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * outfile ; 
 int /*<<< orphan*/  print_rtx (scalar_t__) ; 
 char* print_rtx_head ; 
 scalar_t__ sawclose ; 

void
print_rtl (FILE *outf, rtx rtx_first)
{
  rtx tmp_rtx;

  outfile = outf;
  sawclose = 0;

  if (rtx_first == 0)
    {
      fputs (print_rtx_head, outf);
      fputs ("(nil)\n", outf);
    }
  else
    switch (GET_CODE (rtx_first))
      {
      case INSN:
      case JUMP_INSN:
      case CALL_INSN:
      case NOTE:
      case CODE_LABEL:
      case BARRIER:
	for (tmp_rtx = rtx_first; tmp_rtx != 0; tmp_rtx = NEXT_INSN (tmp_rtx))
	  if (! flag_dump_unnumbered
	      || !NOTE_P (tmp_rtx) || NOTE_LINE_NUMBER (tmp_rtx) < 0)
	    {
	      fputs (print_rtx_head, outfile);
	      print_rtx (tmp_rtx);
	      fprintf (outfile, "\n");
	    }
	break;

      default:
	fputs (print_rtx_head, outfile);
	print_rtx (rtx_first);
      }
}