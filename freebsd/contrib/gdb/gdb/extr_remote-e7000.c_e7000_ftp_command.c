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
 char* dir ; 
 int /*<<< orphan*/  expect (char*) ; 
 char* machine ; 
 char* passwd ; 
 int /*<<< orphan*/  puts_e7000debug (char*) ; 
 int remote_timeout ; 
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 
 int timeout ; 
 char* user ; 
 int /*<<< orphan*/  write_e7000 (char*) ; 

__attribute__((used)) static void
e7000_ftp_command (char *args, int from_tty)
{
  /* FIXME: arbitrary limit on machine names and such.  */
  char buf[200];

  int oldtimeout = timeout;
  timeout = remote_timeout;

  sprintf (buf, "ftp %s\r", machine);
  puts_e7000debug (buf);
  expect (" Username : ");
  sprintf (buf, "%s\r", user);
  puts_e7000debug (buf);
  expect (" Password : ");
  write_e7000 (passwd);
  write_e7000 ("\r");
  expect ("success\r");
  expect ("FTP>");
  sprintf (buf, "cd %s\r", dir);
  puts_e7000debug (buf);
  expect ("FTP>");
  sprintf (buf, "ll 0;s:%s\r", args);
  puts_e7000debug (buf);
  expect ("FTP>");
  puts_e7000debug ("bye\r");
  expect (":");
  timeout = oldtimeout;
}