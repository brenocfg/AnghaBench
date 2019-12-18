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
struct internal_reloc {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
struct external_reloc {int /*<<< orphan*/  r_offset; int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PUT_RELOC_VADDR (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SWAP_OUT_RELOC_EXTRA (int /*<<< orphan*/ *,struct internal_reloc*,struct external_reloc*) ; 
 int /*<<< orphan*/  SWAP_OUT_RELOC_OFFSET (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 unsigned int bfd_coff_relsz (int /*<<< orphan*/ *) ; 

__attribute__((used)) static unsigned int
coff_swap_reloc_out (bfd * abfd, void * src, void * dst)
{
  struct internal_reloc *reloc_src = (struct internal_reloc *) src;
  struct external_reloc *reloc_dst = (struct external_reloc *) dst;

  PUT_RELOC_VADDR (abfd, reloc_src->r_vaddr, reloc_dst->r_vaddr);
  H_PUT_32 (abfd, reloc_src->r_symndx, reloc_dst->r_symndx);
  H_PUT_16 (abfd, reloc_src->r_type, reloc_dst->r_type);

#ifdef SWAP_OUT_RELOC_OFFSET
  SWAP_OUT_RELOC_OFFSET (abfd, reloc_src->r_offset, reloc_dst->r_offset);
#endif
#ifdef SWAP_OUT_RELOC_EXTRA
  SWAP_OUT_RELOC_EXTRA (abfd, reloc_src, reloc_dst);
#endif

  return bfd_coff_relsz (abfd);
}