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
 char* _ (char*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned long,unsigned long,unsigned long) ; 

const char *
cgen_validate_unsigned_integer (unsigned long value,
				unsigned long min,
				unsigned long max)
{
  if (value < min || value > max)
    {
      static char buf[100];

      /* xgettext:c-format */
      sprintf (buf, _("operand out of range (%lu not between %lu and %lu)"),
	       value, min, max);
      return buf;
    }

  return NULL;
}