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
struct real_format {int b; double p; int log2_b; } ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
 struct real_format* REAL_MODE_FORMAT (int) ; 

int
significand_size (enum machine_mode mode)
{
  const struct real_format *fmt;

  fmt = REAL_MODE_FORMAT (mode);
  if (fmt == NULL)
    return 0;

  if (fmt->b == 10)
    {
      /* Return the size in bits of the largest binary value that can be
	 held by the decimal coefficient for this mode.  This is one more
	 than the number of bits required to hold the largest coefficient
	 of this mode.  */
      double log2_10 = 3.3219281;
      return fmt->p * log2_10;
    }
  return fmt->p * fmt->log2_b;
}