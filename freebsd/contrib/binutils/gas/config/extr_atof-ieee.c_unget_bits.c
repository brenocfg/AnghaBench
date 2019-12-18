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
 int LITTLENUM_NUMBER_OF_BITS ; 
 int bits_left_in_littlenum ; 
 int /*<<< orphan*/  littlenum_pointer ; 
 int /*<<< orphan*/  littlenums_left ; 

__attribute__((used)) static void
unget_bits (int num)
{
  if (!littlenums_left)
    {
      ++littlenum_pointer;
      ++littlenums_left;
      bits_left_in_littlenum = num;
    }
  else if (bits_left_in_littlenum + num > LITTLENUM_NUMBER_OF_BITS)
    {
      bits_left_in_littlenum =
	num - (LITTLENUM_NUMBER_OF_BITS - bits_left_in_littlenum);
      ++littlenum_pointer;
      ++littlenums_left;
    }
  else
    bits_left_in_littlenum += num;
}