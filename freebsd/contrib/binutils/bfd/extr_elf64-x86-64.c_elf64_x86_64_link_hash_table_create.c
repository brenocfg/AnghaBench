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
struct bfd_link_hash_table {int dummy; } ;
struct TYPE_6__ {struct bfd_link_hash_table root; } ;
struct TYPE_5__ {scalar_t__ refcount; } ;
struct TYPE_4__ {int /*<<< orphan*/ * abfd; } ;
struct elf64_x86_64_link_hash_table {TYPE_3__ elf; scalar_t__ sgotplt_jump_table_size; TYPE_2__ tls_ld_got; scalar_t__ tlsdesc_got; scalar_t__ tlsdesc_plt; TYPE_1__ sym_sec; int /*<<< orphan*/ * srelbss; int /*<<< orphan*/ * sdynbss; int /*<<< orphan*/ * srelplt; int /*<<< orphan*/ * splt; int /*<<< orphan*/ * srelgot; int /*<<< orphan*/ * sgotplt; int /*<<< orphan*/ * sgot; } ;
struct elf64_x86_64_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct elf64_x86_64_link_hash_table*) ; 
 int /*<<< orphan*/  link_hash_newfunc ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf64_x86_64_link_hash_table_create (bfd *abfd)
{
  struct elf64_x86_64_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct elf64_x86_64_link_hash_table);

  ret = (struct elf64_x86_64_link_hash_table *) bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&ret->elf, abfd, link_hash_newfunc,
				      sizeof (struct elf64_x86_64_link_hash_entry)))
    {
      free (ret);
      return NULL;
    }

  ret->sgot = NULL;
  ret->sgotplt = NULL;
  ret->srelgot = NULL;
  ret->splt = NULL;
  ret->srelplt = NULL;
  ret->sdynbss = NULL;
  ret->srelbss = NULL;
  ret->sym_sec.abfd = NULL;
  ret->tlsdesc_plt = 0;
  ret->tlsdesc_got = 0;
  ret->tls_ld_got.refcount = 0;
  ret->sgotplt_jump_table_size = 0;

  return &ret->elf.root;
}