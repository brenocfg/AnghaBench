#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  undef; int /*<<< orphan*/  define; int /*<<< orphan*/  read_pch; int /*<<< orphan*/  valid_pch; int /*<<< orphan*/  include; int /*<<< orphan*/  def_pragma; int /*<<< orphan*/  ident; int /*<<< orphan*/  line_change; } ;
typedef  TYPE_1__ cpp_callbacks ;
struct TYPE_7__ {scalar_t__ lang; } ;
struct TYPE_6__ {int src_line; int first_time; int /*<<< orphan*/ * outf; scalar_t__ prev; scalar_t__ printed; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ CLK_ASM ; 
 int /*<<< orphan*/  c_common_valid_pch ; 
 int /*<<< orphan*/  cb_def_pragma ; 
 int /*<<< orphan*/  cb_define ; 
 int /*<<< orphan*/  cb_ident ; 
 int /*<<< orphan*/  cb_include ; 
 int /*<<< orphan*/  cb_line_change ; 
 int /*<<< orphan*/  cb_read_pch ; 
 int /*<<< orphan*/  cb_undef ; 
 TYPE_1__* cpp_get_callbacks (int /*<<< orphan*/ ) ; 
 TYPE_3__* cpp_get_options (int /*<<< orphan*/ ) ; 
 scalar_t__ flag_dump_includes ; 
 char flag_dump_macros ; 
 int /*<<< orphan*/  flag_no_output ; 
 scalar_t__ flag_pch_preprocess ; 
 int /*<<< orphan*/  parse_in ; 
 TYPE_2__ print ; 

void
init_pp_output (FILE *out_stream)
{
  cpp_callbacks *cb = cpp_get_callbacks (parse_in);

  if (!flag_no_output)
    {
      cb->line_change = cb_line_change;
      /* Don't emit #pragma or #ident directives if we are processing
	 assembly language; the assembler may choke on them.  */
      if (cpp_get_options (parse_in)->lang != CLK_ASM)
	{
	  cb->ident      = cb_ident;
	  cb->def_pragma = cb_def_pragma;
	}
    }

  if (flag_dump_includes)
    cb->include  = cb_include;

  if (flag_pch_preprocess)
    {
      cb->valid_pch = c_common_valid_pch;
      cb->read_pch = cb_read_pch;
    }

  if (flag_dump_macros == 'N' || flag_dump_macros == 'D')
    {
      cb->define = cb_define;
      cb->undef  = cb_undef;
    }

  /* Initialize the print structure.  Setting print.src_line to -1 here is
     a trick to guarantee that the first token of the file will cause
     a linemarker to be output by maybe_print_line.  */
  print.src_line = -1;
  print.printed = 0;
  print.prev = 0;
  print.outf = out_stream;
  print.first_time = 1;
}