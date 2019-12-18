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
 int /*<<< orphan*/  bfd_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_error_no_error ; 
 scalar_t__ bfd_error_no_more_archived_files ; 
 scalar_t__ bfd_get_error () ; 
 int /*<<< orphan*/  bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_nonfatal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_openr_next_archived_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  display_bfd (int /*<<< orphan*/ *) ; 
 int return_code ; 

__attribute__((used)) static void
display_archive (bfd *file)
{
  bfd *arfile = (bfd *) NULL;
  bfd *last_arfile = (bfd *) NULL;

  for (;;)
    {
      bfd_set_error (bfd_error_no_error);

      arfile = bfd_openr_next_archived_file (file, arfile);
      if (arfile == NULL)
	{
	  if (bfd_get_error () != bfd_error_no_more_archived_files)
	    {
	      bfd_nonfatal (bfd_get_filename (file));
	      return_code = 2;
	    }
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