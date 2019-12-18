#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  asymbol ;
struct TYPE_9__ {unsigned char* contents; } ;
typedef  TYPE_1__ asection ;
struct TYPE_10__ {int /*<<< orphan*/  bfd_arch; int /*<<< orphan*/  object_target; } ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_RELOC_RVA ; 
 int /*<<< orphan*/  BSF_GLOBAL ; 
 int PE_IDATA4_SIZE ; 
 int /*<<< orphan*/  SEC_HAS_CONTENTS ; 
 int /*<<< orphan*/  U (char*) ; 
 TYPE_1__* UNDSEC ; 
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
 TYPE_5__* pe_details ; 
 int /*<<< orphan*/  quick_reloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* quick_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quick_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_relocs (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ symptr ; 
 void* symtab ; 
 int tmp_seq ; 
 void* xmalloc (int) ; 

__attribute__((used)) static bfd *
make_singleton_name_thunk (const char *import, bfd *parent)
{
  /* Name thunks go to idata$4.  */
  asection *id4;
  unsigned char *d4;
  char *oname;
  bfd *abfd;

  oname = xmalloc (20);
  sprintf (oname, "nmth%06d.o", tmp_seq);
  tmp_seq++;

  abfd = bfd_create (oname, parent);
  bfd_find_target (pe_details->object_target, abfd);
  bfd_make_writable (abfd);

  bfd_set_format (abfd, bfd_object);
  bfd_set_arch_mach (abfd, pe_details->bfd_arch, 0);

  symptr = 0;
  symtab = xmalloc (3 * sizeof (asymbol *));
  id4 = quick_section (abfd, ".idata$4", SEC_HAS_CONTENTS, 2);
  quick_symbol (abfd, U ("_nm_thnk_"), import, "", id4, BSF_GLOBAL, 0);
  quick_symbol (abfd, U ("_nm_"), import, "", UNDSEC, BSF_GLOBAL, 0);

  /* We need space for the real thunk and for the null terminator.  */
  bfd_set_section_size (abfd, id4, PE_IDATA4_SIZE * 2);
  d4 = xmalloc (PE_IDATA4_SIZE * 2);
  id4->contents = d4;
  memset (d4, 0, PE_IDATA4_SIZE * 2);
  quick_reloc (abfd, 0, BFD_RELOC_RVA, 2);
  save_relocs (id4);

  bfd_set_symtab (abfd, symtab, symptr);

  bfd_set_section_contents (abfd, id4, d4, 0, PE_IDATA4_SIZE * 2);

  bfd_make_readable (abfd);
  return abfd;
}