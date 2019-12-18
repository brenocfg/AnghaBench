#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_9__ ;
typedef  struct TYPE_26__   TYPE_8__ ;
typedef  struct TYPE_25__   TYPE_7__ ;
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_14__ ;
typedef  struct TYPE_17__   TYPE_12__ ;
typedef  struct TYPE_16__   TYPE_11__ ;
typedef  struct TYPE_15__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {scalar_t__ sc; scalar_t__ value; void* st; int /*<<< orphan*/  index; scalar_t__ reserved; } ;
struct TYPE_18__ {int ifd; TYPE_4__ asym; scalar_t__ reserved; scalar_t__ weakext; scalar_t__ cobol_main; scalar_t__ jmptbl; } ;
struct TYPE_23__ {char* string; } ;
struct TYPE_20__ {TYPE_10__* section; scalar_t__ value; } ;
struct TYPE_24__ {scalar_t__ link; } ;
struct TYPE_19__ {scalar_t__ size; } ;
struct TYPE_25__ {TYPE_2__ def; TYPE_6__ i; TYPE_1__ c; } ;
struct TYPE_26__ {scalar_t__ type; TYPE_5__ root; TYPE_7__ u; } ;
struct TYPE_21__ {scalar_t__ offset; } ;
struct TYPE_27__ {int indx; scalar_t__ type; TYPE_8__ root; TYPE_3__ plt; scalar_t__ needs_plt; int /*<<< orphan*/  ref_regular; int /*<<< orphan*/  def_regular; scalar_t__ ref_dynamic; scalar_t__ def_dynamic; } ;
struct mips_elf_link_hash_entry {int no_fn_stub; TYPE_14__ esym; TYPE_9__ root; } ;
struct extsym_info {int failed; int /*<<< orphan*/  swap; int /*<<< orphan*/  debug; int /*<<< orphan*/  abfd; TYPE_12__* info; } ;
typedef  int bfd_boolean ;
struct TYPE_15__ {scalar_t__ vma; scalar_t__ output_offset; struct TYPE_15__* output_section; int /*<<< orphan*/  owner; } ;
typedef  TYPE_10__ asection ;
struct TYPE_17__ {scalar_t__ strip; int /*<<< orphan*/  keep_hash; } ;
struct TYPE_16__ {scalar_t__ procedure_count; } ;

/* Variables and functions */
 int FALSE ; 
 int /*<<< orphan*/  NEWABI_P (int /*<<< orphan*/ ) ; 
 int TRUE ; 
 int /*<<< orphan*/  bfd_ecoff_debug_one_external (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_14__*) ; 
 int /*<<< orphan*/ * bfd_hash_lookup (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ bfd_link_hash_common ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_new ; 
 scalar_t__ bfd_link_hash_undefined ; 
 scalar_t__ bfd_link_hash_undefweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 char* bfd_section_name (int /*<<< orphan*/ ,TYPE_10__*) ; 
 scalar_t__ elf_gp (int /*<<< orphan*/ ) ; 
 int ifdNil ; 
 int /*<<< orphan*/  indexNil ; 
 char** mips_elf_dynsym_rtproc_names ; 
 TYPE_11__* mips_elf_hash_table (TYPE_12__*) ; 
 void* scAbs ; 
 void* scBss ; 
 scalar_t__ scCommon ; 
 void* scData ; 
 scalar_t__ scFini ; 
 scalar_t__ scInit ; 
 scalar_t__ scRData ; 
 void* scSBss ; 
 scalar_t__ scSCommon ; 
 scalar_t__ scSData ; 
 scalar_t__ scText ; 
 void* scUndefined ; 
 void* stGlobal ; 
 void* stLabel ; 
 void* stProc ; 
 scalar_t__ strcmp (char const*,char*) ; 
 scalar_t__ strip_all ; 
 scalar_t__ strip_some ; 

__attribute__((used)) static bfd_boolean
mips_elf_output_extsym (struct mips_elf_link_hash_entry *h, void *data)
{
  struct extsym_info *einfo = data;
  bfd_boolean strip;
  asection *sec, *output_section;

  if (h->root.root.type == bfd_link_hash_warning)
    h = (struct mips_elf_link_hash_entry *) h->root.root.u.i.link;

  if (h->root.indx == -2)
    strip = FALSE;
  else if ((h->root.def_dynamic
	    || h->root.ref_dynamic
	    || h->root.type == bfd_link_hash_new)
	   && !h->root.def_regular
	   && !h->root.ref_regular)
    strip = TRUE;
  else if (einfo->info->strip == strip_all
	   || (einfo->info->strip == strip_some
	       && bfd_hash_lookup (einfo->info->keep_hash,
				   h->root.root.root.string,
				   FALSE, FALSE) == NULL))
    strip = TRUE;
  else
    strip = FALSE;

  if (strip)
    return TRUE;

  if (h->esym.ifd == -2)
    {
      h->esym.jmptbl = 0;
      h->esym.cobol_main = 0;
      h->esym.weakext = 0;
      h->esym.reserved = 0;
      h->esym.ifd = ifdNil;
      h->esym.asym.value = 0;
      h->esym.asym.st = stGlobal;

      if (h->root.root.type == bfd_link_hash_undefined
	  || h->root.root.type == bfd_link_hash_undefweak)
	{
	  const char *name;

	  /* Use undefined class.  Also, set class and type for some
             special symbols.  */
	  name = h->root.root.root.string;
	  if (strcmp (name, mips_elf_dynsym_rtproc_names[0]) == 0
	      || strcmp (name, mips_elf_dynsym_rtproc_names[1]) == 0)
	    {
	      h->esym.asym.sc = scData;
	      h->esym.asym.st = stLabel;
	      h->esym.asym.value = 0;
	    }
	  else if (strcmp (name, mips_elf_dynsym_rtproc_names[2]) == 0)
	    {
	      h->esym.asym.sc = scAbs;
	      h->esym.asym.st = stLabel;
	      h->esym.asym.value =
		mips_elf_hash_table (einfo->info)->procedure_count;
	    }
	  else if (strcmp (name, "_gp_disp") == 0 && ! NEWABI_P (einfo->abfd))
	    {
	      h->esym.asym.sc = scAbs;
	      h->esym.asym.st = stLabel;
	      h->esym.asym.value = elf_gp (einfo->abfd);
	    }
	  else
	    h->esym.asym.sc = scUndefined;
	}
      else if (h->root.root.type != bfd_link_hash_defined
	  && h->root.root.type != bfd_link_hash_defweak)
	h->esym.asym.sc = scAbs;
      else
	{
	  const char *name;

	  sec = h->root.root.u.def.section;
	  output_section = sec->output_section;

	  /* When making a shared library and symbol h is the one from
	     the another shared library, OUTPUT_SECTION may be null.  */
	  if (output_section == NULL)
	    h->esym.asym.sc = scUndefined;
	  else
	    {
	      name = bfd_section_name (output_section->owner, output_section);

	      if (strcmp (name, ".text") == 0)
		h->esym.asym.sc = scText;
	      else if (strcmp (name, ".data") == 0)
		h->esym.asym.sc = scData;
	      else if (strcmp (name, ".sdata") == 0)
		h->esym.asym.sc = scSData;
	      else if (strcmp (name, ".rodata") == 0
		       || strcmp (name, ".rdata") == 0)
		h->esym.asym.sc = scRData;
	      else if (strcmp (name, ".bss") == 0)
		h->esym.asym.sc = scBss;
	      else if (strcmp (name, ".sbss") == 0)
		h->esym.asym.sc = scSBss;
	      else if (strcmp (name, ".init") == 0)
		h->esym.asym.sc = scInit;
	      else if (strcmp (name, ".fini") == 0)
		h->esym.asym.sc = scFini;
	      else
		h->esym.asym.sc = scAbs;
	    }
	}

      h->esym.asym.reserved = 0;
      h->esym.asym.index = indexNil;
    }

  if (h->root.root.type == bfd_link_hash_common)
    h->esym.asym.value = h->root.root.u.c.size;
  else if (h->root.root.type == bfd_link_hash_defined
	   || h->root.root.type == bfd_link_hash_defweak)
    {
      if (h->esym.asym.sc == scCommon)
	h->esym.asym.sc = scBss;
      else if (h->esym.asym.sc == scSCommon)
	h->esym.asym.sc = scSBss;

      sec = h->root.root.u.def.section;
      output_section = sec->output_section;
      if (output_section != NULL)
	h->esym.asym.value = (h->root.root.u.def.value
			      + sec->output_offset
			      + output_section->vma);
      else
	h->esym.asym.value = 0;
    }
  else if (h->root.needs_plt)
    {
      struct mips_elf_link_hash_entry *hd = h;
      bfd_boolean no_fn_stub = h->no_fn_stub;

      while (hd->root.root.type == bfd_link_hash_indirect)
	{
	  hd = (struct mips_elf_link_hash_entry *)h->root.root.u.i.link;
	  no_fn_stub = no_fn_stub || hd->no_fn_stub;
	}

      if (!no_fn_stub)
	{
	  /* Set type and value for a symbol with a function stub.  */
	  h->esym.asym.st = stProc;
	  sec = hd->root.root.u.def.section;
	  if (sec == NULL)
	    h->esym.asym.value = 0;
	  else
	    {
	      output_section = sec->output_section;
	      if (output_section != NULL)
		h->esym.asym.value = (hd->root.plt.offset
				      + sec->output_offset
				      + output_section->vma);
	      else
		h->esym.asym.value = 0;
	    }
	}
    }

  if (! bfd_ecoff_debug_one_external (einfo->abfd, einfo->debug, einfo->swap,
				      h->root.root.root.string,
				      &h->esym))
    {
      einfo->failed = TRUE;
      return FALSE;
    }

  return TRUE;
}