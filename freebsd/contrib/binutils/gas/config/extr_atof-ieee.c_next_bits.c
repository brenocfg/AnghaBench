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
 int* littlenum_pointer ; 
 scalar_t__ littlenums_left ; 
 int* mask ; 

__attribute__((used)) static int
next_bits (int number_of_bits)
{
  int return_value;

  if (!littlenums_left)
    return 0;

  if (number_of_bits >= bits_left_in_littlenum)
    {
      return_value = mask[bits_left_in_littlenum] & *littlenum_pointer;
      number_of_bits -= bits_left_in_littlenum;
      return_value <<= number_of_bits;

      if (--littlenums_left)
	{
	  bits_left_in_littlenum = LITTLENUM_NUMBER_OF_BITS - number_of_bits;
	  --littlenum_pointer;
	  return_value |=
	    (*littlenum_pointer >> bits_left_in_littlenum)
	    & mask[number_of_bits];
	}
    }
  else
    {
      bits_left_in_littlenum -= number_of_bits;
      return_value =
	mask[number_of_bits] & (*littlenum_pointer >> bits_left_in_littlenum);
    }
  return return_value;
}