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
struct internal_reloc {int r_symndx; int r_type; int r_offset; scalar_t__ r_extern; scalar_t__ r_size; int /*<<< orphan*/  r_vaddr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
typedef  TYPE_1__ RELOC ;

/* Variables and functions */
 int H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int H_GET_S32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  MIPS_R_PAIR 129 
#define  MIPS_R_REFHI 128 

__attribute__((used)) static void
mips_swap_reloc_in (bfd * abfd, void * src, void * dst)
{
  static struct internal_reloc pair_prev;
  RELOC *reloc_src = (RELOC *) src;
  struct internal_reloc *reloc_dst = (struct internal_reloc *) dst;

  reloc_dst->r_vaddr = H_GET_32 (abfd, reloc_src->r_vaddr);
  reloc_dst->r_symndx = H_GET_S32 (abfd, reloc_src->r_symndx);
  reloc_dst->r_type = H_GET_16 (abfd, reloc_src->r_type);
  reloc_dst->r_size = 0;
  reloc_dst->r_extern = 0;
  reloc_dst->r_offset = 0;

  switch (reloc_dst->r_type)
  {
  case MIPS_R_REFHI:
    pair_prev = *reloc_dst;
    break;
  case MIPS_R_PAIR:
    reloc_dst->r_offset = reloc_dst->r_symndx;
    if (reloc_dst->r_offset & 0x8000)
      reloc_dst->r_offset -= 0x10000;
    reloc_dst->r_symndx = pair_prev.r_symndx;
    break;
  }
}