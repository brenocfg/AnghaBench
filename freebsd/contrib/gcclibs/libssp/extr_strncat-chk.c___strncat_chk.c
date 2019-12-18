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
__strncat_chk (char *__restrict__ dest, const char *__restrict__ src,
               size_t n, size_t slen)
{
  char c;
  char *s = dest;

  do
    {
      if (slen-- == 0)
        __chk_fail ();
      c = *dest++;
    }
  while (c != '\0');

  ++slen;
  dest -= 2;

  if (n >= 4)
    {
      size_t n4 = n >> 2;
      do
        {
          if (slen-- == 0)
            __chk_fail ();
          c = *src++;
          *++dest = c;
          if (c == '\0')
            return s;
          if (slen-- == 0)
            __chk_fail ();
          c = *src++;
          *++dest = c;
          if (c == '\0')
            return s;
          if (slen-- == 0)
            __chk_fail ();
          c = *src++;
          *++dest = c;
          if (c == '\0')
            return s;
          if (slen-- == 0)
            __chk_fail ();
          c = *src++;
          *++dest = c;
          if (c == '\0')
            return s;
          if (slen-- == 0)
            __chk_fail ();
          c = *src++;
          *++dest = c;
          if (c == '\0')
            return s;
        } while (--n4 > 0);
      n &= 3;
    }

  while (n > 0)
    {
      if (slen-- == 0)
        __chk_fail ();
      c = *src++;
      *++dest = c;
      if (c == '\0')
        return s;
      n--;
    }

  if (c != '\0')
    {
      if (slen-- == 0)
        __chk_fail ();
      *++dest = '\0';
    }

  return s;
}