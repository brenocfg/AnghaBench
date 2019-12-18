#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  value; TYPE_5__* section; } ;
struct TYPE_9__ {scalar_t__ link; } ;
struct TYPE_11__ {TYPE_2__ def; TYPE_1__ i; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_3__ u; } ;
struct elf_link_hash_entry {TYPE_4__ root; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {int flags; scalar_t__ sec_info_type; } ;
typedef  TYPE_5__ asection ;
struct TYPE_14__ {int /*<<< orphan*/  sec_info; } ;

/* Variables and functions */
 scalar_t__ ELF_INFO_TYPE_MERGE ; 
 int SEC_MERGE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _bfd_merged_section_offset (int /*<<< orphan*/ *,TYPE_5__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 TYPE_6__* elf_section_data (TYPE_5__*) ; 

bfd_boolean
_bfd_elf_link_sec_merge_syms (struct elf_link_hash_entry *h, void *data)
{
  asection *sec;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if ((h->root.type == bfd_link_hash_defined
       || h->root.type == bfd_link_hash_defweak)
      && ((sec = h->root.u.def.section)->flags & SEC_MERGE)
      && sec->sec_info_type == ELF_INFO_TYPE_MERGE)
    {
      bfd *output_bfd = data;

      h->root.u.def.value =
	_bfd_merged_section_offset (output_bfd,
				    &h->root.u.def.section,
				    elf_section_data (sec)->sec_info,
				    h->root.u.def.value);
    }

  return TRUE;
}