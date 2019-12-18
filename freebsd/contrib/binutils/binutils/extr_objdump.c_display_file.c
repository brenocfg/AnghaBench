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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 char* _ (char*) ; 
 int /*<<< orphan*/  bfd_archive ; 
 scalar_t__ bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_no_error ; 
 scalar_t__ bfd_error_no_more_archived_files ; 
 scalar_t__ bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * bfd_openr (char*,char*) ; 
 int /*<<< orphan*/ * bfd_openr_next_archived_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_bfd (int /*<<< orphan*/ *) ; 
 int exit_status ; 
 int get_file_size (char*) ; 
 int /*<<< orphan*/  nonfatal (char*) ; 
 int /*<<< orphan*/  printf (char*,char*) ; 

__attribute__((used)) static void
display_file (char *filename, char *target)
{
  bfd *file;
  bfd *arfile = NULL;

  if (get_file_size (filename) < 1)
    {
      exit_status = 1;
      return;
    }

  file = bfd_openr (filename, target);
  if (file == NULL)
    {
      nonfatal (filename);
      return;
    }

  /* If the file is an archive, process all of its elements.  */
  if (bfd_check_format (file, bfd_archive))
    {
      bfd *last_arfile = NULL;

      printf (_("In archive %s:\n"), bfd_get_filename (file));
      for (;;)
	{
	  bfd_set_error (bfd_error_no_error);

	  arfile = bfd_openr_next_archived_file (file, arfile);
	  if (arfile == NULL)
	    {
	      if (bfd_get_error () != bfd_error_no_more_archived_files)
		nonfatal (bfd_get_filename (file));
	      break;
	    }

	  display_bfd (arfile);

	  if (last_arfile != NULL)
	    bfd_close (last_arfile);
	  last_arfile = arfile;
	}

      if (last_arfile != NULL)
	bfd_close (last_arfile);
    }
  else
    display_bfd (file);

  bfd_close (file);
}