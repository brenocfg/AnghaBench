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
typedef  int ptrdiff_t ;

/* Variables and functions */

__attribute__((used)) static char const *
scan_char_literal (char const *lit, char *valptr)
{
  register char const *p = lit;
  char value;
  ptrdiff_t digits;
  char c = *p++;

  switch (c)
    {
      case 0:
      case '\'':
	return 0;

      case '\\':
	value = 0;
	while ((c = *p++) != '\'')
	  {
	    unsigned int digit = c - '0';
	    if (8 <= digit)
	      return 0;
	    value = 8 * value + digit;
	  }
	digits = p - lit - 2;
	if (! (1 <= digits && digits <= 3))
	  return 0;
	break;

      default:
	value = c;
	if (*p++ != '\'')
	  return 0;
	break;
    }

  *valptr = value;
  return p;
}