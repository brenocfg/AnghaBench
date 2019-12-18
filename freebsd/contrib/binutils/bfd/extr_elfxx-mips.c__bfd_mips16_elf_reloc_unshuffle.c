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
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  scalar_t__ bfd_boolean ;
typedef  int /*<<< orphan*/  bfd ;

/* Variables and functions */
 int R_MIPS16_26 ; 
 int R_MIPS16_GPREL ; 
 int R_MIPS16_HI16 ; 
 int R_MIPS16_LO16 ; 
 int bfd_get_16 (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_put_32 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

void
_bfd_mips16_elf_reloc_unshuffle (bfd *abfd, int r_type,
				 bfd_boolean jal_shuffle, bfd_byte *data)
{
  bfd_vma extend, insn, val;

  if (r_type != R_MIPS16_26 && r_type != R_MIPS16_GPREL
      && r_type != R_MIPS16_HI16 && r_type != R_MIPS16_LO16)
    return;

  /* Pick up the mips16 extend instruction and the real instruction.  */
  extend = bfd_get_16 (abfd, data);
  insn = bfd_get_16 (abfd, data + 2);
  if (r_type == R_MIPS16_26)
    {
      if (jal_shuffle)
	val = ((extend & 0xfc00) << 16) | ((extend & 0x3e0) << 11)
	      | ((extend & 0x1f) << 21) | insn;
      else
	val = extend << 16 | insn;
    }
  else
    val = ((extend & 0xf800) << 16) | ((insn & 0xffe0) << 11)
	  | ((extend & 0x1f) << 11) | (extend & 0x7e0) | (insn & 0x1f);
  bfd_put_32 (abfd, val, data);
}