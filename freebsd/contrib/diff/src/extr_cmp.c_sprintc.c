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
 int /*<<< orphan*/  isprint (unsigned char) ; 

__attribute__((used)) static void
sprintc (char *buf, unsigned char c)
{
  if (! isprint (c))
    {
      if (c >= 128)
	{
	  *buf++ = 'M';
	  *buf++ = '-';
	  c -= 128;
	}
      if (c < 32)
	{
	  *buf++ = '^';
	  c += 64;
	}
      else if (c == 127)
	{
	  *buf++ = '^';
	  c = '?';
	}
    }

  *buf++ = c;
  *buf = 0;
}