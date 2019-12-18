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
 scalar_t__ isspace (char const) ; 

unsigned int
msymbol_hash_iw (const char *string)
{
  unsigned int hash = 0;
  while (*string && *string != '(')
    {
      while (isspace (*string))
	++string;
      if (*string && *string != '(')
	{
	  hash = hash * 67 + *string - 113;
	  ++string;
	}
    }
  return hash;
}