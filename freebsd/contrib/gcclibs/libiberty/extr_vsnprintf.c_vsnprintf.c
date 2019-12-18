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
typedef  int /*<<< orphan*/  va_list ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int strlen (char*) ; 
 int vasprintf (char**,char const*,int /*<<< orphan*/ ) ; 

int
vsnprintf (char *s, size_t n, const char *format, va_list ap)
{
  char *buf = 0;
  int result = vasprintf (&buf, format, ap);

  if (!buf)
    return -1;
  if (result < 0)
    {
      free (buf);
      return -1;
    }

  result = strlen (buf);
  if (n > 0)
    {
      if ((long) n > result)
	memcpy (s, buf, result+1);
      else
        {
	  memcpy (s, buf, n-1);
	  s[n - 1] = 0;
	}
    }
  free (buf);
  return result;
}