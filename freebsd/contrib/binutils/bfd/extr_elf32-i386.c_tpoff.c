#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct elf_link_hash_table {TYPE_1__* tls_sec; scalar_t__ tls_size; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_2__ {scalar_t__ vma; } ;

/* Variables and functions */
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_vma
tpoff (struct bfd_link_info *info, bfd_vma address)
{
  struct elf_link_hash_table *htab = elf_hash_table (info);

  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (htab->tls_sec == NULL)
    return 0;
  return htab->tls_size + htab->tls_sec->vma - address;
}