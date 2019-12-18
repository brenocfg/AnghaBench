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
struct mips_elf_link_hash_table {int* dynsym_sec_strindex; TYPE_1__ root; scalar_t__ function_stub_size; scalar_t__ plt_entry_size; scalar_t__ plt_header_size; int /*<<< orphan*/ * splt; int /*<<< orphan*/ * sgotplt; int /*<<< orphan*/ * srelplt2; int /*<<< orphan*/ * srelplt; int /*<<< orphan*/ * sdynbss; int /*<<< orphan*/ * srelbss; void* is_vxworks; void* mips16_stubs_seen; scalar_t__ rld_value; void* use_rld_obj_head; scalar_t__ compact_rel_size; scalar_t__ procedure_count; } ;
struct mips_elf_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 void* FALSE ; 
 size_t SIZEOF_MIPS_DYNSYM_SECNAMES ; 
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct mips_elf_link_hash_table* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct mips_elf_link_hash_table*) ; 
 size_t i ; 
 int /*<<< orphan*/  mips_elf_link_hash_newfunc ; 

struct bfd_link_hash_table *
_bfd_mips_elf_link_hash_table_create (bfd *abfd)
{
  struct mips_elf_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct mips_elf_link_hash_table);

  ret = bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&ret->root, abfd,
				      mips_elf_link_hash_newfunc,
				      sizeof (struct mips_elf_link_hash_entry)))
    {
      free (ret);
      return NULL;
    }

#if 0
  /* We no longer use this.  */
  for (i = 0; i < SIZEOF_MIPS_DYNSYM_SECNAMES; i++)
    ret->dynsym_sec_strindex[i] = (bfd_size_type) -1;
#endif
  ret->procedure_count = 0;
  ret->compact_rel_size = 0;
  ret->use_rld_obj_head = FALSE;
  ret->rld_value = 0;
  ret->mips16_stubs_seen = FALSE;
  ret->is_vxworks = FALSE;
  ret->srelbss = NULL;
  ret->sdynbss = NULL;
  ret->srelplt = NULL;
  ret->srelplt2 = NULL;
  ret->sgotplt = NULL;
  ret->splt = NULL;
  ret->plt_header_size = 0;
  ret->plt_entry_size = 0;
  ret->function_stub_size = 0;

  return &ret->root.root;
}