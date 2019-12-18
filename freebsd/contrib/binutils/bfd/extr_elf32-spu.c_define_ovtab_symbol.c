#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct spu_link_hash_table {TYPE_1__* ovtab; int /*<<< orphan*/  elf; } ;
struct TYPE_9__ {int /*<<< orphan*/  string; } ;
struct TYPE_7__ {TYPE_1__* section; } ;
struct TYPE_8__ {TYPE_2__ def; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_4__ root; TYPE_3__ u; } ;
struct elf_link_hash_entry {int def_regular; int ref_regular; int ref_regular_nonweak; TYPE_5__ root; scalar_t__ non_elf; int /*<<< orphan*/  type; } ;
struct TYPE_6__ {int /*<<< orphan*/  owner; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  STT_OBJECT ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  _bfd_error_handler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bfd_error_bad_value ; 
 scalar_t__ bfd_link_hash_defined ; 
 int /*<<< orphan*/  bfd_set_error (int /*<<< orphan*/ ) ; 
 struct elf_link_hash_entry* elf_link_hash_lookup (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct elf_link_hash_entry *
define_ovtab_symbol (struct spu_link_hash_table *htab, const char *name)
{
  struct elf_link_hash_entry *h;

  h = elf_link_hash_lookup (&htab->elf, name, TRUE, FALSE, FALSE);
  if (h == NULL)
    return NULL;

  if (h->root.type != bfd_link_hash_defined
      || !h->def_regular)
    {
      h->root.type = bfd_link_hash_defined;
      h->root.u.def.section = htab->ovtab;
      h->type = STT_OBJECT;
      h->ref_regular = 1;
      h->def_regular = 1;
      h->ref_regular_nonweak = 1;
      h->non_elf = 0;
    }
  else
    {
      (*_bfd_error_handler) (_("%B is not allowed to define %s"),
			     h->root.u.def.section->owner,
			     h->root.root.string);
      bfd_set_error (bfd_error_bad_value);
      return NULL;
    }

  return h;
}