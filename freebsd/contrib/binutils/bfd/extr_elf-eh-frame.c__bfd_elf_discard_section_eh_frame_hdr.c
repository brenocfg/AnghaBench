#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct eh_frame_hdr_info {int fde_count; scalar_t__ table; TYPE_1__* hdr_sec; int /*<<< orphan*/ * cies; } ;
struct elf_link_hash_table {struct eh_frame_hdr_info eh_info; } ;
struct bfd_link_info {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_3__ {int size; } ;
typedef  TYPE_1__ asection ;
struct TYPE_4__ {TYPE_1__* eh_frame_hdr; } ;

/* Variables and functions */
 int EH_FRAME_HDR_SIZE ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  htab_delete (int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_discard_section_eh_frame_hdr (bfd *abfd, struct bfd_link_info *info)
{
  struct elf_link_hash_table *htab;
  struct eh_frame_hdr_info *hdr_info;
  asection *sec;

  htab = elf_hash_table (info);
  hdr_info = &htab->eh_info;

  if (hdr_info->cies != NULL)
    {
      htab_delete (hdr_info->cies);
      hdr_info->cies = NULL;
    }

  sec = hdr_info->hdr_sec;
  if (sec == NULL)
    return FALSE;

  sec->size = EH_FRAME_HDR_SIZE;
  if (hdr_info->table)
    sec->size += 4 + hdr_info->fde_count * 8;

  elf_tdata (abfd)->eh_frame_hdr = sec;
  return TRUE;
}