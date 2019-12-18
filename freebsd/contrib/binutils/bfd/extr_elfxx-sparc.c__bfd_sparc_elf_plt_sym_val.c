#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int bfd_vma ;
struct TYPE_5__ {int vma; int /*<<< orphan*/  owner; } ;
typedef  TYPE_1__ asection ;
struct TYPE_6__ {int address; } ;
typedef  TYPE_2__ arelent ;

/* Variables and functions */
 scalar_t__ ABI_64_P (int /*<<< orphan*/ ) ; 
 int PLT64_ENTRY_SIZE ; 
 int PLT64_HEADER_SIZE ; 
 int PLT64_LARGE_THRESHOLD ; 

bfd_vma
_bfd_sparc_elf_plt_sym_val (bfd_vma i, const asection *plt, const arelent *rel)
{
  if (ABI_64_P (plt->owner))
    {
      bfd_vma j;

      i += PLT64_HEADER_SIZE / PLT64_ENTRY_SIZE;
      if (i < PLT64_LARGE_THRESHOLD)
	return plt->vma + i * PLT64_ENTRY_SIZE;

      j = (i - PLT64_LARGE_THRESHOLD) % 160;
      i -= j;
      return plt->vma + i * PLT64_ENTRY_SIZE + j * 4 * 6;
    }
  else
    return rel->address;
}