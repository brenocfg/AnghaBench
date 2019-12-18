#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct objfile {TYPE_4__* obfd; } ;
struct comp_unit {int addr_size; char* dwarf_frame_buffer; int dwarf_frame_size; void* dwarf_frame_section; int /*<<< orphan*/ * cie; scalar_t__ tbase; TYPE_4__* abfd; scalar_t__ dbase; struct objfile* objfile; } ;
struct TYPE_6__ {scalar_t__ vma; } ;
typedef  TYPE_2__ asection ;
struct TYPE_7__ {TYPE_1__* arch_info; } ;
struct TYPE_5__ {int bits_per_address; } ;

/* Variables and functions */
 TYPE_2__* bfd_get_section_by_name (TYPE_4__*,char*) ; 
 void* bfd_get_section_size (void*) ; 
 char* decode_frame_entry (struct comp_unit*,char*,int) ; 
 void* dwarf2_read_section (struct objfile*,void*) ; 
 void* dwarf_eh_frame_section ; 
 void* dwarf_frame_section ; 

void
dwarf2_build_frame_info (struct objfile *objfile)
{
  struct comp_unit unit;
  char *frame_ptr;

  /* Build a minimal decoding of the DWARF2 compilation unit.  */
  unit.abfd = objfile->obfd;
  unit.objfile = objfile;
  unit.addr_size = objfile->obfd->arch_info->bits_per_address / 8;
  unit.dbase = 0;
  unit.tbase = 0;

  /* First add the information from the .eh_frame section.  That way,
     the FDEs from that section are searched last.  */
  if (dwarf_eh_frame_section)
    {
      asection *got, *txt;

      unit.cie = NULL;
      unit.dwarf_frame_buffer = dwarf2_read_section (objfile,
						     dwarf_eh_frame_section);

      unit.dwarf_frame_size
	= bfd_get_section_size (dwarf_eh_frame_section);
      unit.dwarf_frame_section = dwarf_eh_frame_section;

      /* FIXME: kettenis/20030602: This is the DW_EH_PE_datarel base
	 that is used for the i386/amd64 target, which currently is
	 the only target in GCC that supports/uses the
	 DW_EH_PE_datarel encoding.  */
      got = bfd_get_section_by_name (unit.abfd, ".got");
      if (got)
	unit.dbase = got->vma;

      /* GCC emits the DW_EH_PE_textrel encoding type on sh and ia64
         so far.  */
      txt = bfd_get_section_by_name (unit.abfd, ".text");
      if (txt)
	unit.tbase = txt->vma;

      frame_ptr = unit.dwarf_frame_buffer;
      while (frame_ptr < unit.dwarf_frame_buffer + unit.dwarf_frame_size)
	frame_ptr = decode_frame_entry (&unit, frame_ptr, 1);
    }

  if (dwarf_frame_section)
    {
      unit.cie = NULL;
      unit.dwarf_frame_buffer = dwarf2_read_section (objfile,
						     dwarf_frame_section);
      unit.dwarf_frame_size
	= bfd_get_section_size (dwarf_frame_section);
      unit.dwarf_frame_section = dwarf_frame_section;

      frame_ptr = unit.dwarf_frame_buffer;
      while (frame_ptr < unit.dwarf_frame_buffer + unit.dwarf_frame_size)
	frame_ptr = decode_frame_entry (&unit, frame_ptr, 0);
    }
}