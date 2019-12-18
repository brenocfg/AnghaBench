#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_table {int /*<<< orphan*/  dynobj; } ;
struct TYPE_4__ {scalar_t__ link; } ;
struct TYPE_5__ {TYPE_1__ i; } ;
struct TYPE_6__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; int /*<<< orphan*/  def_regular; int /*<<< orphan*/  type; int /*<<< orphan*/  other; scalar_t__ forced_local; TYPE_3__ root; } ;
struct elf_backend_data {int /*<<< orphan*/  (* is_function_type ) (int /*<<< orphan*/ ) ;} ;
struct bfd_link_info {scalar_t__ executable; } ;
typedef  int bfd_boolean ;

/* Variables and functions */
 int ELF_ST_VISIBILITY (int /*<<< orphan*/ ) ; 
 int FALSE ; 
#define  STV_HIDDEN 130 
#define  STV_INTERNAL 129 
#define  STV_PROTECTED 128 
 scalar_t__ SYMBOLIC_BIND (struct bfd_link_info*,struct elf_link_hash_entry*) ; 
 int TRUE ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_elf_hash_table (struct elf_link_hash_table*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_elf_dynamic_symbol_p (struct elf_link_hash_entry *h,
			   struct bfd_link_info *info,
			   bfd_boolean ignore_protected)
{
  bfd_boolean binding_stays_local_p;
  const struct elf_backend_data *bed;
  struct elf_link_hash_table *hash_table;

  if (h == NULL)
    return FALSE;

  while (h->root.type == bfd_link_hash_indirect
	 || h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  /* If it was forced local, then clearly it's not dynamic.  */
  if (h->dynindx == -1)
    return FALSE;
  if (h->forced_local)
    return FALSE;

  /* Identify the cases where name binding rules say that a
     visible symbol resolves locally.  */
  binding_stays_local_p = info->executable || SYMBOLIC_BIND (info, h);

  switch (ELF_ST_VISIBILITY (h->other))
    {
    case STV_INTERNAL:
    case STV_HIDDEN:
      return FALSE;

    case STV_PROTECTED:
      hash_table = elf_hash_table (info);
      if (!is_elf_hash_table (hash_table))
	return FALSE;

      bed = get_elf_backend_data (hash_table->dynobj);

      /* Proper resolution for function pointer equality may require
	 that these symbols perhaps be resolved dynamically, even though
	 we should be resolving them to the current module.  */
      if (!ignore_protected || !bed->is_function_type (h->type))
	binding_stays_local_p = TRUE;
      break;

    default:
      break;
    }

  /* If it isn't defined locally, then clearly it's dynamic.  */
  if (!h->def_regular)
    return TRUE;

  /* Otherwise, the symbol is dynamic if binding rules don't tell
     us that it remains local.  */
  return !binding_stays_local_p;
}