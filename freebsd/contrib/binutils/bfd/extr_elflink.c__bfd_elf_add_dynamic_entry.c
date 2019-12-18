#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_table {int /*<<< orphan*/  dynobj; } ;
struct elf_backend_data {TYPE_2__* s; } ;
struct bfd_link_info {int dummy; } ;
typedef  void* bfd_vma ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {int size; int /*<<< orphan*/ * contents; } ;
typedef  TYPE_3__ asection ;
struct TYPE_7__ {void* d_val; } ;
struct TYPE_10__ {TYPE_1__ d_un; void* d_tag; } ;
struct TYPE_8__ {int sizeof_dyn; int /*<<< orphan*/  (* swap_dyn_out ) (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_4__ Elf_Internal_Dyn ;

/* Variables and functions */
 int /*<<< orphan*/  BFD_ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* bfd_get_section_by_name (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * bfd_realloc (int /*<<< orphan*/ *,int) ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 
 struct elf_backend_data* get_elf_backend_data (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  is_elf_hash_table (struct elf_link_hash_table*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ *) ; 

bfd_boolean
_bfd_elf_add_dynamic_entry (struct bfd_link_info *info,
			    bfd_vma tag,
			    bfd_vma val)
{
  struct elf_link_hash_table *hash_table;
  const struct elf_backend_data *bed;
  asection *s;
  bfd_size_type newsize;
  bfd_byte *newcontents;
  Elf_Internal_Dyn dyn;

  hash_table = elf_hash_table (info);
  if (! is_elf_hash_table (hash_table))
    return FALSE;

  bed = get_elf_backend_data (hash_table->dynobj);
  s = bfd_get_section_by_name (hash_table->dynobj, ".dynamic");
  BFD_ASSERT (s != NULL);

  newsize = s->size + bed->s->sizeof_dyn;
  newcontents = bfd_realloc (s->contents, newsize);
  if (newcontents == NULL)
    return FALSE;

  dyn.d_tag = tag;
  dyn.d_un.d_val = val;
  bed->s->swap_dyn_out (hash_table->dynobj, &dyn, newcontents + s->size);

  s->size = newsize;
  s->contents = newcontents;

  return TRUE;
}