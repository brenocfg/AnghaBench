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
 int /*<<< orphan*/  error (char*) ; 
 int sscanf (char*,char*,char*,...) ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int using_pc ; 
 int using_tcp ; 
 int using_tcp_remote ; 

__attribute__((used)) static int
e7000_parse_device (char *args, char *dev_name, int baudrate)
{
  char junk[128];
  int n = 0;
  if (args && strcasecmp (args, "pc") == 0)
    {
      strcpy (dev_name, args);
      using_pc = 1;
    }
  else
    {
      /* FIXME! temp hack to allow use with port master -
         target tcp_remote <device> */
      if (args && strncmp (args, "tcp", 10) == 0)
	{
	  char com_type[128];
	  n = sscanf (args, " %s %s %d %s", com_type, dev_name, &baudrate, junk);
	  using_tcp_remote = 1;
	  n--;
	}
      else if (args)
	{
	  n = sscanf (args, " %s %d %s", dev_name, &baudrate, junk);
	}

      if (n != 1 && n != 2)
	{
	  error ("Bad arguments.  Usage:\ttarget e7000 <device> <speed>\n\
or \t\ttarget e7000 <host>[:<port>]\n\
or \t\ttarget e7000 tcp_remote <host>[:<port>]\n\
or \t\ttarget e7000 pc\n");
	}

#if !defined(__GO32__) && !defined(_WIN32) && !defined(__CYGWIN__)
      /* FIXME!  test for ':' is ambiguous */
      if (n == 1 && strchr (dev_name, ':') == 0)
	{
	  /* Default to normal telnet port */
	  /* serial_open will use this to determine tcp communication */
	  strcat (dev_name, ":23");
	}
#endif
      if (!using_tcp_remote && strchr (dev_name, ':'))
	using_tcp = 1;
    }

  return n;
}