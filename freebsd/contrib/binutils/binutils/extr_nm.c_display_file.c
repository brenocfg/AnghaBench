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
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  (* print_object_filename ) (char*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_check_format_matches (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char***) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 scalar_t__ bfd_error_file_ambiguously_recognized ; 
 int /*<<< orphan*/  bfd_fatal (char*) ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_nonfatal (char*) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/ * bfd_openr (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_archive (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  display_rel_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* format ; 
 int /*<<< orphan*/  free (char**) ; 
 int get_file_size (char*) ; 
 int /*<<< orphan*/ * lineno_cache_bfd ; 
 int /*<<< orphan*/ * lineno_cache_rel_bfd ; 
 int /*<<< orphan*/  list_matching_formats (char**) ; 
 int /*<<< orphan*/  set_print_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  target ; 

__attribute__((used)) static bfd_boolean
display_file (char *filename)
{
  bfd_boolean retval = TRUE;
  bfd *file;
  char **matching;

  if (get_file_size (filename) < 1)
    return FALSE;

  file = bfd_openr (filename, target);
  if (file == NULL)
    {
      bfd_nonfatal (filename);
      return FALSE;
    }

  if (bfd_check_format (file, bfd_archive))
    {
      display_archive (file);
    }
  else if (bfd_check_format_matches (file, bfd_object, &matching))
    {
      set_print_width (file);
      format->print_object_filename (filename);
      display_rel_file (file, NULL);
    }
  else
    {
      bfd_nonfatal (filename);
      if (bfd_get_error () == bfd_error_file_ambiguously_recognized)
	{
	  list_matching_formats (matching);
	  free (matching);
	}
      retval = FALSE;
    }

  if (!bfd_close (file))
    bfd_fatal (filename);

  lineno_cache_bfd = NULL;
  lineno_cache_rel_bfd = NULL;

  return retval;
}