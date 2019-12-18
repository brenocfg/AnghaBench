#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct elf_link_hash_entry {int /*<<< orphan*/  other; } ;
typedef  int /*<<< orphan*/  bfd_boolean ;

/* Variables and functions */
 scalar_t__ ELF_MIPS_IS_OPTIONAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 

bfd_boolean
_bfd_mips_elf_ignore_undef_symbol (struct elf_link_hash_entry *h)
{
  return ELF_MIPS_IS_OPTIONAL (h->other) ? TRUE : FALSE;
}