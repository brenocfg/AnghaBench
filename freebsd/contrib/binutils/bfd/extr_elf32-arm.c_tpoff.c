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
struct elf_link_hash_table {TYPE_1__* tls_sec; } ;
struct bfd_link_info {int dummy; } ;
typedef  scalar_t__ bfd_vma ;
struct TYPE_2__ {scalar_t__ vma; int /*<<< orphan*/  alignment_power; } ;

/* Variables and functions */
 scalar_t__ TCB_SIZE ; 
 scalar_t__ align_power (scalar_t__,int /*<<< orphan*/ ) ; 
 struct elf_link_hash_table* elf_hash_table (struct bfd_link_info*) ; 

__attribute__((used)) static bfd_vma
tpoff (struct bfd_link_info *info, bfd_vma address)
{
  struct elf_link_hash_table *htab = elf_hash_table (info);
  bfd_vma base;

  /* If tls_sec is NULL, we should have signalled an error already.  */
  if (htab->tls_sec == NULL)
    return 0;
  base = align_power ((bfd_vma) TCB_SIZE, htab->tls_sec->alignment_power);
  return address - htab->tls_sec->vma + base;
}