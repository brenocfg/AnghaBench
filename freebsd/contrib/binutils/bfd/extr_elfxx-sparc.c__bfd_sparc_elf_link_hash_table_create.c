#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct bfd_link_hash_table {int dummy; } ;
struct TYPE_2__ {struct bfd_link_hash_table root; } ;
struct _bfd_sparc_elf_link_hash_table {int word_align_power; int align_power_max; int bytes_per_word; int bytes_per_rela; int dynamic_interpreter_size; TYPE_1__ elf; int /*<<< orphan*/  dynamic_interpreter; int /*<<< orphan*/  tpoff_reloc; int /*<<< orphan*/  dtpmod_reloc; int /*<<< orphan*/  dtpoff_reloc; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_info; int /*<<< orphan*/  put_word; } ;
struct _bfd_sparc_elf_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;
typedef  int /*<<< orphan*/  Elf64_External_Rela ;
typedef  int /*<<< orphan*/  Elf32_External_Rela ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ELF32_DYNAMIC_INTERPRETER ; 
 int /*<<< orphan*/  ELF64_DYNAMIC_INTERPRETER ; 
 int /*<<< orphan*/  R_SPARC_TLS_DTPMOD32 ; 
 int /*<<< orphan*/  R_SPARC_TLS_DTPMOD64 ; 
 int /*<<< orphan*/  R_SPARC_TLS_DTPOFF32 ; 
 int /*<<< orphan*/  R_SPARC_TLS_DTPOFF64 ; 
 int /*<<< orphan*/  R_SPARC_TLS_TPOFF32 ; 
 int /*<<< orphan*/  R_SPARC_TLS_TPOFF64 ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bfd_zmalloc (int) ; 
 int /*<<< orphan*/  free (struct _bfd_sparc_elf_link_hash_table*) ; 
 int /*<<< orphan*/  link_hash_newfunc ; 
 int /*<<< orphan*/  sparc_elf_r_info_32 ; 
 int /*<<< orphan*/  sparc_elf_r_info_64 ; 
 int /*<<< orphan*/  sparc_elf_r_symndx_32 ; 
 int /*<<< orphan*/  sparc_elf_r_symndx_64 ; 
 int /*<<< orphan*/  sparc_put_word_32 ; 
 int /*<<< orphan*/  sparc_put_word_64 ; 

struct bfd_link_hash_table *
_bfd_sparc_elf_link_hash_table_create (bfd *abfd)
{
  struct _bfd_sparc_elf_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct _bfd_sparc_elf_link_hash_table);

  ret = (struct _bfd_sparc_elf_link_hash_table *) bfd_zmalloc (amt);
  if (ret == NULL)
    return NULL;

  if (ABI_64_P (abfd))
    {
      ret->put_word = sparc_put_word_64;
      ret->r_info = sparc_elf_r_info_64;
      ret->r_symndx = sparc_elf_r_symndx_64;
      ret->dtpoff_reloc = R_SPARC_TLS_DTPOFF64;
      ret->dtpmod_reloc = R_SPARC_TLS_DTPMOD64;
      ret->tpoff_reloc = R_SPARC_TLS_TPOFF64;
      ret->word_align_power = 3;
      ret->align_power_max = 4;
      ret->bytes_per_word = 8;
      ret->bytes_per_rela = sizeof (Elf64_External_Rela);
      ret->dynamic_interpreter = ELF64_DYNAMIC_INTERPRETER;
      ret->dynamic_interpreter_size = sizeof ELF64_DYNAMIC_INTERPRETER;
    }
  else
    {
      ret->put_word = sparc_put_word_32;
      ret->r_info = sparc_elf_r_info_32;
      ret->r_symndx = sparc_elf_r_symndx_32;
      ret->dtpoff_reloc = R_SPARC_TLS_DTPOFF32;
      ret->dtpmod_reloc = R_SPARC_TLS_DTPMOD32;
      ret->tpoff_reloc = R_SPARC_TLS_TPOFF32;
      ret->word_align_power = 2;
      ret->align_power_max = 3;
      ret->bytes_per_word = 4;
      ret->bytes_per_rela = sizeof (Elf32_External_Rela);
      ret->dynamic_interpreter = ELF32_DYNAMIC_INTERPRETER;
      ret->dynamic_interpreter_size = sizeof ELF32_DYNAMIC_INTERPRETER;
    }

  if (!_bfd_elf_link_hash_table_init (&ret->elf, abfd, link_hash_newfunc,
				      sizeof (struct _bfd_sparc_elf_link_hash_entry)))
    {
      free (ret);
      return NULL;
    }

  return &ret->elf.root;
}