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
 scalar_t__ ISSPACE (unsigned char) ; 

__attribute__((used)) static int
prepend_args (char const *options, char *buf, char **argv)
{
  char const *o = options;
  char *b = buf;
  int n = 0;

  for (;;)
    {
      while (ISSPACE ((unsigned char) *o))
	o++;
      if (!*o)
	return n;
      if (argv)
	argv[n] = b;
      n++;

      do
	if ((*b++ = *o++) == '\\' && *o)
	  b[-1] = *o++;
      while (*o && ! ISSPACE ((unsigned char) *o));

      *b++ = '\0';
    }
}