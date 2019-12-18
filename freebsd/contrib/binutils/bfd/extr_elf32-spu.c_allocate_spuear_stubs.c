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
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct stubarr {int err; int count; int /*<<< orphan*/  stub_hash_table; } ;
struct spu_stub_hash_entry {int /*<<< orphan*/  target_off; int /*<<< orphan*/ * target_section; } ;
struct TYPE_6__ {int /*<<< orphan*/  value; int /*<<< orphan*/ * section; } ;
struct TYPE_7__ {TYPE_2__ def; } ;
struct TYPE_5__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ type; TYPE_3__ u; TYPE_1__ root; } ;
struct elf_link_hash_entry {TYPE_4__ root; scalar_t__ def_regular; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  Elf_Internal_Rela ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_hash_lookup (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 int /*<<< orphan*/  free (char*) ; 
 char* spu_stub_name (int /*<<< orphan*/ *,struct elf_link_hash_entry*,int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static bfd_boolean
allocate_spuear_stubs (struct elf_link_hash_entry *h, void *inf)
{
  /* Symbols starting with _SPUEAR_ need a stub because they may be
     invoked by the PPU.  */
  if ((h->root.type == bfd_link_hash_defined
       || h->root.type == bfd_link_hash_defweak)
      && h->def_regular
      && strncmp (h->root.root.string, "_SPUEAR_", 8) == 0)
    {
      struct stubarr *stubs = inf;
      static Elf_Internal_Rela zero_rel;
      char *stub_name = spu_stub_name (h->root.u.def.section, h, &zero_rel);
      struct spu_stub_hash_entry *sh;

      if (stub_name == NULL)
	{
	  stubs->err = 1;
	  return FALSE;
	}

      sh = (struct spu_stub_hash_entry *)
	bfd_hash_lookup (stubs->stub_hash_table, stub_name, TRUE, FALSE);
      if (sh == NULL)
	{
	  free (stub_name);
	  return FALSE;
	}

      /* If this entry isn't new, we already have a stub.  */
      if (sh->target_section != NULL)
	{
	  free (stub_name);
	  return TRUE;
	}

      sh->target_section = h->root.u.def.section;
      sh->target_off = h->root.u.def.value;
      stubs->count += 1;
    }
  
  return TRUE;
}