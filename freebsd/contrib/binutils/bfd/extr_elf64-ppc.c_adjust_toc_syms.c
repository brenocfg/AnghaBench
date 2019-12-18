#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_8__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int value; TYPE_9__* section; } ;
struct TYPE_15__ {TYPE_5__ def; } ;
struct TYPE_13__ {int /*<<< orphan*/  string; } ;
struct TYPE_16__ {TYPE_6__ u; TYPE_4__ root; } ;
struct TYPE_17__ {TYPE_7__ root; } ;
struct ppc_link_hash_entry {int adjust_done; TYPE_8__ elf; } ;
struct TYPE_10__ {scalar_t__ link; } ;
struct TYPE_11__ {TYPE_1__ i; } ;
struct TYPE_12__ {scalar_t__ type; TYPE_2__ u; } ;
struct elf_link_hash_entry {TYPE_3__ root; } ;
struct adjust_toc_info {unsigned long* skip; int /*<<< orphan*/  global_toc_syms; TYPE_9__* toc; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;
struct TYPE_18__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__ bfd_abs_section ; 
 scalar_t__ bfd_link_hash_defined ; 
 scalar_t__ bfd_link_hash_defweak ; 
 scalar_t__ bfd_link_hash_indirect ; 
 scalar_t__ bfd_link_hash_warning ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
adjust_toc_syms (struct elf_link_hash_entry *h, void *inf)
{
  struct ppc_link_hash_entry *eh;
  struct adjust_toc_info *toc_inf = (struct adjust_toc_info *) inf;

  if (h->root.type == bfd_link_hash_indirect)
    return TRUE;

  if (h->root.type == bfd_link_hash_warning)
    h = (struct elf_link_hash_entry *) h->root.u.i.link;

  if (h->root.type != bfd_link_hash_defined
      && h->root.type != bfd_link_hash_defweak)
    return TRUE;

  eh = (struct ppc_link_hash_entry *) h;
  if (eh->adjust_done)
    return TRUE;

  if (eh->elf.root.u.def.section == toc_inf->toc)
    {
      unsigned long skip = toc_inf->skip[eh->elf.root.u.def.value >> 3];
      if (skip != (unsigned long) -1)
	eh->elf.root.u.def.value -= skip;
      else
	{
	  (*_bfd_error_handler)
	    (_("%s defined in removed toc entry"), eh->elf.root.root.string);
	  eh->elf.root.u.def.section = &bfd_abs_section;
	  eh->elf.root.u.def.value = 0;
	}
      eh->adjust_done = 1;
    }
  else if (strcmp (eh->elf.root.u.def.section->name, ".toc") == 0)
    toc_inf->global_toc_syms = TRUE;

  return TRUE;
}