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
struct target_ops {int dummy; } ;
typedef  enum mips_monitor_type { ____Placeholder_mips_monitor_type } mips_monitor_type ;

/* Variables and functions */
 int baud_rate ; 
 char** buildargv (char*) ; 
 struct target_ops* current_ops ; 
 int /*<<< orphan*/  deprecated_mips_set_processor_regs_hack () ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  get_selected_frame () ; 
 int /*<<< orphan*/  make_cleanup_freeargv (char**) ; 
 int /*<<< orphan*/ * mips_desc ; 
 int /*<<< orphan*/  mips_initialize () ; 
 int mips_is_open ; 
 int mips_monitor ; 
 int /*<<< orphan*/ * mips_monitor_prompt ; 
 int /*<<< orphan*/  nomem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*) ; 
 int /*<<< orphan*/  push_target (struct target_ops*) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ *) ; 
 void* serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ *) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  stop_pc ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int tftp_in_use ; 
 char* tftp_localname ; 
 char* tftp_name ; 
 void* udp_desc ; 
 int udp_in_use ; 
 int /*<<< orphan*/  unpush_target (struct target_ops*) ; 
 int /*<<< orphan*/  xfree (char*) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static void
common_open (struct target_ops *ops, char *name, int from_tty,
	     enum mips_monitor_type new_monitor,
	     const char *new_monitor_prompt)
{
  char *ptype;
  char *serial_port_name;
  char *remote_name = 0;
  char *local_name = 0;
  char **argv;

  if (name == 0)
    error (
	    "To open a MIPS remote debugging connection, you need to specify what serial\n\
device is attached to the target board (e.g., /dev/ttya).\n"
	    "If you want to use TFTP to download to the board, specify the name of a\n"
	    "temporary file to be used by GDB for downloads as the second argument.\n"
	    "This filename must be in the form host:filename, where host is the name\n"
	    "of the host running the TFTP server, and the file must be readable by the\n"
	    "world.  If the local name of the temporary file differs from the name as\n"
	    "seen from the board via TFTP, specify that name as the third parameter.\n");

  /* Parse the serial port name, the optional TFTP name, and the
     optional local TFTP name.  */
  if ((argv = buildargv (name)) == NULL)
    nomem (0);
  make_cleanup_freeargv (argv);

  serial_port_name = xstrdup (argv[0]);
  if (argv[1])			/* remote TFTP name specified? */
    {
      remote_name = argv[1];
      if (argv[2])		/* local TFTP filename specified? */
	local_name = argv[2];
    }

  target_preopen (from_tty);

  if (mips_is_open)
    unpush_target (current_ops);

  /* Open and initialize the serial port.  */
  mips_desc = serial_open (serial_port_name);
  if (mips_desc == NULL)
    perror_with_name (serial_port_name);

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (mips_desc, baud_rate))
	{
	  serial_close (mips_desc);
	  perror_with_name (serial_port_name);
	}
    }

  serial_raw (mips_desc);

  /* Open and initialize the optional download port.  If it is in the form
     hostname#portnumber, it's a UDP socket.  If it is in the form
     hostname:filename, assume it's the TFTP filename that must be
     passed to the DDB board to tell it where to get the load file.  */
  if (remote_name)
    {
      if (strchr (remote_name, '#'))
	{
	  udp_desc = serial_open (remote_name);
	  if (!udp_desc)
	    perror_with_name ("Unable to open UDP port");
	  udp_in_use = 1;
	}
      else
	{
	  /* Save the remote and local names of the TFTP temp file.  If
	     the user didn't specify a local name, assume it's the same
	     as the part of the remote name after the "host:".  */
	  if (tftp_name)
	    xfree (tftp_name);
	  if (tftp_localname)
	    xfree (tftp_localname);
	  if (local_name == NULL)
	    if ((local_name = strchr (remote_name, ':')) != NULL)
	      local_name++;	/* skip over the colon */
	  if (local_name == NULL)
	    local_name = remote_name;	/* local name same as remote name */
	  tftp_name = xstrdup (remote_name);
	  tftp_localname = xstrdup (local_name);
	  tftp_in_use = 1;
	}
    }

  current_ops = ops;
  mips_is_open = 1;

  /* Reset the expected monitor prompt if it's never been set before.  */
  if (mips_monitor_prompt == NULL)
    mips_monitor_prompt = xstrdup (new_monitor_prompt);
  mips_monitor = new_monitor;

  mips_initialize ();

  if (from_tty)
    printf_unfiltered ("Remote MIPS debugging using %s\n", serial_port_name);

  /* Switch to using remote target now.  */
  push_target (ops);

  /* FIXME: Should we call start_remote here?  */

  /* Try to figure out the processor model if possible.  */
  deprecated_mips_set_processor_regs_hack ();

  /* This is really the job of start_remote however, that makes an
     assumption that the target is about to print out a status message
     of some sort.  That doesn't happen here (in fact, it may not be
     possible to get the monitor to send the appropriate packet).  */

  flush_cached_frames ();
  registers_changed ();
  stop_pc = read_pc ();
  print_stack_frame (get_selected_frame (), -1, 1);
  xfree (serial_port_name);
}