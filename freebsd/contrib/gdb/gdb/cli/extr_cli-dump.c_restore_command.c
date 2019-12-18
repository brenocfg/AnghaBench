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
struct callback_data {scalar_t__ load_start; scalar_t__ load_end; void* load_offset; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct callback_data*) ; 
 int /*<<< orphan*/ * bfd_openr_with_cleanup (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*) ; 
 scalar_t__ info_verbose ; 
 int /*<<< orphan*/  noprocess () ; 
 void* parse_and_eval_long (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,unsigned long,unsigned long,unsigned long) ; 
 int /*<<< orphan*/  restore_binary_file (char*,struct callback_data*) ; 
 int /*<<< orphan*/  restore_section_callback ; 
 char* scan_expression_with_cleanup (char**,int /*<<< orphan*/ *) ; 
 char* scan_filename_with_cleanup (char**,int /*<<< orphan*/ *) ; 
 char* skip_spaces (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_has_execution ; 

__attribute__((used)) static void
restore_command (char *args, int from_tty)
{
  char *filename;
  struct callback_data data;
  bfd *ibfd;
  int binary_flag = 0;

  if (!target_has_execution)
    noprocess ();

  data.load_offset = 0;
  data.load_start  = 0;
  data.load_end    = 0;

  /* Parse the input arguments.  First is filename (required). */
  filename = scan_filename_with_cleanup (&args, NULL);
  if (args != NULL && *args != '\0')
    {
      char *binary_string = "binary";

      /* Look for optional "binary" flag.  */
      if (strncmp (args, binary_string, strlen (binary_string)) == 0)
	{
	  binary_flag = 1;
	  args += strlen (binary_string);
	  args = skip_spaces (args);
	}
      /* Parse offset (optional). */
      if (args != NULL && *args != '\0')
      data.load_offset = 
	parse_and_eval_long (scan_expression_with_cleanup (&args, NULL));
      if (args != NULL && *args != '\0')
	{
	  /* Parse start address (optional). */
	  data.load_start = 
	    parse_and_eval_long (scan_expression_with_cleanup (&args, NULL));
	  if (args != NULL && *args != '\0')
	    {
	      /* Parse end address (optional). */
	      data.load_end = parse_and_eval_long (args);
	      if (data.load_end <= data.load_start)
		error ("Start must be less than end.");
	    }
	}
    }

  if (info_verbose)
    printf_filtered ("Restore file %s offset 0x%lx start 0x%lx end 0x%lx\n",
		     filename, (unsigned long) data.load_offset, 
		     (unsigned long) data.load_start, 
		     (unsigned long) data.load_end);

  if (binary_flag)
    {
      restore_binary_file (filename, &data);
    }
  else
    {
      /* Open the file for loading. */
      ibfd = bfd_openr_with_cleanup (filename, NULL);

      /* Process the sections. */
      bfd_map_over_sections (ibfd, restore_section_callback, &data);
    }
  return;
}