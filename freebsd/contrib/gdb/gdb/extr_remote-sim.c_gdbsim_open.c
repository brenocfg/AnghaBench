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

/* Variables and functions */
#define  BFD_ENDIAN_BIG 130 
#define  BFD_ENDIAN_LITTLE 129 
#define  BFD_ENDIAN_UNKNOWN 128 
 int /*<<< orphan*/  SIM_OPEN_DEBUG ; 
 scalar_t__ alloca (int) ; 
 char** buildargv (char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  exec_bfd ; 
 int /*<<< orphan*/  gdb_callback ; 
 int /*<<< orphan*/ * gdbsim_desc ; 
 int /*<<< orphan*/  gdbsim_ops ; 
 int /*<<< orphan*/  init_callbacks () ; 
 int /*<<< orphan*/  make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 char* selected_architecture_name () ; 
 int selected_byte_order () ; 
 int /*<<< orphan*/ * sim_open (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ sr_get_debug () ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  target_fetch_registers (int) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
gdbsim_open (char *args, int from_tty)
{
  int len;
  char *arg_buf;
  char **argv;

  if (sr_get_debug ())
    printf_filtered ("gdbsim_open: args \"%s\"\n", args ? args : "(null)");

  /* Remove current simulator if one exists.  Only do this if the simulator
     has been opened because sim_close requires it.
     This is important because the call to push_target below will cause
     sim_close to be called if the simulator is already open, but push_target
     is called after sim_open!  We can't move the call to push_target before
     the call to sim_open because sim_open may invoke `error'.  */
  if (gdbsim_desc != NULL)
    unpush_target (&gdbsim_ops);

  len = (7 + 1			/* gdbsim */
	 + strlen (" -E little")
	 + strlen (" --architecture=xxxxxxxxxx")
	 + (args ? strlen (args) : 0)
	 + 50) /* slack */ ;
  arg_buf = (char *) alloca (len);
  strcpy (arg_buf, "gdbsim");	/* 7 */
  /* Specify the byte order for the target when it is both selectable
     and explicitly specified by the user (not auto detected). */
  switch (selected_byte_order ())
    {
    case BFD_ENDIAN_BIG:
      strcat (arg_buf, " -E big");
      break;
    case BFD_ENDIAN_LITTLE:
      strcat (arg_buf, " -E little");
      break;
    case BFD_ENDIAN_UNKNOWN:
      break;
    }
  /* Specify the architecture of the target when it has been
     explicitly specified */
  if (selected_architecture_name () != NULL)
    {
      strcat (arg_buf, " --architecture=");
      strcat (arg_buf, selected_architecture_name ());
    }
  /* finally, any explicit args */
  if (args)
    {
      strcat (arg_buf, " ");	/* 1 */
      strcat (arg_buf, args);
    }
  argv = buildargv (arg_buf);
  if (argv == NULL)
    error ("Insufficient memory available to allocate simulator arg list.");
  make_cleanup_freeargv (argv);

  init_callbacks ();
  gdbsim_desc = sim_open (SIM_OPEN_DEBUG, &gdb_callback, exec_bfd, argv);

  if (gdbsim_desc == 0)
    error ("unable to create simulator instance");

  push_target (&gdbsim_ops);
  target_fetch_registers (-1);
  printf_filtered ("Connected to the simulator.\n");
}