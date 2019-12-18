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
struct TYPE_2__ {int ifd; } ;
struct mips_elf_link_hash_entry {int /*<<< orphan*/  tls_type; void* is_relocation_target; void* is_branch_target; void* forced_local; int /*<<< orphan*/ * call_fp_stub; int /*<<< orphan*/ * call_stub; void* need_fn_stub; int /*<<< orphan*/ * fn_stub; void* no_fn_stub; void* readonly_reloc; scalar_t__ possibly_dynamic_relocs; TYPE_1__ esym; } ;
struct bfd_hash_table {int dummy; } ;
struct bfd_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  EXTR ;

/* Variables and functions */
 void* FALSE ; 
 int /*<<< orphan*/  GOT_NORMAL ; 
 scalar_t__ _bfd_elf_link_hash_newfunc (struct bfd_hash_entry*,struct bfd_hash_table*,char const*) ; 
 struct mips_elf_link_hash_entry* bfd_hash_allocate (struct bfd_hash_table*,int) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static struct bfd_hash_entry *
mips_elf_link_hash_newfunc (struct bfd_hash_entry *entry,
			    struct bfd_hash_table *table, const char *string)
{
  struct mips_elf_link_hash_entry *ret =
    (struct mips_elf_link_hash_entry *) entry;

  /* Allocate the structure if it has not already been allocated by a
     subclass.  */
  if (ret == NULL)
    ret = bfd_hash_allocate (table, sizeof (struct mips_elf_link_hash_entry));
  if (ret == NULL)
    return (struct bfd_hash_entry *) ret;

  /* Call the allocation method of the superclass.  */
  ret = ((struct mips_elf_link_hash_entry *)
	 _bfd_elf_link_hash_newfunc ((struct bfd_hash_entry *) ret,
				     table, string));
  if (ret != NULL)
    {
      /* Set local fields.  */
      memset (&ret->esym, 0, sizeof (EXTR));
      /* We use -2 as a marker to indicate that the information has
	 not been set.  -1 means there is no associated ifd.  */
      ret->esym.ifd = -2;
      ret->possibly_dynamic_relocs = 0;
      ret->readonly_reloc = FALSE;
      ret->no_fn_stub = FALSE;
      ret->fn_stub = NULL;
      ret->need_fn_stub = FALSE;
      ret->call_stub = NULL;
      ret->call_fp_stub = NULL;
      ret->forced_local = FALSE;
      ret->is_branch_target = FALSE;
      ret->is_relocation_target = FALSE;
      ret->tls_type = GOT_NORMAL;
    }

  return (struct bfd_hash_entry *) ret;
}