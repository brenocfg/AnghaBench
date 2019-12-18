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
 int /*<<< orphan*/  __chk_fail () ; 

char *
__strcat_chk (char *__restrict__ dest, const char *__restrict__ src,
              size_t slen)
{
  char *s1 = dest;
  const char *s2 = src;
  char c;

  do
    {
      if (slen-- == 0)
        __chk_fail ();
      c = *s1++;
    }
  while (c != '\0');

  ++slen;
  s1 -= 2;

  do
    {
      if (slen-- == 0)
        __chk_fail ();
      c = *s2++;
      *++s1 = c;
    }
  while (c != '\0');

  return dest;
}