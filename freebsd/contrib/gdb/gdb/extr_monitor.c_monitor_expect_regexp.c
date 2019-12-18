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
struct re_pattern_buffer {int dummy; } ;

/* Variables and functions */
 int TARGET_BUF_SIZE ; 
 char* alloca (int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  monitor_debug (char*) ; 
 int re_search (struct re_pattern_buffer*,char*,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  readchar (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  timeout ; 

__attribute__((used)) static int
monitor_expect_regexp (struct re_pattern_buffer *pat, char *buf, int buflen)
{
  char *mybuf;
  char *p;
  monitor_debug ("MON Expecting regexp\n");
  if (buf)
    mybuf = buf;
  else
    {
      mybuf = alloca (TARGET_BUF_SIZE);
      buflen = TARGET_BUF_SIZE;
    }

  p = mybuf;
  while (1)
    {
      int retval;

      if (p - mybuf >= buflen)
	{			/* Buffer about to overflow */

/* On overflow, we copy the upper half of the buffer to the lower half.  Not
   great, but it usually works... */

	  memcpy (mybuf, mybuf + buflen / 2, buflen / 2);
	  p = mybuf + buflen / 2;
	}

      *p++ = readchar (timeout);

      retval = re_search (pat, mybuf, p - mybuf, 0, p - mybuf, NULL);
      if (retval >= 0)
	return 1;
    }
}