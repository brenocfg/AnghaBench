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
 scalar_t__ DBX_DEBUG ; 
 scalar_t__ DWARF2_DEBUG ; 
 char const* current_function_file ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ mips_output_filename_first_time ; 
 int num_source_filenames ; 
 int /*<<< orphan*/  output_quoted_string (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 scalar_t__ write_symbols ; 

void
mips_output_filename (FILE *stream, const char *name)
{

  /* If we are emitting DWARF-2, let dwarf2out handle the ".file"
     directives.  */
  if (write_symbols == DWARF2_DEBUG)
    return;
  else if (mips_output_filename_first_time)
    {
      mips_output_filename_first_time = 0;
      num_source_filenames += 1;
      current_function_file = name;
      fprintf (stream, "\t.file\t%d ", num_source_filenames);
      output_quoted_string (stream, name);
      putc ('\n', stream);
    }

  /* If we are emitting stabs, let dbxout.c handle this (except for
     the mips_output_filename_first_time case).  */
  else if (write_symbols == DBX_DEBUG)
    return;

  else if (name != current_function_file
	   && strcmp (name, current_function_file) != 0)
    {
      num_source_filenames += 1;
      current_function_file = name;
      fprintf (stream, "\t.file\t%d ", num_source_filenames);
      output_quoted_string (stream, name);
      putc ('\n', stream);
    }
}