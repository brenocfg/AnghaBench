#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_final_link_info {int symbuf_count; int /*<<< orphan*/  output_bfd; int /*<<< orphan*/  symbuf; } ;
struct elf_backend_data {TYPE_1__* s; } ;
typedef  scalar_t__ file_ptr ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_5__ {scalar_t__ sh_size; scalar_t__ sh_offset; } ;
struct TYPE_6__ {TYPE_2__ symtab_hdr; } ;
struct TYPE_4__ {int sizeof_sym; } ;
typedef  TYPE_2__ Elf_Internal_Shdr ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRUE ; 
 int bfd_bwrite (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_seek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_3__* elf_tdata (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_link_flush_output_syms (struct elf_final_link_info *finfo,
			    const struct elf_backend_data *bed)
{
  if (finfo->symbuf_count > 0)
    {
      Elf_Internal_Shdr *hdr;
      file_ptr pos;
      bfd_size_type amt;

      hdr = &elf_tdata (finfo->output_bfd)->symtab_hdr;
      pos = hdr->sh_offset + hdr->sh_size;
      amt = finfo->symbuf_count * bed->s->sizeof_sym;
      if (bfd_seek (finfo->output_bfd, pos, SEEK_SET) != 0
	  || bfd_bwrite (finfo->symbuf, amt, finfo->output_bfd) != amt)
	return FALSE;

      hdr->sh_size += amt;
      finfo->symbuf_count = 0;
    }

  return TRUE;
}