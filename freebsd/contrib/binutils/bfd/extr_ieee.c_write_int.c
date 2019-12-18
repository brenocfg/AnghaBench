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
 int /*<<< orphan*/  OUT (int) ; 
 scalar_t__ ieee_number_repeat_start_enum ; 

__attribute__((used)) static void
write_int (int value)
{
  if (value >= 0 && value <= 127)
    {
      OUT (value);
    }
  else
    {
      unsigned int length;

      /* How many significant bytes ?  */
      /* FIXME FOR LONGER INTS.  */
      if (value & 0xff000000)
	length = 4;
      else if (value & 0x00ff0000)
	length = 3;
      else if (value & 0x0000ff00)
	length = 2;
      else
	length = 1;

      OUT ((int) ieee_number_repeat_start_enum + length);
      switch (length)
	{
	case 4:
	  OUT (value >> 24);
	case 3:
	  OUT (value >> 16);
	case 2:
	  OUT (value >> 8);
	case 1:
	  OUT (value);
	}
    }
}