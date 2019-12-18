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
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int ethernet ; 
 int monitor_expect (char*,char*,int) ; 
 int /*<<< orphan*/  monitor_expect_prompt (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  monitor_open (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  monitor_printf (char*) ; 
 int /*<<< orphan*/  monitor_printf_noecho (char*) ; 
 int /*<<< orphan*/  r3900_cmds ; 
 char** r3900_inits ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 

__attribute__((used)) static void
r3900_open (char *args, int from_tty)
{
  char buf[64];
  int i;

  monitor_open (args, &r3900_cmds, from_tty);

  /* We have to handle sending the init strings ourselves, because
     the first two strings we send (carriage returns) may not be echoed
     by the monitor, but the rest will be.  */
  monitor_printf_noecho ("\r\r");
  for (i = 0; r3900_inits[i] != NULL; i++)
    {
      monitor_printf (r3900_inits[i]);
      monitor_expect_prompt (NULL, 0);
    }

  /* Attempt to determine whether the console device is ethernet or serial.
     This will tell us which kind of load to use (S-records over a serial
     link, or the Densan fast binary multi-section format over the net).  */

  ethernet = 0;
  monitor_printf ("v\r");
  if (monitor_expect ("console device :", NULL, 0) != -1)
    if (monitor_expect ("\n", buf, sizeof (buf)) != -1)
      if (strstr (buf, "ethernet") != NULL)
	ethernet = 1;
  monitor_expect_prompt (NULL, 0);
}