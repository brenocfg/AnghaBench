#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* print_archive_member ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* print_archive_filename ) (int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  PROGRESS (int) ; 
 scalar_t__ bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 scalar_t__ bfd_error_no_more_archived_files ; 
 int /*<<< orphan*/  bfd_fatal (int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr_next_archived_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_rel_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* format ; 
 int /*<<< orphan*/  free (char**) ; 
 int /*<<< orphan*/ * lineno_cache_bfd ; 
 int /*<<< orphan*/ * lineno_cache_rel_bfd ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 scalar_t__ print_armap ; 
 int /*<<< orphan*/  print_symdef_entry (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  set_print_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
display_archive (bfd *file)
{
  bfd *arfile = NULL;
  bfd *last_arfile = NULL;
  char **matching;

  format->print_archive_filename (bfd_get_filename (file));

  if (print_armap)
    print_symdef_entry (file);

  for (;;)
    {
      PROGRESS (1);

      arfile = bfd_openr_next_archived_file (file, arfile);

      if (arfile == NULL)
	{
	  if (bfd_get_error () != bfd_error_no_more_archived_files)
	    bfd_fatal (bfd_get_filename (file));
	  break;
	}

      if (bfd_check_format_matches (arfile, bfd_object, &matching))
	{
	  set_print_width (arfile);
	  format->print_archive_member (bfd_get_filename (file),
					bfd_get_filename (arfile));
	  display_rel_file (arfile, file);
	}
      else
	{
	  bfd_nonfatal (bfd_get_filename (arfile));
	  if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	    {
	      list_matching_formats (matching);
	      free (matching);
	    }
	}

      if (last_arfile != NULL)
	{
	  bfd_close (last_arfile);
	  lineno_cache_bfd = NULL;
	  lineno_cache_rel_bfd = NULL;
	}
      last_arfile = arfile;
    }

  if (last_arfile != NULL)
    {
      bfd_close (last_arfile);
      lineno_cache_bfd = NULL;
      lineno_cache_rel_bfd = NULL;
    }
}