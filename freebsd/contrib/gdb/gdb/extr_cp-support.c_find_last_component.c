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
 int strlen (char const*) ; 

__attribute__((used)) static const char *
find_last_component (const char *name)
{
  const char *p;
  int depth;

  /* Functions can have local classes, so we need to find the
     beginning of the last argument list, not the end of the first
     one.  */
  p = name + strlen (name) - 1;
  while (p > name && *p != ')')
    p--;

  if (p == name)
    return NULL;

  /* P now points at the `)' at the end of the argument list.  Walk
     back to the beginning.  */
  p--;
  depth = 1;
  while (p > name && depth > 0)
    {
      if (*p == '<' || *p == '(')
	depth--;
      else if (*p == '>' || *p == ')')
	depth++;
      p--;
    }

  if (p == name)
    return NULL;

  while (p > name && *p != ':')
    p--;

  if (p == name || p == name + 1 || p[-1] != ':')
    return NULL;

  return p - 1;
}