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
struct group_list {struct group_list* next; struct group_list* root; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int NUM_ELEM (scalar_t__*) ; 
 char* _ (char*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  cmdline_dump_sects ; 
 scalar_t__ do_arch ; 
 scalar_t__ do_dump ; 
 scalar_t__ do_reloc ; 
 scalar_t__ do_syms ; 
 scalar_t__ do_unwind ; 
 int /*<<< orphan*/  do_using_dynamic ; 
 scalar_t__ do_version ; 
 int /*<<< orphan*/  dump_sects ; 
 scalar_t__* dynamic_info ; 
 struct group_list* dynamic_strings ; 
 scalar_t__ dynamic_strings_length ; 
 struct group_list* dynamic_symbols ; 
 struct group_list* dynamic_syminfo ; 
 int /*<<< orphan*/  error (char*,char*) ; 
 int /*<<< orphan*/  free (struct group_list*) ; 
 int /*<<< orphan*/  free_debug_memory () ; 
 int /*<<< orphan*/  get_file_header (int /*<<< orphan*/ *) ; 
 unsigned int group_count ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ num_cmdline_dump_sects ; 
 scalar_t__ num_dump_sects ; 
 scalar_t__ num_dynamic_syms ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 int /*<<< orphan*/  process_arch_specific (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_dynamic_section (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_file_header () ; 
 int /*<<< orphan*/  process_gnu_liblist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_notes (int /*<<< orphan*/ *) ; 
 scalar_t__ process_program_headers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_relocs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_section_contents (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_section_groups (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_section_headers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_symbol_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_syminfo (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_unwind (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  process_version_sections (int /*<<< orphan*/ *) ; 
 struct group_list* program_headers ; 
 int /*<<< orphan*/  request_dump (scalar_t__,int /*<<< orphan*/ ) ; 
 struct group_list* section_groups ; 
 struct group_list* section_headers ; 
 struct group_list* section_headers_groups ; 
 scalar_t__ show_name ; 
 struct group_list* string_table ; 
 scalar_t__ string_table_length ; 
 scalar_t__* version_info ; 

__attribute__((used)) static int
process_object (char *file_name, FILE *file)
{
  unsigned int i;

  if (! get_file_header (file))
    {
      error (_("%s: Failed to read file header\n"), file_name);
      return 1;
    }

  /* Initialise per file variables.  */
  for (i = NUM_ELEM (version_info); i--;)
    version_info[i] = 0;

  for (i = NUM_ELEM (dynamic_info); i--;)
    dynamic_info[i] = 0;

  /* Process the file.  */
  if (show_name)
    printf (_("\nFile: %s\n"), file_name);

  /* Initialise the dump_sects array from the cmdline_dump_sects array.
     Note we do this even if cmdline_dump_sects is empty because we
     must make sure that the dump_sets array is zeroed out before each
     object file is processed.  */
  if (num_dump_sects > num_cmdline_dump_sects)
    memset (dump_sects, 0, num_dump_sects);

  if (num_cmdline_dump_sects > 0)
    {
      if (num_dump_sects == 0)
	/* A sneaky way of allocating the dump_sects array.  */
	request_dump (num_cmdline_dump_sects, 0);

      assert (num_dump_sects >= num_cmdline_dump_sects);
      memcpy (dump_sects, cmdline_dump_sects, num_cmdline_dump_sects);
    }

  if (! process_file_header ())
    return 1;

  if (! process_section_headers (file))
    {
      /* Without loaded section headers we cannot process lots of
	 things.  */
      do_unwind = do_version = do_dump = do_arch = 0;

      if (! do_using_dynamic)
	do_syms = do_reloc = 0;
    }

  if (! process_section_groups (file))
    {
      /* Without loaded section groups we cannot process unwind.  */
      do_unwind = 0;
    }

  if (process_program_headers (file))
    process_dynamic_section (file);

  process_relocs (file);

  process_unwind (file);

  process_symbol_table (file);

  process_syminfo (file);

  process_version_sections (file);

  process_section_contents (file);

  process_notes (file);

  process_gnu_liblist (file);

  process_arch_specific (file);

  if (program_headers)
    {
      free (program_headers);
      program_headers = NULL;
    }

  if (section_headers)
    {
      free (section_headers);
      section_headers = NULL;
    }

  if (string_table)
    {
      free (string_table);
      string_table = NULL;
      string_table_length = 0;
    }

  if (dynamic_strings)
    {
      free (dynamic_strings);
      dynamic_strings = NULL;
      dynamic_strings_length = 0;
    }

  if (dynamic_symbols)
    {
      free (dynamic_symbols);
      dynamic_symbols = NULL;
      num_dynamic_syms = 0;
    }

  if (dynamic_syminfo)
    {
      free (dynamic_syminfo);
      dynamic_syminfo = NULL;
    }

  if (section_headers_groups)
    {
      free (section_headers_groups);
      section_headers_groups = NULL;
    }

  if (section_groups)
    {
      struct group_list *g, *next;

      for (i = 0; i < group_count; i++)
	{
	  for (g = section_groups [i].root; g != NULL; g = next)
	    {
	      next = g->next;
	      free (g);
	    }
	}

      free (section_groups);
      section_groups = NULL;
    }

  free_debug_memory ();

  return 0;
}