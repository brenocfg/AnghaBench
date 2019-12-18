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
struct internal_reloc {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_2__ {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
typedef  TYPE_1__ RELOC ;

/* Variables and functions */
 int /*<<< orphan*/  GET_RELOC_VADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_GET_S32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_IN_RELOC_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
coff_swap_reloc_in (bfd * abfd, void * src, void * dst)
{
  RELOC *reloc_src = (RELOC *) src;
  struct internal_reloc *reloc_dst = (struct internal_reloc *) dst;

  reloc_dst->r_vaddr  = GET_RELOC_VADDR (abfd, reloc_src->r_vaddr);
  reloc_dst->r_symndx = H_GET_S32 (abfd, reloc_src->r_symndx);
  reloc_dst->r_type   = H_GET_16 (abfd, reloc_src->r_type);

#ifdef SWAP_IN_RELOC_OFFSET
  reloc_dst->r_offset = SWAP_IN_RELOC_OFFSET (abfd, reloc_src->r_offset);
#endif
}