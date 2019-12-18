#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ string; } ;
struct TYPE_8__ {int /*<<< orphan*/ * abfd; } ;
struct TYPE_9__ {TYPE_1__ undef; } ;
struct TYPE_11__ {TYPE_3__ root; TYPE_2__ u; } ;
struct TYPE_12__ {scalar_t__ non_elf; TYPE_4__ root; } ;
struct ppc_link_hash_entry {int fake; int is_func_descriptor; int is_func; struct ppc_link_hash_entry* oh; TYPE_5__ elf; } ;
struct bfd_link_info {int dummy; } ;
struct bfd_link_hash_entry {int dummy; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_13__ {scalar_t__ value; int /*<<< orphan*/  section; int /*<<< orphan*/  flags; scalar_t__ name; } ;
typedef  TYPE_6__ asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  BSF_WEAK ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_generic_link_add_one_symbol (struct bfd_link_info*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bfd_link_hash_entry**) ; 
 TYPE_6__* bfd_make_empty_symbol (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_und_section_ptr ; 

__attribute__((used)) static struct ppc_link_hash_entry *
make_fdh (struct bfd_link_info *info,
	  struct ppc_link_hash_entry *fh)
{
  bfd *abfd;
  asymbol *newsym;
  struct bfd_link_hash_entry *bh;
  struct ppc_link_hash_entry *fdh;

  abfd = fh->elf.root.u.undef.abfd;
  newsym = bfd_make_empty_symbol (abfd);
  newsym->name = fh->elf.root.root.string + 1;
  newsym->section = bfd_und_section_ptr;
  newsym->value = 0;
  newsym->flags = BSF_WEAK;

  bh = NULL;
  if (!_bfd_generic_link_add_one_symbol (info, abfd, newsym->name,
					 newsym->flags, newsym->section,
					 newsym->value, NULL, FALSE, FALSE,
					 &bh))
    return NULL;

  fdh = (struct ppc_link_hash_entry *) bh;
  fdh->elf.non_elf = 0;
  fdh->fake = 1;
  fdh->is_func_descriptor = 1;
  fdh->oh = fh;
  fh->is_func = 1;
  fh->oh = fdh;
  return fdh;
}