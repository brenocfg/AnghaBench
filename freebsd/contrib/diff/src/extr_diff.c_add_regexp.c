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
struct regexp_list {char* regexps; size_t len; int multiple_regexps; size_t size; int /*<<< orphan*/  buf; } ;

/* Variables and functions */
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,char const*,char const*) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,size_t) ; 
 char* re_compile_pattern (char const*,size_t,int /*<<< orphan*/ ) ; 
 size_t strlen (char const*) ; 
 char* xrealloc (char*,size_t) ; 

__attribute__((used)) static void
add_regexp (struct regexp_list *reglist, char const *pattern)
{
  size_t patlen = strlen (pattern);
  char const *m = re_compile_pattern (pattern, patlen, reglist->buf);

  if (m != 0)
    error (0, 0, "%s: %s", pattern, m);
  else
    {
      char *regexps = reglist->regexps;
      size_t len = reglist->len;
      bool multiple_regexps = reglist->multiple_regexps = regexps != 0;
      size_t newlen = reglist->len = len + 2 * multiple_regexps + patlen;
      size_t size = reglist->size;

      if (size <= newlen)
	{
	  if (!size)
	    size = 1;

	  do size *= 2;
	  while (size <= newlen);

	  reglist->size = size;
	  reglist->regexps = regexps = xrealloc (regexps, size);
	}
      if (multiple_regexps)
	{
	  regexps[len++] = '\\';
	  regexps[len++] = '|';
	}
      memcpy (regexps + len, pattern, patlen + 1);
    }
}