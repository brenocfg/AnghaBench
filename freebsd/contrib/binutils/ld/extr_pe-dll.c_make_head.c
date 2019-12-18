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
 int PE_IDATA5_SIZE ; 
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
 int /*<<< orphan*/  dll_symname ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 TYPE_5__* pe_details ; 
 int /*<<< orphan*/  quick_reloc (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int) ; 
 TYPE_1__* quick_section (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  quick_symbol (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  save_relocs (TYPE_1__*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 scalar_t__ symptr ; 
 void* symtab ; 
 int tmp_seq ; 
 void* xmalloc (int) ; 

__attribute__((used)) static bfd *
make_head (bfd *parent)
{
  asection *id2, *id5, *id4;
  unsigned char *d2, *d5, *d4;
  char *oname;
  bfd *abfd;

  oname = xmalloc (20);
  sprintf (oname, "d%06d.o", tmp_seq);
  tmp_seq++;

  abfd = bfd_create (oname, parent);
  bfd_find_target (pe_details->object_target, abfd);
  bfd_make_writable (abfd);

  bfd_set_format (abfd, bfd_object);
  bfd_set_arch_mach (abfd, pe_details->bfd_arch, 0);

  symptr = 0;
  symtab = xmalloc (6 * sizeof (asymbol *));
  id2 = quick_section (abfd, ".idata$2", SEC_HAS_CONTENTS, 2);
  id5 = quick_section (abfd, ".idata$5", SEC_HAS_CONTENTS, 2);
  id4 = quick_section (abfd, ".idata$4", SEC_HAS_CONTENTS, 2);
  quick_symbol (abfd, U ("_head_"), dll_symname, "", id2, BSF_GLOBAL, 0);
  quick_symbol (abfd, U (""), dll_symname, "_iname", UNDSEC, BSF_GLOBAL, 0);

  /* OK, pay attention here.  I got confused myself looking back at
     it.  We create a four-byte section to mark the beginning of the
     list, and we include an offset of 4 in the section, so that the
     pointer to the list points to the *end* of this section, which is
     the start of the list of sections from other objects.  */

  bfd_set_section_size (abfd, id2, 20);
  d2 = xmalloc (20);
  id2->contents = d2;
  memset (d2, 0, 20);
  d2[0] = d2[16] = 4; /* Reloc addend.  */
  quick_reloc (abfd,  0, BFD_RELOC_RVA, 2);
  quick_reloc (abfd, 12, BFD_RELOC_RVA, 4);
  quick_reloc (abfd, 16, BFD_RELOC_RVA, 1);
  save_relocs (id2);

  bfd_set_section_size (abfd, id5, PE_IDATA5_SIZE);
  d5 = xmalloc (PE_IDATA5_SIZE);
  id5->contents = d5;
  memset (d5, 0, PE_IDATA5_SIZE);

  bfd_set_section_size (abfd, id4, PE_IDATA4_SIZE);
  d4 = xmalloc (PE_IDATA4_SIZE);
  id4->contents = d4;
  memset (d4, 0, PE_IDATA4_SIZE);

  bfd_set_symtab (abfd, symtab, symptr);

  bfd_set_section_contents (abfd, id2, d2, 0, 20);
  bfd_set_section_contents (abfd, id5, d5, 0, PE_IDATA5_SIZE);
  bfd_set_section_contents (abfd, id4, d4, 0, PE_IDATA4_SIZE);

  bfd_make_readable (abfd);
  return abfd;
}