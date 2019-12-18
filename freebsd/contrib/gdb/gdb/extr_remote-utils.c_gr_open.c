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
struct gr_settings {TYPE_1__* ops; int /*<<< orphan*/ * clear_all_breakpoints; } ;
struct TYPE_3__ {int /*<<< orphan*/  to_shortname; } ;

/* Variables and functions */
 int baud_rate ; 
 int /*<<< orphan*/  gr_checkin () ; 
 int /*<<< orphan*/  gr_clear_all_breakpoints () ; 
 int /*<<< orphan*/  gr_close (int /*<<< orphan*/ ) ; 
 struct gr_settings* gr_settings ; 
 int /*<<< orphan*/  perror_with_name (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int /*<<< orphan*/  push_target (TYPE_1__*) ; 
 int /*<<< orphan*/ * remove_breakpoints ; 
 int /*<<< orphan*/  serial_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_flush_input (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  serial_open (char*) ; 
 int /*<<< orphan*/  serial_raw (int /*<<< orphan*/ *) ; 
 scalar_t__ serial_setbaudrate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * sr_get_desc () ; 
 char* sr_get_device () ; 
 scalar_t__ sr_get_retries () ; 
 int /*<<< orphan*/  sr_scan_args (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  sr_set_desc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sr_set_retries (int) ; 
 int /*<<< orphan*/  target_preopen (int) ; 
 int /*<<< orphan*/  unpush_target (TYPE_1__*) ; 
 int /*<<< orphan*/  usage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void
gr_open (char *args, int from_tty, struct gr_settings *gr)
{
  target_preopen (from_tty);
  sr_scan_args (gr->ops->to_shortname, args);
  unpush_target (gr->ops);

  gr_settings = gr;

  if (sr_get_desc () != NULL)
    gr_close (0);

  /* If no args are specified, then we use the device specified by a
     previous command or "set remotedevice".  But if there is no
     device, better stop now, not dump core.  */

  if (sr_get_device () == NULL)
    usage (gr->ops->to_shortname, NULL);

  sr_set_desc (serial_open (sr_get_device ()));
  if (!sr_get_desc ())
    perror_with_name ((char *) sr_get_device ());

  if (baud_rate != -1)
    {
      if (serial_setbaudrate (sr_get_desc (), baud_rate) != 0)
	{
	  serial_close (sr_get_desc ());
	  perror_with_name (sr_get_device ());
	}
    }

  serial_raw (sr_get_desc ());

  /* If there is something sitting in the buffer we might take it as a
     response to a command, which would be bad.  */
  serial_flush_input (sr_get_desc ());

  /* default retries */
  if (sr_get_retries () == 0)
    sr_set_retries (1);

  /* default clear breakpoint function */
  if (gr_settings->clear_all_breakpoints == NULL)
    gr_settings->clear_all_breakpoints = remove_breakpoints;

  if (from_tty)
    {
      printf_filtered ("Remote debugging using `%s'", sr_get_device ());
      if (baud_rate != -1)
	printf_filtered (" at baud rate of %d",
			 baud_rate);
      printf_filtered ("\n");
    }

  push_target (gr->ops);
  gr_checkin ();
  gr_clear_all_breakpoints ();
  return;
}