#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_7__ {int sec_info_type; } ;
typedef  TYPE_1__ asection ;
struct TYPE_8__ {int /*<<< orphan*/  sec_info; } ;

/* Variables and functions */
#define  ELF_INFO_TYPE_EH_FRAME 129 
#define  ELF_INFO_TYPE_STABS 128 
 int /*<<< orphan*/  _bfd_elf_eh_frame_section_offset (int /*<<< orphan*/ *,struct bfd_link_info*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _bfd_stab_section_offset (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* elf_section_data (TYPE_1__*) ; 

bfd_vma
_bfd_elf_section_offset (bfd *abfd,
			 struct bfd_link_info *info,
			 asection *sec,
			 bfd_vma offset)
{
  switch (sec->sec_info_type)
    {
    case ELF_INFO_TYPE_STABS:
      return _bfd_stab_section_offset (sec, elf_section_data (sec)->sec_info,
				       offset);
    case ELF_INFO_TYPE_EH_FRAME:
      return _bfd_elf_eh_frame_section_offset (abfd, info, sec, offset);
    default:
      return offset;
    }
}