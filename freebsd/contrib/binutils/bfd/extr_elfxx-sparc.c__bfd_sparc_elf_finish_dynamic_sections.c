#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_8__ ;
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_info {scalar_t__ shared; } ;
struct TYPE_11__ {int /*<<< orphan*/ * dynobj; } ;
struct _bfd_sparc_elf_link_hash_table {TYPE_3__* sgot; int /*<<< orphan*/  plt_entry_size; scalar_t__ is_vxworks; int /*<<< orphan*/  plt_header_size; TYPE_1__ elf; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_14__ {scalar_t__ size; scalar_t__ contents; scalar_t__ output_offset; TYPE_8__* output_section; } ;
typedef  TYPE_4__ asection ;
struct TYPE_17__ {scalar_t__ dynamic_sections_created; } ;
struct TYPE_16__ {scalar_t__ vma; } ;
struct TYPE_12__ {int /*<<< orphan*/  sh_entsize; } ;
struct TYPE_15__ {TYPE_2__ this_hdr; } ;
struct TYPE_13__ {scalar_t__ size; TYPE_8__* output_section; int /*<<< orphan*/  contents; } ;

/* Variables and functions */
 int /*<<< orphan*/  ABI_64_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BFD_ASSERT (int) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  SPARC_ELF_PUT_WORD (struct _bfd_sparc_elf_link_hash_table*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SPARC_ELF_WORD_BYTES (struct _bfd_sparc_elf_link_hash_table*) ; 
 scalar_t__ SPARC_NOP ; 
 int /*<<< orphan*/  TRUE ; 
 struct _bfd_sparc_elf_link_hash_table* _bfd_sparc_elf_hash_table (struct bfd_link_info*) ; 
 TYPE_4__* bfd_get_section_by_name (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 TYPE_9__* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_7__* elf_section_data (TYPE_8__*) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sparc_finish_dyn (int /*<<< orphan*/ *,struct bfd_link_info*,int /*<<< orphan*/ *,TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/  sparc_vxworks_finish_exec_plt (int /*<<< orphan*/ *,struct bfd_link_info*) ; 
 int /*<<< orphan*/  sparc_vxworks_finish_shared_plt (int /*<<< orphan*/ *,struct bfd_link_info*) ; 

bfd_boolean
_bfd_sparc_elf_finish_dynamic_sections (bfd *output_bfd, struct bfd_link_info *info)
{
  bfd *dynobj;
  asection *sdyn;
  struct _bfd_sparc_elf_link_hash_table *htab;

  htab = _bfd_sparc_elf_hash_table (info);
  dynobj = htab->elf.dynobj;

  sdyn = bfd_get_section_by_name (dynobj, ".dynamic");

  if (elf_hash_table (info)->dynamic_sections_created)
    {
      asection *splt;

      splt = bfd_get_section_by_name (dynobj, ".plt");
      BFD_ASSERT (splt != NULL && sdyn != NULL);

      if (!sparc_finish_dyn (output_bfd, info, dynobj, sdyn, splt))
	return FALSE;

      /* Initialize the contents of the .plt section.  */
      if (splt->size > 0)
	{
	  if (htab->is_vxworks)
	    {
	      if (info->shared)
		sparc_vxworks_finish_shared_plt (output_bfd, info);
	      else
		sparc_vxworks_finish_exec_plt (output_bfd, info);
	    }
	  else
	    {
	      memset (splt->contents, 0, htab->plt_header_size);
	      if (!ABI_64_P (output_bfd))
		bfd_put_32 (output_bfd, (bfd_vma) SPARC_NOP,
			    splt->contents + splt->size - 4);
	    }
	}

      elf_section_data (splt->output_section)->this_hdr.sh_entsize
	= (htab->is_vxworks || !ABI_64_P (output_bfd))
	  ? 0 : htab->plt_entry_size;
    }

  /* Set the first entry in the global offset table to the address of
     the dynamic section.  */
  if (htab->sgot && htab->sgot->size > 0)
    {
      bfd_vma val = (sdyn ?
		     sdyn->output_section->vma + sdyn->output_offset :
		     0);

      SPARC_ELF_PUT_WORD (htab, output_bfd, val, htab->sgot->contents);
    }

  if (htab->sgot)
    elf_section_data (htab->sgot->output_section)->this_hdr.sh_entsize =
      SPARC_ELF_WORD_BYTES (htab);

  return TRUE;
}