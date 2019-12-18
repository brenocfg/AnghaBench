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
 int PPC_OPCODE_POWER4 ; 

__attribute__((used)) static int
valid_bo (long value, int dialect)
{
  if ((dialect & PPC_OPCODE_POWER4) == 0)
    {
      /* Certain encodings have bits that are required to be zero.
	 These are (z must be zero, y may be anything):
	     001zy
	     011zy
	     1z00y
	     1z01y
	     1z1zz
      */
      switch (value & 0x14)
	{
	default:
	case 0:
	  return 1;
	case 0x4:
	  return (value & 0x2) == 0;
	case 0x10:
	  return (value & 0x8) == 0;
	case 0x14:
	  return value == 0x14;
	}
    }
  else
    {
      /* Certain encodings have bits that are required to be zero.
	 These are (z must be zero, a & t may be anything):
	     0000z
	     0001z
	     0100z
	     0101z
	     001at
	     011at
	     1a00t
	     1a01t
	     1z1zz
      */
      if ((value & 0x14) == 0)
	return (value & 0x1) == 0;
      else if ((value & 0x14) == 0x14)
	return value == 0x14;
      else
	return 1;
    }
}