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
 int /*<<< orphan*/  monitor_write (unsigned char*,int) ; 
 int /*<<< orphan*/  puts_debug (char*,char*,char*) ; 
 scalar_t__ remote_debug ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static void
debug_write (unsigned char *buf, int buflen)
{
  char s[10];

  monitor_write (buf, buflen);

  if (remote_debug > 0)
    {
      while (buflen-- > 0)
	{
	  sprintf (s, "[%02x]", *buf & 0xff);
	  puts_debug ("Sent -->", s, "<--");
	  buf++;
	}
    }
}