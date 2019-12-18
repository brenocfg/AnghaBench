#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  to_sections_end; int /*<<< orphan*/  to_sections; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEPRECATED_HPUX_TEXT_END (TYPE_1__*) ; 
 int O_BINARY ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 int /*<<< orphan*/  bfd_object ; 
 scalar_t__ build_section_table (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  error (char*,char*,char*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  exec_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec_file_display_hook (char*) ; 
 TYPE_1__ exec_ops ; 
 int /*<<< orphan*/  getenv (char*) ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  make_cleanup (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  map_vmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int openp (int /*<<< orphan*/ ,int,char*,int,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  push_target (TYPE_1__*) ; 
 int /*<<< orphan*/  set_gdbarch_from_file (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  stub1 (char*) ; 
 int /*<<< orphan*/  unpush_target (TYPE_1__*) ; 
 int /*<<< orphan*/  validate_files () ; 
 int /*<<< orphan*/ * vmap ; 
 scalar_t__ write_files ; 
 int /*<<< orphan*/  xfree ; 
 char* xstrdup (char*) ; 

void
exec_file_attach (char *filename, int from_tty)
{
  /* Remove any previous exec file.  */
  unpush_target (&exec_ops);

  /* Now open and digest the file the user requested, if any.  */

  if (!filename)
    {
      if (from_tty)
        printf_unfiltered ("No executable file now.\n");
    }
  else
    {
      char *scratch_pathname;
      int scratch_chan;

      scratch_chan = openp (getenv ("PATH"), 1, filename,
		   write_files ? O_RDWR | O_BINARY : O_RDONLY | O_BINARY, 0,
			    &scratch_pathname);
#if defined(__GO32__) || defined(_WIN32) || defined(__CYGWIN__)
      if (scratch_chan < 0)
	{
	  char *exename = alloca (strlen (filename) + 5);
	  strcat (strcpy (exename, filename), ".exe");
	  scratch_chan = openp (getenv ("PATH"), 1, exename, write_files ?
	     O_RDWR | O_BINARY : O_RDONLY | O_BINARY, 0, &scratch_pathname);
	}
#endif
      if (scratch_chan < 0)
	perror_with_name (filename);
      exec_bfd = bfd_fdopenr (scratch_pathname, gnutarget, scratch_chan);

      if (!exec_bfd)
	error ("\"%s\": could not open as an executable file: %s",
	       scratch_pathname, bfd_errmsg (bfd_get_error ()));

      /* At this point, scratch_pathname and exec_bfd->name both point to the
         same malloc'd string.  However exec_close() will attempt to free it
         via the exec_bfd->name pointer, so we need to make another copy and
         leave exec_bfd as the new owner of the original copy. */
      scratch_pathname = xstrdup (scratch_pathname);
      make_cleanup (xfree, scratch_pathname);

      if (!bfd_check_format (exec_bfd, bfd_object))
	{
	  /* Make sure to close exec_bfd, or else "run" might try to use
	     it.  */
	  exec_close (0);
	  error ("\"%s\": not in executable format: %s",
		 scratch_pathname, bfd_errmsg (bfd_get_error ()));
	}

      /* FIXME - This should only be run for RS6000, but the ifdef is a poor
         way to accomplish.  */
#ifdef DEPRECATED_IBM6000_TARGET
      /* Setup initial vmap. */

      map_vmap (exec_bfd, 0);
      if (vmap == NULL)
	{
	  /* Make sure to close exec_bfd, or else "run" might try to use
	     it.  */
	  exec_close (0);
	  error ("\"%s\": can't find the file sections: %s",
		 scratch_pathname, bfd_errmsg (bfd_get_error ()));
	}
#endif /* DEPRECATED_IBM6000_TARGET */

      if (build_section_table (exec_bfd, &exec_ops.to_sections,
			       &exec_ops.to_sections_end))
	{
	  /* Make sure to close exec_bfd, or else "run" might try to use
	     it.  */
	  exec_close (0);
	  error ("\"%s\": can't find the file sections: %s",
		 scratch_pathname, bfd_errmsg (bfd_get_error ()));
	}

#ifdef DEPRECATED_HPUX_TEXT_END
      DEPRECATED_HPUX_TEXT_END (&exec_ops);
#endif

      validate_files ();

      set_gdbarch_from_file (exec_bfd);

      push_target (&exec_ops);

      /* Tell display code (if any) about the changed file name.  */
      if (exec_file_display_hook)
	(*exec_file_display_hook) (filename);
    }
}