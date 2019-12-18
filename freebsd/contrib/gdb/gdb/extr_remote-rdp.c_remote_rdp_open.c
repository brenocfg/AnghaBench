#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  (* init ) (TYPE_1__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  RDI_ConfigCPU ; 
 int /*<<< orphan*/  RDI_MatchAny ; 
 int /*<<< orphan*/  RDP_INFO ; 
 int /*<<< orphan*/  RDP_INFO_ICEBREAKER ; 
 int /*<<< orphan*/  RDP_SELECT_CONFIG ; 
 int baud_rate ; 
 TYPE_1__* callback ; 
 int /*<<< orphan*/  error_no_arg (char*) ; 
 int /*<<< orphan*/  flush_cached_frames () ; 
 int /*<<< orphan*/  get_selected_frame () ; 
 int /*<<< orphan*/  io ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  print_stack_frame (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int) ; 
 int /*<<< orphan*/  push_target (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rdp_catch_vectors () ; 
 int /*<<< orphan*/  rdp_info () ; 
 int /*<<< orphan*/  rdp_init (int,int) ; 
 int /*<<< orphan*/  read_pc () ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  remote_rdp_ops ; 
 int /*<<< orphan*/  send_rdp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stop_pc ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  target_preopen (int) ; 

__attribute__((used)) static void
remote_rdp_open (char *args, int from_tty)
{
  int not_icebreaker;

  if (!args)
    error_no_arg ("serial port device name");

  baud_rate = 9600;

  target_preopen (from_tty);

  io = serial_open (args);

  if (!io)
    perror_with_name (args);

  serial_raw (io);

  rdp_init (1, from_tty);


  if (from_tty)
    {
      printf_unfiltered ("Remote RDP debugging using %s at %d baud\n", args, baud_rate);
    }

  rdp_info ();

  /* Need to set up the vector interception state */
  rdp_catch_vectors ();

  /*
     ** If it's an EmbeddedICE, we need to set the processor config.
     ** Assume we can always have ARM7TDI...
   */
  send_rdp ("bw-SB", RDP_INFO, RDP_INFO_ICEBREAKER, &not_icebreaker);
  if (!not_icebreaker)
    {
      const char *CPU = "ARM7TDI";
      int ICEversion;
      int len = strlen (CPU);

      send_rdp ("bbbbw-p-SWZ",
		RDP_SELECT_CONFIG,
		RDI_ConfigCPU,	/* Aspect: set the CPU */
		len,		/* The number of bytes in the name */
		RDI_MatchAny,	/* We'll take whatever we get */
		0,		/* We'll take whatever version's there */
		CPU, len,
		&ICEversion);
    }

  /* command line initialised on 'run' */

  push_target (&remote_rdp_ops);

  callback->init (callback);
  flush_cached_frames ();
  registers_changed ();
  stop_pc = read_pc ();
  print_stack_frame (get_selected_frame (), -1, 1);
}