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
struct ppc_stub_hash_entry {int dummy; } ;
struct bfd_link_hash_table {int dummy; } ;
struct TYPE_9__ {int /*<<< orphan*/ * glist; scalar_t__ offset; } ;
struct TYPE_8__ {int /*<<< orphan*/ * glist; scalar_t__ offset; } ;
struct TYPE_7__ {int /*<<< orphan*/ * glist; scalar_t__ refcount; } ;
struct TYPE_6__ {int /*<<< orphan*/ * glist; scalar_t__ refcount; } ;
struct TYPE_10__ {struct bfd_link_hash_table root; TYPE_4__ init_plt_offset; TYPE_3__ init_got_offset; TYPE_2__ init_plt_refcount; TYPE_1__ init_got_refcount; } ;
struct ppc_link_hash_table {TYPE_5__ elf; int /*<<< orphan*/  branch_hash_table; int /*<<< orphan*/  stub_hash_table; } ;
struct ppc_link_hash_entry {int dummy; } ;
struct ppc_branch_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_5__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  bfd_hash_table_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct ppc_link_hash_table* bfd_zmalloc (int) ; 
 int /*<<< orphan*/  branch_hash_newfunc ; 
 int /*<<< orphan*/  free (struct ppc_link_hash_table*) ; 
 int /*<<< orphan*/  link_hash_newfunc ; 
 int /*<<< orphan*/  stub_hash_newfunc ; 

__attribute__((used)) static struct bfd_link_hash_table *
ppc64_elf_link_hash_table_create (bfd *abfd)
{
  struct ppc_link_hash_table *htab;
  bfd_size_type amt = sizeof (struct ppc_link_hash_table);

  htab = bfd_zmalloc (amt);
  if (htab == NULL)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&htab->elf, abfd, link_hash_newfunc,
				      sizeof (struct ppc_link_hash_entry)))
    {
      free (htab);
      return NULL;
    }

  /* Init the stub hash table too.  */
  if (!bfd_hash_table_init (&htab->stub_hash_table, stub_hash_newfunc,
			    sizeof (struct ppc_stub_hash_entry)))
    return NULL;

  /* And the branch hash table.  */
  if (!bfd_hash_table_init (&htab->branch_hash_table, branch_hash_newfunc,
			    sizeof (struct ppc_branch_hash_entry)))
    return NULL;

  /* Initializing two fields of the union is just cosmetic.  We really
     only care about glist, but when compiled on a 32-bit host the
     bfd_vma fields are larger.  Setting the bfd_vma to zero makes
     debugger inspection of these fields look nicer.  */
  htab->elf.init_got_refcount.refcount = 0;
  htab->elf.init_got_refcount.glist = NULL;
  htab->elf.init_plt_refcount.refcount = 0;
  htab->elf.init_plt_refcount.glist = NULL;
  htab->elf.init_got_offset.offset = 0;
  htab->elf.init_got_offset.glist = NULL;
  htab->elf.init_plt_offset.offset = 0;
  htab->elf.init_plt_offset.glist = NULL;

  return &htab->elf.root;
}