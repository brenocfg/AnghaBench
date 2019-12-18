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
 char OCD_AYT ; 
 int ocd_interrupt_flag ; 
 int /*<<< orphan*/  ocd_interrupt_twice ; 
 int /*<<< orphan*/  ocd_put_packet (char*,int) ; 
 int /*<<< orphan*/  ocd_stop () ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  signal (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ocd_interrupt (int signo)
{
  /* If this doesn't work, try more severe steps.  */
  signal (signo, ocd_interrupt_twice);

  if (remote_debug)
    printf_unfiltered ("ocd_interrupt called\n");

  {
    char buf[1];

    ocd_stop ();
    buf[0] = OCD_AYT;
    ocd_put_packet (buf, 1);
    ocd_interrupt_flag = 1;
  }
}