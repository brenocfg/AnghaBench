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
byte_get_little_endian (unsigned char *field, int size)
{
  switch (size)
    {
    case 1:
      return *field;

    case 2:
      return  ((unsigned int) (field[0]))
	|    (((unsigned int) (field[1])) << 8);

    case 4:
      return  ((unsigned long) (field[0]))
	|    (((unsigned long) (field[1])) << 8)
	|    (((unsigned long) (field[2])) << 16)
	|    (((unsigned long) (field[3])) << 24);

    case 8:
      if (sizeof (dwarf_vma) == 8)
	return  ((dwarf_vma) (field[0]))
	  |    (((dwarf_vma) (field[1])) << 8)
	  |    (((dwarf_vma) (field[2])) << 16)
	  |    (((dwarf_vma) (field[3])) << 24)
	  |    (((dwarf_vma) (field[4])) << 32)
	  |    (((dwarf_vma) (field[5])) << 40)
	  |    (((dwarf_vma) (field[6])) << 48)
	  |    (((dwarf_vma) (field[7])) << 56);
      else if (sizeof (dwarf_vma) == 4)
	/* We want to extract data from an 8 byte wide field and
	   place it into a 4 byte wide field.  Since this is a little
	   endian source we can just use the 4 byte extraction code.  */
	return  ((unsigned long) (field[0]))
	  |    (((unsigned long) (field[1])) << 8)
	  |    (((unsigned long) (field[2])) << 16)
	  |    (((unsigned long) (field[3])) << 24);

    default:
      error (_("Unhandled data length: %d\n"), size);
      abort ();
    }
}