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
struct internal_reloc {int r_type; int r_offset; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
struct external_reloc {int /*<<< orphan*/  r_type; int /*<<< orphan*/  r_symndx; int /*<<< orphan*/  r_vaddr; } ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int /*<<< orphan*/  H_PUT_16 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  H_PUT_32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int MIPS_R_PAIR ; 
#define  MIPS_R_REFHI 129 
#define  MIPS_R_REFLO 128 
 unsigned int RELSZ ; 

__attribute__((used)) static unsigned int
mips_swap_reloc_out (bfd * abfd, void * src, void * dst)
{
  static int prev_offset = 1;
  static bfd_vma prev_addr = 0;
  struct internal_reloc *reloc_src = (struct internal_reloc *)src;
  struct external_reloc *reloc_dst = (struct external_reloc *)dst;

  switch (reloc_src->r_type)
    {
    case MIPS_R_REFHI:
      prev_addr = reloc_src->r_vaddr;
      prev_offset = reloc_src->r_offset;
      break;
    case MIPS_R_REFLO:
      if (reloc_src->r_vaddr == prev_addr)
	{
	  /* FIXME: only slightly hackish.  If we see a REFLO pointing to
	     the same address as a REFHI, we assume this is the matching
	     PAIR reloc and output it accordingly.  The symndx is really
	     the low 16 bits of the addend */
	  H_PUT_32 (abfd, reloc_src->r_vaddr, reloc_dst->r_vaddr);
	  H_PUT_32 (abfd, reloc_src->r_symndx, reloc_dst->r_symndx);
	  H_PUT_16 (abfd, MIPS_R_PAIR, reloc_dst->r_type);
	  return RELSZ;
	}
      break;
    }

  H_PUT_32 (abfd, reloc_src->r_vaddr, reloc_dst->r_vaddr);
  H_PUT_32 (abfd, reloc_src->r_symndx, reloc_dst->r_symndx);

  H_PUT_16 (abfd, reloc_src->r_type, reloc_dst->r_type);
  return RELSZ;
}