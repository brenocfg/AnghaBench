#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* section; } ;
struct TYPE_7__ {scalar_t__ link; } ;
struct TYPE_11__ {TYPE_4__ def; TYPE_1__ i; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_5__ u; } ;
struct elf_link_hash_entry {TYPE_6__ root; } ;
struct elf_gc_sweep_symbol_info {int /*<<< orphan*/  info; int /*<<< orphan*/  (* hide_symbol ) (int /*<<< orphan*/ ,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_9__ {TYPE_2__* owner; int /*<<< orphan*/  gc_mark; } ;
struct TYPE_8__ {int flags; } ;

/* Variables and functions */
 int DYNAMIC ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_warning ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,struct elf_link_hash_entry*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
elf_gc_sweep_symbol (struct elf_link_hash_entry *h, void *data)
{
  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if ((h->root.type == bfd_link_hash_defined
       || h->root.type == bfd_link_hash_defweak)
      && !h->root.u.def.section->gc_mark
      && !(h->root.u.def.section->owner->flags & DYNAMIC))
    {
      struct elf_gc_sweep_symbol_info *inf = data;
      (*inf->hide_symbol) (inf->info, h, TRUE);
    }

  return TRUE;
}