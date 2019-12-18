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
 int /*<<< orphan*/  RETURN_QUIT ; 
 int /*<<< orphan*/  close_ports () ; 
 int interrupt_count ; 
 int /*<<< orphan*/  mips_desc ; 
 scalar_t__ mips_is_open ; 
 scalar_t__ mips_wait_flag ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 scalar_t__ query (char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  serial_send_break (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  serial_write (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sleep (int) ; 
 int /*<<< orphan*/  target_mourn_inferior () ; 
 int /*<<< orphan*/  target_terminal_inferior () ; 
 int /*<<< orphan*/  target_terminal_ours () ; 
 int /*<<< orphan*/  throw_exception (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
mips_kill (void)
{
  if (!mips_wait_flag)
    return;

  interrupt_count++;

  if (interrupt_count >= 2)
    {
      interrupt_count = 0;

      target_terminal_ours ();

      if (query ("Interrupted while waiting for the program.\n\
Give up (and stop debugging it)? "))
	{
	  /* Clean up in such a way that mips_close won't try to talk to the
	     board (it almost surely won't work since we weren't able to talk to
	     it).  */
	  mips_wait_flag = 0;
	  close_ports ();

	  printf_unfiltered ("Ending remote MIPS debugging.\n");
	  target_mourn_inferior ();

	  throw_exception (RETURN_QUIT);
	}

      target_terminal_inferior ();
    }

  if (remote_debug > 0)
    printf_unfiltered ("Sending break\n");

  serial_send_break (mips_desc);

#if 0
  if (mips_is_open)
    {
      char cc;

      /* Send a ^C.  */
      cc = '\003';
      serial_write (mips_desc, &cc, 1);
      sleep (1);
      target_mourn_inferior ();
    }
#endif
}