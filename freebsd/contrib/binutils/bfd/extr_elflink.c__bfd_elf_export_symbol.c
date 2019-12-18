#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_7__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  string; } ;
struct TYPE_8__ {scalar_t__ link; } ;
struct TYPE_9__ {TYPE_1__ i; } ;
struct TYPE_11__ {scalar_t__ type; TYPE_3__ root; TYPE_2__ u; } ;
struct elf_link_hash_entry {int dynindx; TYPE_4__ root; scalar_t__ ref_regular; scalar_t__ def_regular; int /*<<< orphan*/  dynamic; } ;
struct elf_info_failed {int /*<<< orphan*/  failed; TYPE_7__* info; struct bfd_elf_version_tree* verdefs; } ;
struct TYPE_12__ {int /*<<< orphan*/ * list; } ;
struct bfd_elf_version_tree {TYPE_5__ locals; struct bfd_elf_version_expr* (* match ) (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ;TYPE_5__ globals; struct bfd_elf_version_tree* next; } ;
struct bfd_elf_version_expr {int dummy; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_13__ {int /*<<< orphan*/  export_dynamic; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bfd_elf_link_record_dynamic_symbol (TYPE_7__*,struct elf_link_hash_entry*) ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 struct bfd_elf_version_expr* stub1 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct bfd_elf_version_expr* stub2 (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bfd_boolean
_bfd_elf_export_symbol (struct elf_link_hash_entry *h, void *data)
{
  struct elf_info_failed *eif = data;

  /* Ignore this if we won't export it.  */
  if (!eif->info->export_dynamic && !h->dynamic)
    return TRUE;

  /* Ignore indirect symbols.  These are added by the versioning code.  */
  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if (h->dynindx == -1
      && (h->def_regular
	  || h->ref_regular))
    {
      struct bfd_elf_version_tree *t;
      struct bfd_elf_version_expr *d;

      for (t = eif->verdefs; t != NULL; t = t->next)
	{
	  if (t->globals.list != NULL)
	    {
	      d = (*t->match) (&t->globals, NULL, h->root.root.string);
	      if (d != NULL)
		goto doit;
	    }

	  if (t->locals.list != NULL)
	    {
	      d = (*t->match) (&t->locals, NULL, h->root.root.string);
	      if (d != NULL)
		return TRUE;
	    }
	}

      if (!eif->verdefs)
	{
	doit:
	  if (! bfd_elf_link_record_dynamic_symbol (eif->info, h))
	    {
	      eif->failed = TRUE;
	      return FALSE;
	    }
	}
    }

  return TRUE;
}