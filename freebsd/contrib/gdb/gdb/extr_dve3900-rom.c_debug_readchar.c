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
 int monitor_readchar () ; 
 int /*<<< orphan*/  puts_debug (char*,char*,char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
debug_readchar (int hex)
{
  char buf[10];
  int c = monitor_readchar ();

  if (remote_debug > 0)
    {
      if (hex)
	sprintf (buf, "[%02x]", c & 0xff);
      else if (c == '\0')
	strcpy (buf, "\\0");
      else
	{
	  buf[0] = c;
	  buf[1] = '\0';
	}
      puts_debug ("Read -->", buf, "<--");
    }
  return c;
}