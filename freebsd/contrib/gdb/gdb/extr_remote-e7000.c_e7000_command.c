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
 int ctrl_c ; 
 int /*<<< orphan*/  e7000_desc ; 
 scalar_t__ echo ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  expect_full_prompt () ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int /*<<< orphan*/  registers_changed () ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static void
e7000_command (char *args, int fromtty)
{
  /* FIXME: arbitrary limit on length of args.  */
  char buf[200];

  echo = 0;

  if (!e7000_desc)
    error ("e7000 target not open.");
  if (!args)
    {
      puts_e7000debug ("\r");
    }
  else
    {
      sprintf (buf, "%s\r", args);
      puts_e7000debug (buf);
    }

  echo++;
  ctrl_c = 2;
  expect_full_prompt ();
  echo--;
  ctrl_c = 0;
  printf_unfiltered ("\n");

  /* Who knows what the command did... */
  registers_changed ();
}