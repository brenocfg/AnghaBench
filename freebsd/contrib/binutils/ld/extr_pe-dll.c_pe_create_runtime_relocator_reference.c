#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_7__ {unsigned char* contents; } ;
typedef  TYPE_1__ asection ;
struct TYPE_8__ {int /*<<< orphan*/  bfd_arch; int /*<<< orphan*/  object_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_RVA ; 
 int /*<<< orphan*/  BSF_NO_FLAGS ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  U (char*) ; 
 int /*<<< orphan*/  UNDSEC ; 
 int /*<<< orphan*/ * bfd_create (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_find_target (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_make_readable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_make_writable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_object ; 
 int /*<<< orphan*/  bfd_set_arch_mach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_format (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_set_section_contents (int /*<<< orphan*/ *,TYPE_1__*,unsigned char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_set_section_size (int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/  bfd_set_symtab (int /*<<< orphan*/ *,void*,scalar_t__) ; 
 TYPE_4__* pe_details ; 
 int /*<<< orphan*/  quick_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* quick_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quick_symbol (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_relocs (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ symptr ; 
 void* symtab ; 
 int tmp_seq ; 
 void* xmalloc (int) ; 

__attribute__((used)) static bfd *
pe_create_runtime_relocator_reference (bfd *parent)
{
  asection *extern_rt_rel;
  unsigned char *extern_rt_rel_d;
  char *oname;
  bfd *abfd;

  oname = xmalloc (20);
  sprintf (oname, "ertr%06d.o", tmp_seq);
  tmp_seq++;

  abfd = bfd_create (oname, parent);
  bfd_find_target (pe_details->object_target, abfd);
  bfd_make_writable (abfd);

  bfd_set_format (abfd, bfd_object);
  bfd_set_arch_mach (abfd, pe_details->bfd_arch, 0);

  symptr = 0;
  symtab = xmalloc (2 * sizeof (asymbol *));
  extern_rt_rel = quick_section (abfd, ".rdata", SEC_HAS_CONTENTS, 2);

  quick_symbol (abfd, "", U ("_pei386_runtime_relocator"), "", UNDSEC,
		BSF_NO_FLAGS, 0);

  bfd_set_section_size (abfd, extern_rt_rel, 4);
  extern_rt_rel_d = xmalloc (4);
  extern_rt_rel->contents = extern_rt_rel_d;

  quick_reloc (abfd, 0, BFD_RELOC_RVA, 1);
  save_relocs (extern_rt_rel);

  bfd_set_symtab (abfd, symtab, symptr);

  bfd_set_section_contents (abfd, extern_rt_rel, extern_rt_rel_d, 0, 4);

  bfd_make_readable (abfd);
  return abfd;
}