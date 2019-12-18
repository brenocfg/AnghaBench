#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ui_file {int dummy; } ;
struct TYPE_2__ {char* prompt; } ;

/* Variables and functions */
 TYPE_1__* current_monitor ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  fputs_unfiltered (char*,struct ui_file*) ; 
 int /*<<< orphan*/ * monitor_desc ; 
 int monitor_expect_prompt (char*,int) ; 
 int /*<<< orphan*/  monitor_printf (char*,char*) ; 

__attribute__((used)) static void
monitor_rcmd (char *command,
	      struct ui_file *outbuf)
{
  char *p;
  int resp_len;
  char buf[1000];

  if (monitor_desc == NULL)
    error ("monitor target not open.");

  p = current_monitor->prompt;

  /* Send the command.  Note that if no args were supplied, then we're
     just sending the monitor a newline, which is sometimes useful.  */

  monitor_printf ("%s\r", (command ? command : ""));

  resp_len = monitor_expect_prompt (buf, sizeof buf);

  fputs_unfiltered (buf, outbuf);	/* Output the response */
}