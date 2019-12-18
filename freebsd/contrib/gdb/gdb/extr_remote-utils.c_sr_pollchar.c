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
 int SERIAL_TIMEOUT ; 
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 int serial_readchar (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sr_get_debug () ; 
 int /*<<< orphan*/  sr_get_desc () ; 

int
sr_pollchar (void)
{
  int buf;

  buf = serial_readchar (sr_get_desc (), 0);
  if (buf == SERIAL_TIMEOUT)
    buf = 0;
  if (sr_get_debug () > 0)
    {
      if (buf)
	printf_unfiltered ("%c", buf);
      else
	printf_unfiltered ("<empty character poll>");
    }

  return buf & 0x7f;
}