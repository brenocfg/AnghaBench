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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ ieee_number_repeat_start_enum ; 
 int /*<<< orphan*/  ieee_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
ieee_write_int (bfd *abfd, bfd_vma value)
{
  if (value <= 127)
    {
      if (! ieee_write_byte (abfd, (bfd_byte) value))
	return FALSE;
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

      if (! ieee_write_byte (abfd,
			     (bfd_byte) ((int) ieee_number_repeat_start_enum
					 + length)))
	return FALSE;
      switch (length)
	{
	case 4:
	  if (! ieee_write_byte (abfd, (bfd_byte) (value >> 24)))
	    return FALSE;
	  /* Fall through.  */
	case 3:
	  if (! ieee_write_byte (abfd, (bfd_byte) (value >> 16)))
	    return FALSE;
	  /* Fall through.  */
	case 2:
	  if (! ieee_write_byte (abfd, (bfd_byte) (value >> 8)))
	    return FALSE;
	  /* Fall through.  */
	case 1:
	  if (! ieee_write_byte (abfd, (bfd_byte) (value)))
	    return FALSE;
	}
    }

  return TRUE;
}