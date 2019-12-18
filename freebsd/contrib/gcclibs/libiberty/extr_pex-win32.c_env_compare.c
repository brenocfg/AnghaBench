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
 scalar_t__ tolower (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
env_compare (const void *a_ptr, const void *b_ptr)
{
  const char *a;
  const char *b;
  unsigned char c1;
  unsigned char c2;

  a = *(const char **) a_ptr;
  b = *(const char **) b_ptr;

  /* a and b will be of the form: VAR=VALUE
     We compare only the variable name part here using a case-insensitive
     comparison algorithm.  It might appear that in fact strcasecmp () can
     take the place of this whole function, and indeed it could, save for
     the fact that it would fail in cases such as comparing A1=foo and
     A=bar (because 1 is less than = in the ASCII character set).
     (Environment variables containing no numbers would work in such a
     scenario.)  */

  do
    {
      c1 = (unsigned char) tolower (*a++);
      c2 = (unsigned char) tolower (*b++);

      if (c1 == '=')
        c1 = '\0';

      if (c2 == '=')
        c2 = '\0';
    }
  while (c1 == c2 && c1 != '\0');

  return c1 - c2;
}