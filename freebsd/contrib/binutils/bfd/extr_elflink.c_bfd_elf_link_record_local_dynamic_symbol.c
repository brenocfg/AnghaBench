#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct elf_strtab_hash {int dummy; } ;
struct TYPE_9__ {scalar_t__ st_shndx; unsigned long st_name; int /*<<< orphan*/  st_info; } ;
struct elf_link_local_dynamic_entry {long input_indx; TYPE_5__ isym; int /*<<< orphan*/ * input_bfd; struct elf_link_local_dynamic_entry* next; } ;
struct elf_link_hash_table {int /*<<< orphan*/  dynsymcount; struct elf_link_local_dynamic_entry* dynlocal; struct elf_strtab_hash* dynstr; } ;
struct bfd_link_info {int /*<<< orphan*/  hash; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_6__ {int /*<<< orphan*/  output_section; } ;
typedef  TYPE_1__ asection ;
struct TYPE_8__ {int /*<<< orphan*/  sh_link; } ;
struct TYPE_7__ {TYPE_4__ symtab_hdr; } ;
typedef  int /*<<< orphan*/  Elf_External_Sym_Shndx ;
typedef  int /*<<< orphan*/  Elf64_External_Sym ;

/* Variables and functions */
 int /*<<< orphan*/  ELF_ST_INFO (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ELF_ST_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ SHN_HIRESERVE ; 
 scalar_t__ SHN_LORESERVE ; 
 scalar_t__ SHN_UNDEF ; 
 int /*<<< orphan*/  STB_LOCAL ; 
 unsigned long _bfd_elf_strtab_add (struct elf_strtab_hash*,char*,int /*<<< orphan*/ ) ; 
 struct elf_strtab_hash* _bfd_elf_strtab_init () ; 
 struct elf_link_local_dynamic_entry* bfd_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  bfd_elf_get_elf_syms (int /*<<< orphan*/ *,TYPE_4__*,int,long,TYPE_5__*,char*,int /*<<< orphan*/ *) ; 
 char* bfd_elf_string_from_elf_section (int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ bfd_is_abs_section (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_release (int /*<<< orphan*/ *,struct elf_link_local_dynamic_entry*) ; 
 TYPE_1__* bfd_section_from_elf_index (int /*<<< orphan*/ *,scalar_t__) ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 
 TYPE_2__* elf_tdata (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  is_elf_hash_table (int /*<<< orphan*/ ) ; 

int
bfd_elf_link_record_local_dynamic_symbol (struct bfd_link_info *info,
					  bfd *input_bfd,
					  long input_indx)
{
  bfd_size_type amt;
  struct elf_link_local_dynamic_entry *entry;
  struct elf_link_hash_table *eht;
  struct elf_strtab_hash *dynstr;
  unsigned long dynstr_index;
  char *name;
  Elf_External_Sym_Shndx eshndx;
  char esym[sizeof (Elf64_External_Sym)];

  if (! is_elf_hash_table (info->hash))
    return 0;

  /* See if the entry exists already.  */
  for (entry = elf_hash_table (info)->dynlocal; entry ; entry = entry->next)
    if (entry->input_bfd == input_bfd && entry->input_indx == input_indx)
      return 1;

  amt = sizeof (*entry);
  entry = bfd_alloc (input_bfd, amt);
  if (entry == NULL)
    return 0;

  /* Go find the symbol, so that we can find it's name.  */
  if (!bfd_elf_get_elf_syms (input_bfd, &elf_tdata (input_bfd)->symtab_hdr,
			     1, input_indx, &entry->isym, esym, &eshndx))
    {
      bfd_release (input_bfd, entry);
      return 0;
    }

  if (entry->isym.st_shndx != SHN_UNDEF
      && (entry->isym.st_shndx < SHN_LORESERVE
	  || entry->isym.st_shndx > SHN_HIRESERVE))
    {
      asection *s;

      s = bfd_section_from_elf_index (input_bfd, entry->isym.st_shndx);
      if (s == NULL || bfd_is_abs_section (s->output_section))
	{
	  /* We can still bfd_release here as nothing has done another
	     bfd_alloc.  We can't do this later in this function.  */
	  bfd_release (input_bfd, entry);
	  return 2;
	}
    }

  name = (bfd_elf_string_from_elf_section
	  (input_bfd, elf_tdata (input_bfd)->symtab_hdr.sh_link,
	   entry->isym.st_name));

  dynstr = elf_hash_table (info)->dynstr;
  if (dynstr == NULL)
    {
      /* Create a strtab to hold the dynamic symbol names.  */
      elf_hash_table (info)->dynstr = dynstr = _bfd_elf_strtab_init ();
      if (dynstr == NULL)
	return 0;
    }

  dynstr_index = _bfd_elf_strtab_add (dynstr, name, FALSE);
  if (dynstr_index == (unsigned long) -1)
    return 0;
  entry->isym.st_name = dynstr_index;

  eht = elf_hash_table (info);

  entry->next = eht->dynlocal;
  eht->dynlocal = entry;
  entry->input_bfd = input_bfd;
  entry->input_indx = input_indx;
  eht->dynsymcount++;

  /* Whatever binding the symbol had before, it's now local.  */
  entry->isym.st_info
    = ELF_ST_INFO (STB_LOCAL, ELF_ST_TYPE (entry->isym.st_info));

  /* The dynindx will be set at the end of size_dynamic_sections.  */

  return 1;
}