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
 scalar_t__ ISDIGIT (unsigned char) ; 

__attribute__((used)) static int
consume_count (const char **type)
{
  int count = 0;

  if (! ISDIGIT ((unsigned char)**type))
    return -1;

  while (ISDIGIT ((unsigned char)**type))
    {
      count *= 10;

      /* Check for overflow.
	 We assume that count is represented using two's-complement;
	 no power of two is divisible by ten, so if an overflow occurs
	 when multiplying by ten, the result will not be a multiple of
	 ten.  */
      if ((count % 10) != 0)
	{
	  while (ISDIGIT ((unsigned char) **type))
	    (*type)++;
	  return -1;
	}

      count += **type - '0';
      (*type)++;
    }

  if (count < 0)
    count = -1;

  return (count);
}