#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_1__* buffer; } ;
typedef  TYPE_2__ cpp_reader ;
struct TYPE_15__ {int /*<<< orphan*/  preprocessed; scalar_t__ directives_only; scalar_t__ traditional; } ;
struct TYPE_14__ {int /*<<< orphan*/  outf; scalar_t__ printed; } ;
struct TYPE_12__ {scalar_t__ prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpp_forall_identifiers (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_9__* cpp_get_options (TYPE_2__*) ; 
 int /*<<< orphan*/  cpp_scan_nooutput (TYPE_2__*) ; 
 int /*<<< orphan*/  dump_macro ; 
 char flag_dump_macros ; 
 scalar_t__ flag_no_output ; 
 TYPE_6__ print ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  scan_translation_unit (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_translation_unit_directives_only (TYPE_2__*) ; 
 int /*<<< orphan*/  scan_translation_unit_trad (TYPE_2__*) ; 

void
preprocess_file (cpp_reader *pfile)
{
  /* A successful cpp_read_main_file guarantees that we can call
     cpp_scan_nooutput or cpp_get_token next.  */
  if (flag_no_output)
    {
      /* Scan -included buffers, then the main file.  */
      while (pfile->buffer->prev)
	cpp_scan_nooutput (pfile);
      cpp_scan_nooutput (pfile);
    }
  else if (cpp_get_options (pfile)->traditional)
    scan_translation_unit_trad (pfile);
  else if (cpp_get_options (pfile)->directives_only
	   && !cpp_get_options (pfile)->preprocessed)
    scan_translation_unit_directives_only (pfile);
  else
    scan_translation_unit (pfile);

  /* -dM command line option.  Should this be elsewhere?  */
  if (flag_dump_macros == 'M')
    cpp_forall_identifiers (pfile, dump_macro, NULL);

  /* Flush any pending output.  */
  if (print.printed)
    putc ('\n', print.outf);
}