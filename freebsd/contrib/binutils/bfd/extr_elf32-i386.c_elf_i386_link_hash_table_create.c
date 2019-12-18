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
struct TYPE_5__ {int /*<<< orphan*/ * abfd; } ;
struct TYPE_4__ {scalar_t__ refcount; } ;
struct elf_i386_link_hash_table {TYPE_3__ elf; scalar_t__ plt0_pad_byte; int /*<<< orphan*/ * srelplt2; scalar_t__ is_vxworks; TYPE_2__ sym_sec; scalar_t__ sgotplt_jump_table_size; scalar_t__ next_tls_desc_index; TYPE_1__ tls_ldm_got; int /*<<< orphan*/ * srelbss; int /*<<< orphan*/ * sdynbss; int /*<<< orphan*/ * srelplt; int /*<<< orphan*/ * splt; int /*<<< orphan*/ * srelgot; int /*<<< orphan*/ * sgotplt; int /*<<< orphan*/ * sgot; } ;
struct elf_i386_link_hash_entry {int dummy; } ;
typedef  int bfd_size_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  _bfd_elf_link_hash_table_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 struct elf_i386_link_hash_table* bfd_malloc (int) ; 
 int /*<<< orphan*/  free (struct elf_i386_link_hash_table*) ; 
 int /*<<< orphan*/  link_hash_newfunc ; 

__attribute__((used)) static struct bfd_link_hash_table *
elf_i386_link_hash_table_create (bfd *abfd)
{
  struct elf_i386_link_hash_table *ret;
  bfd_size_type amt = sizeof (struct elf_i386_link_hash_table);

  ret = bfd_malloc (amt);
  if (ret == NULL)
    return NULL;

  if (!_bfd_elf_link_hash_table_init (&ret->elf, abfd, link_hash_newfunc,
				      sizeof (struct elf_i386_link_hash_entry)))
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
  ret->tls_ldm_got.refcount = 0;
  ret->next_tls_desc_index = 0;
  ret->sgotplt_jump_table_size = 0;
  ret->sym_sec.abfd = NULL;
  ret->is_vxworks = 0;
  ret->srelplt2 = NULL;
  ret->plt0_pad_byte = 0;

  return &ret->elf.root;
}