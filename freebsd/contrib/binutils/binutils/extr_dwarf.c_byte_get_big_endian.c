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
typedef  unsigned char dwarf_vma ;

/* Variables and functions */
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  error (int /*<<< orphan*/ ,int) ; 

dwarf_vma
byte_get_big_endian (unsigned char *field, int size)
{
  switch (size)
    {
    case 1:
      return *field;

    case 2:
      return ((unsigned int) (field[1])) | (((int) (field[0])) << 8);

    case 4:
      return ((unsigned long) (field[3]))
	|   (((unsigned long) (field[2])) << 8)
	|   (((unsigned long) (field[1])) << 16)
	|   (((unsigned long) (field[0])) << 24);

    case 8:
      if (sizeof (dwarf_vma) == 8)
	return ((dwarf_vma) (field[7]))
	  |   (((dwarf_vma) (field[6])) << 8)
	  |   (((dwarf_vma) (field[5])) << 16)
	  |   (((dwarf_vma) (field[4])) << 24)
	  |   (((dwarf_vma) (field[3])) << 32)
	  |   (((dwarf_vma) (field[2])) << 40)
	  |   (((dwarf_vma) (field[1])) << 48)
	  |   (((dwarf_vma) (field[0])) << 56);
      else if (sizeof (dwarf_vma) == 4)
	{
	  /* Although we are extracing data from an 8 byte wide field,
	     we are returning only 4 bytes of data.  */
	  field += 4;
	  return ((unsigned long) (field[3]))
	    |   (((unsigned long) (field[2])) << 8)
	    |   (((unsigned long) (field[1])) << 16)
	    |   (((unsigned long) (field[0])) << 24);
	}

    default:
      error (_("Unhandled data length: %d\n"), size);
      abort ();
    }
}