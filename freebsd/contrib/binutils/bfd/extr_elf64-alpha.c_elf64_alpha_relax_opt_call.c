#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
struct alpha_relax_info {int other; scalar_t__ gotobj; TYPE_12__* tsec; TYPE_3__* link_info; int /*<<< orphan*/  abfd; TYPE_4__* relend; TYPE_4__* relocs; TYPE_12__* sec; } ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_20__ {scalar_t__ gotobj; } ;
struct TYPE_19__ {int r_addend; } ;
struct TYPE_18__ {TYPE_2__* hash; scalar_t__ keep_memory; } ;
struct TYPE_17__ {scalar_t__ creator; } ;
struct TYPE_16__ {scalar_t__ vma; } ;
struct TYPE_15__ {int reloc_count; TYPE_10__* owner; scalar_t__ output_offset; TYPE_1__* output_section; } ;
struct TYPE_14__ {scalar_t__ xvec; } ;
typedef  int /*<<< orphan*/  PTR ;
typedef  TYPE_4__ Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  R_ALPHA_GPDISP ; 
 int STO_ALPHA_NOPV ; 
 int STO_ALPHA_STD_GPLOAD ; 
 TYPE_4__* _bfd_elf_link_read_relocs (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ ,TYPE_4__*,scalar_t__) ; 
 TYPE_9__* alpha_elf_tdata (TYPE_10__*) ; 
 TYPE_4__* elf64_alpha_find_reloc_at_ofs (TYPE_4__*,TYPE_4__*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 

__attribute__((used)) static bfd_vma
elf64_alpha_relax_opt_call (struct alpha_relax_info *info, bfd_vma symval)
{
  /* If the function has the same gp, and we can identify that the
     function does not use its function pointer, we can eliminate the
     address load.  */

  /* If the symbol is marked NOPV, we are being told the function never
     needs its procedure value.  */
  if ((info->other & STO_ALPHA_STD_GPLOAD) == STO_ALPHA_NOPV)
    return symval;

  /* If the symbol is marked STD_GP, we are being told the function does
     a normal ldgp in the first two words.  */
  else if ((info->other & STO_ALPHA_STD_GPLOAD) == STO_ALPHA_STD_GPLOAD)
    ;

  /* Otherwise, we may be able to identify a GP load in the first two
     words, which we can then skip.  */
  else
    {
      Elf_Internal_Rela *tsec_relocs, *tsec_relend, *tsec_free, *gpdisp;
      bfd_vma ofs;

      /* Load the relocations from the section that the target symbol is in.  */
      if (info->sec == info->tsec)
	{
	  tsec_relocs = info->relocs;
	  tsec_relend = info->relend;
	  tsec_free = NULL;
	}
      else
	{
	  tsec_relocs = (_bfd_elf_link_read_relocs
		         (info->abfd, info->tsec, (PTR) NULL,
			 (Elf_Internal_Rela *) NULL,
			 info->link_info->keep_memory));
	  if (tsec_relocs == NULL)
	    return 0;
	  tsec_relend = tsec_relocs + info->tsec->reloc_count;
	  tsec_free = (info->link_info->keep_memory ? NULL : tsec_relocs);
	}

      /* Recover the symbol's offset within the section.  */
      ofs = (symval - info->tsec->output_section->vma
	     - info->tsec->output_offset);

      /* Look for a GPDISP reloc.  */
      gpdisp = (elf64_alpha_find_reloc_at_ofs
		(tsec_relocs, tsec_relend, ofs, R_ALPHA_GPDISP));

      if (!gpdisp || gpdisp->r_addend != 4)
	{
	  if (tsec_free)
	    free (tsec_free);
	  return 0;
	}
      if (tsec_free)
        free (tsec_free);
    }

  /* We've now determined that we can skip an initial gp load.  Verify
     that the call and the target use the same gp.   */
  if (info->link_info->hash->creator != info->tsec->owner->xvec
      || info->gotobj != alpha_elf_tdata (info->tsec->owner)->gotobj)
    return 0;

  return symval + 8;
}