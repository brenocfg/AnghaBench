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
struct TYPE_2__ {scalar_t__ offset; } ;
struct elf_link_hash_entry {int /*<<< orphan*/  pointer_equality_needed; int /*<<< orphan*/  def_regular; TYPE_1__ plt; } ;
typedef  scalar_t__ bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  _bfd_elf_hash_symbol (struct elf_link_hash_entry*) ; 

__attribute__((used)) static bfd_boolean
elf64_x86_64_hash_symbol (struct elf_link_hash_entry *h)
{
  if (h->plt.offset != (bfd_vma) -1
      && !h->def_regular
      && !h->pointer_equality_needed)
    return FALSE;

  return _bfd_elf_hash_symbol (h);
}