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
typedef  int /*<<< orphan*/  common_header_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  next_byte (int /*<<< orphan*/ *) ; 
 int this_byte (int /*<<< orphan*/ *) ; 
 int this_byte_and_next (int /*<<< orphan*/ *) ; 

__attribute__((used)) static bfd_boolean
parse_int (common_header_type *ieee, bfd_vma *value_ptr)
{
  int value = this_byte (ieee);
  int result;

  if (value >= 0 && value <= 127)
    {
      *value_ptr = value;
      next_byte (ieee);
      return TRUE;
    }
  else if (value >= 0x80 && value <= 0x88)
    {
      unsigned int count = value & 0xf;

      result = 0;
      next_byte (ieee);
      while (count)
	{
	  result = (result << 8) | this_byte_and_next (ieee);
	  count--;
	}
      *value_ptr = result;
      return TRUE;
    }
  return FALSE;
}