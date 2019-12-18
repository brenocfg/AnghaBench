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
typedef  enum elf_spu_reloc_type { ____Placeholder_elf_spu_reloc_type } elf_spu_reloc_type ;
typedef  int bfd_reloc_code_real_type ;

/* Variables and functions */
#define  BFD_RELOC_32 143 
#define  BFD_RELOC_32_PCREL 142 
#define  BFD_RELOC_SPU_HI16 141 
#define  BFD_RELOC_SPU_IMM10 140 
#define  BFD_RELOC_SPU_IMM10W 139 
#define  BFD_RELOC_SPU_IMM16 138 
#define  BFD_RELOC_SPU_IMM16W 137 
#define  BFD_RELOC_SPU_IMM18 136 
#define  BFD_RELOC_SPU_IMM7 135 
#define  BFD_RELOC_SPU_IMM8 134 
#define  BFD_RELOC_SPU_LO16 133 
#define  BFD_RELOC_SPU_PCREL16 132 
#define  BFD_RELOC_SPU_PCREL9a 131 
#define  BFD_RELOC_SPU_PCREL9b 130 
#define  BFD_RELOC_SPU_PPU32 129 
#define  BFD_RELOC_SPU_PPU64 128 
 int R_SPU_ADDR10 ; 
 int R_SPU_ADDR10I ; 
 int R_SPU_ADDR16 ; 
 int R_SPU_ADDR16I ; 
 int R_SPU_ADDR16_HI ; 
 int R_SPU_ADDR16_LO ; 
 int R_SPU_ADDR18 ; 
 int R_SPU_ADDR32 ; 
 int R_SPU_ADDR7 ; 
 int R_SPU_NONE ; 
 int R_SPU_PPU32 ; 
 int R_SPU_PPU64 ; 
 int R_SPU_REL16 ; 
 int R_SPU_REL32 ; 
 int R_SPU_REL9 ; 
 int R_SPU_REL9I ; 

__attribute__((used)) static enum elf_spu_reloc_type
spu_elf_bfd_to_reloc_type (bfd_reloc_code_real_type code)
{
  switch (code)
    {
    default:
      return R_SPU_NONE;
    case BFD_RELOC_SPU_IMM10W:
      return R_SPU_ADDR10;
    case BFD_RELOC_SPU_IMM16W:
      return R_SPU_ADDR16;
    case BFD_RELOC_SPU_LO16:
      return R_SPU_ADDR16_LO;
    case BFD_RELOC_SPU_HI16:
      return R_SPU_ADDR16_HI;
    case BFD_RELOC_SPU_IMM18:
      return R_SPU_ADDR18;
    case BFD_RELOC_SPU_PCREL16:
      return R_SPU_REL16;
    case BFD_RELOC_SPU_IMM7:
      return R_SPU_ADDR7;
    case BFD_RELOC_SPU_IMM8:
      return R_SPU_NONE;
    case BFD_RELOC_SPU_PCREL9a:
      return R_SPU_REL9;
    case BFD_RELOC_SPU_PCREL9b:
      return R_SPU_REL9I;
    case BFD_RELOC_SPU_IMM10:
      return R_SPU_ADDR10I;
    case BFD_RELOC_SPU_IMM16:
      return R_SPU_ADDR16I;
    case BFD_RELOC_32:
      return R_SPU_ADDR32;
    case BFD_RELOC_32_PCREL:
      return R_SPU_REL32;
    case BFD_RELOC_SPU_PPU32:
      return R_SPU_PPU32;
    case BFD_RELOC_SPU_PPU64:
      return R_SPU_PPU64;
    }
}