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
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 char* U (char*) ; 
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
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_4__* pe_details ; 
 int /*<<< orphan*/  quick_reloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* quick_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quick_symbol (int /*<<< orphan*/ *,char*,char const*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_relocs (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ symptr ; 
 void* symtab ; 
 int tmp_seq ; 
 void* xmalloc (int) ; 

__attribute__((used)) static bfd *
make_import_fixup_entry (const char *name,
			 const char *fixup_name,
			 const char *dll_symname,
			 bfd *parent)
{
  asection *id2;
  unsigned char *d2;
  char *oname;
  bfd *abfd;

  oname = xmalloc (20);
  sprintf (oname, "fu%06d.o", tmp_seq);
  tmp_seq++;

  abfd = bfd_create (oname, parent);
  bfd_find_target (pe_details->object_target, abfd);
  bfd_make_writable (abfd);

  bfd_set_format (abfd, bfd_object);
  bfd_set_arch_mach (abfd, pe_details->bfd_arch, 0);

  symptr = 0;
  symtab = xmalloc (6 * sizeof (asymbol *));
  id2 = quick_section (abfd, ".idata$2", SEC_HAS_CONTENTS, 2);

  quick_symbol (abfd, U ("_nm_thnk_"), name, "", UNDSEC, BSF_GLOBAL, 0);
  quick_symbol (abfd, U (""), dll_symname, "_iname", UNDSEC, BSF_GLOBAL, 0);
  quick_symbol (abfd, "", fixup_name, "", UNDSEC, BSF_GLOBAL, 0);

  bfd_set_section_size (abfd, id2, 20);
  d2 = xmalloc (20);
  id2->contents = d2;
  memset (d2, 0, 20);

  quick_reloc (abfd, 0, BFD_RELOC_RVA, 1);
  quick_reloc (abfd, 12, BFD_RELOC_RVA, 2);
  quick_reloc (abfd, 16, BFD_RELOC_RVA, 3);
  save_relocs (id2);

  bfd_set_symtab (abfd, symtab, symptr);

  bfd_set_section_contents (abfd, id2, d2, 0, 20);

  bfd_make_readable (abfd);
  return abfd;
}