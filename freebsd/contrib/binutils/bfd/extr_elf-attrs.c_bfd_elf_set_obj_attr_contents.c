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
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int OBJ_ATTR_FIRST ; 
 int OBJ_ATTR_LAST ; 
 int /*<<< orphan*/  abort () ; 
 int vendor_obj_attr_size (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vendor_set_obj_attr_contents (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int) ; 

void
bfd_elf_set_obj_attr_contents (bfd *abfd, bfd_byte *contents, bfd_vma size)
{
  bfd_byte *p;
  int vendor;
  bfd_vma my_size;

  p = contents;
  *(p++) = 'A';
  my_size = 1;
  for (vendor = OBJ_ATTR_FIRST; vendor <= OBJ_ATTR_LAST; vendor++)
    {
      bfd_vma vendor_size = vendor_obj_attr_size (abfd, vendor);
      if (vendor_size)
	vendor_set_obj_attr_contents (abfd, p, vendor_size, vendor);
      p += vendor_size;
      my_size += vendor_size;
    }

  if (size != my_size)
    abort ();
}