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
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int bfd_get_32 (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,void*) ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_overflow ; 

__attribute__((used)) static bfd_reloc_status_type
elf32_arm_abs12_reloc (bfd *abfd, void *data, bfd_vma value)
{
  if (value > 0xfff)
    return bfd_reloc_overflow;

  value |= bfd_get_32 (abfd, data) & 0xfffff000;
  bfd_put_32 (abfd, value, data);
  return bfd_reloc_ok;
}