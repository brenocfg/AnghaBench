#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct cleanup {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_4__ {int /*<<< orphan*/  to_sections_end; int /*<<< orphan*/  to_sections; } ;

/* Variables and functions */
 int O_BINARY ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int /*<<< orphan*/  RETURN_MASK_ALL ; 
 int /*<<< orphan*/  add_to_thread_list ; 
 int /*<<< orphan*/  bfd_check_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_core ; 
 char* bfd_core_file_failing_command (int /*<<< orphan*/ *) ; 
 int bfd_core_file_failing_signal (int /*<<< orphan*/ *) ; 
 char* bfd_errmsg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * bfd_fdopenr (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_get_error () ; 
 char* bfd_get_filename (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_map_over_sections (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ build_section_table (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  catch_errors (int /*<<< orphan*/ ,int*,char*,int /*<<< orphan*/ ) ; 
 char* concat (int /*<<< orphan*/ ,char*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * core_bfd ; 
 int /*<<< orphan*/  core_close_cleanup (char*) ; 
 int /*<<< orphan*/  core_gdbarch ; 
 TYPE_1__ core_ops ; 
 int /*<<< orphan*/  core_vec ; 
 int /*<<< orphan*/  current_directory ; 
 int /*<<< orphan*/  deprecated_selected_frame ; 
 int /*<<< orphan*/  discard_cleanups (struct cleanup*) ; 
 int /*<<< orphan*/  error (char*,...) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  frame_relative_level (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gdb_check_format (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdbarch_from_bfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_current_frame () ; 
 int /*<<< orphan*/  gnutarget ; 
 int /*<<< orphan*/  init_thread_list () ; 
 struct cleanup* make_cleanup (int /*<<< orphan*/  (*) (char*),char*) ; 
 int /*<<< orphan*/  make_cleanup_bfd_close (int /*<<< orphan*/ *) ; 
 int open (char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  push_target (TYPE_1__*) ; 
 int /*<<< orphan*/  select_frame (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_gdbarch_from_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sniff_core_bfd (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  solib_add_stub ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 
 int /*<<< orphan*/  target_longname ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  target_signal_from_host (int) ; 
 int /*<<< orphan*/  target_signal_to_string (int /*<<< orphan*/ ) ; 
 char* tilde_expand (char*) ; 
 int /*<<< orphan*/  unpush_target (TYPE_1__*) ; 
 int /*<<< orphan*/  validate_files () ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ write_files ; 
 int /*<<< orphan*/  xfree (char*) ; 

__attribute__((used)) static void
core_open (char *filename, int from_tty)
{
  const char *p;
  int siggy;
  struct cleanup *old_chain;
  char *temp;
  bfd *temp_bfd;
  int ontop;
  int scratch_chan;

  target_preopen (from_tty);
  if (!filename)
    {
      error (core_bfd ?
	     "No core file specified.  (Use `detach' to stop debugging a core file.)"
	     : "No core file specified.");
    }

  filename = tilde_expand (filename);
  if (filename[0] != '/')
    {
      temp = concat (current_directory, "/", filename, NULL);
      xfree (filename);
      filename = temp;
    }

  old_chain = make_cleanup (xfree, filename);

  scratch_chan = open (filename, O_BINARY | ( write_files ? O_RDWR : O_RDONLY ), 0);
  if (scratch_chan < 0)
    perror_with_name (filename);

  temp_bfd = bfd_fdopenr (filename, gnutarget, scratch_chan);
  if (temp_bfd == NULL)
    perror_with_name (filename);

  if (!bfd_check_format (temp_bfd, bfd_core) &&
      !gdb_check_format (temp_bfd))
    {
      /* Do it after the err msg */
      /* FIXME: should be checking for errors from bfd_close (for one thing,
         on error it does not free all the storage associated with the
         bfd).  */
      make_cleanup_bfd_close (temp_bfd);
      error ("\"%s\" is not a core dump: %s",
	     filename, bfd_errmsg (bfd_get_error ()));
    }

  /* Looks semi-reasonable.  Toss the old core file and work on the new.  */

  discard_cleanups (old_chain);	/* Don't free filename any more */
  unpush_target (&core_ops);
  core_bfd = temp_bfd;
  old_chain = make_cleanup (core_close_cleanup, 0 /*ignore*/);

  /* FIXME: kettenis/20031023: This is very dangerous.  The
     CORE_GDBARCH that results from this call may very well be
     different from CURRENT_GDBARCH.  However, its methods may only
     work if it is selected as the current architecture, because they
     rely on swapped data (see gdbarch.c).  We should get rid of that
     swapped data.  */
  core_gdbarch = gdbarch_from_bfd (core_bfd);

  /* Find a suitable core file handler to munch on core_bfd */
  core_vec = sniff_core_bfd (core_bfd);

  validate_files ();

  /* Find the data section */
  if (build_section_table (core_bfd, &core_ops.to_sections,
			   &core_ops.to_sections_end))
    error ("\"%s\": Can't find sections: %s",
	   bfd_get_filename (core_bfd), bfd_errmsg (bfd_get_error ()));

  /* If we have no exec file, try to set the architecture from the
     core file.  We don't do this unconditionally since an exec file
     typically contains more information that helps us determine the
     architecture than a core file.  */
  if (!exec_bfd)
    set_gdbarch_from_file (core_bfd);

  ontop = !push_target (&core_ops);
  discard_cleanups (old_chain);

  p = bfd_core_file_failing_command (core_bfd);
  if (p)
    printf_filtered ("Core was generated by `%s'.\n", p);

  siggy = bfd_core_file_failing_signal (core_bfd);
  if (siggy > 0)
    /* NOTE: target_signal_from_host() converts a target signal value
       into gdb's internal signal value.  Unfortunately gdb's internal
       value is called ``target_signal'' and this function got the
       name ..._from_host(). */
    printf_filtered ("Program terminated with signal %d, %s.\n", siggy,
		     target_signal_to_string (target_signal_from_host (siggy)));

  /* Build up thread list from BFD sections. */

  init_thread_list ();
  bfd_map_over_sections (core_bfd, add_to_thread_list,
			 bfd_get_section_by_name (core_bfd, ".reg"));

  if (ontop)
    {
      /* Fetch all registers from core file.  */
      target_fetch_registers (-1);

      /* Add symbols and section mappings for any shared libraries.  */
#ifdef SOLIB_ADD
      catch_errors (solib_add_stub, &from_tty, (char *) 0,
		    RETURN_MASK_ALL);
#endif

      /* Now, set up the frame cache, and print the top of stack.  */
      flush_cached_frames ();
      select_frame (get_current_frame ());
      print_stack_frame (deprecated_selected_frame,
			 frame_relative_level (deprecated_selected_frame), 1);
    }
  else
    {
      warning (
		"you won't be able to access this core file until you terminate\n\
your %s; do ``info files''", target_longname);
    }
}