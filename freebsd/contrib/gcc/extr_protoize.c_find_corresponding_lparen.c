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

__attribute__((used)) static const char *
find_corresponding_lparen (const char *p)
{
  const char *q;
  int paren_depth;

  for (paren_depth = 1, q = p-1; paren_depth; q--)
    {
      switch (*q)
	{
	case ')':
	  paren_depth++;
	  break;
	case '(':
	  paren_depth--;
	  break;
	}
    }
  return ++q;
}