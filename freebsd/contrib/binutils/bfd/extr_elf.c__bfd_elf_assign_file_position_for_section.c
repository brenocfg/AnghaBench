#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  void* file_ptr ;
typedef  scalar_t__ bfd_boolean ;
struct TYPE_5__ {unsigned int sh_addralign; scalar_t__ sh_type; scalar_t__ sh_size; TYPE_1__* bfd_section; void* sh_offset; } ;
struct TYPE_4__ {void* filepos; } ;
typedef  TYPE_2__ Elf_Internal_Shdr ;

/* Variables and functions */
 void* BFD_ALIGN (void*,unsigned int) ; 
 scalar_t__ SHT_NOBITS ; 

file_ptr
_bfd_elf_assign_file_position_for_section (Elf_Internal_Shdr *i_shdrp,
					   file_ptr offset,
					   bfd_boolean align)
{
  if (align)
    {
      unsigned int al;

      al = i_shdrp->sh_addralign;
      if (al > 1)
	offset = BFD_ALIGN (offset, al);
    }
  i_shdrp->sh_offset = offset;
  if (i_shdrp->bfd_section != NULL)
    i_shdrp->bfd_section->filepos = offset;
  if (i_shdrp->sh_type != SHT_NOBITS)
    offset += i_shdrp->sh_size;
  return offset;
}