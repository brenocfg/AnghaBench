#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int type; scalar_t__ pc_relative; } ;
typedef  TYPE_2__ reloc_howto_type ;
typedef  int bfd_vma ;
typedef  int /*<<< orphan*/  bfd_reloc_status_type ;
typedef  int /*<<< orphan*/  bfd_byte ;
typedef  int /*<<< orphan*/  bfd ;
struct TYPE_10__ {int output_offset; TYPE_1__* output_section; } ;
typedef  TYPE_3__ asection ;
struct TYPE_11__ {int r_offset; int r_addend; } ;
struct TYPE_8__ {int vma; } ;
typedef  TYPE_4__ Elf_Internal_Rela ;

/* Variables and functions */
#define  R_MEP_16 147 
#define  R_MEP_32 146 
#define  R_MEP_8 145 
#define  R_MEP_ADDR24A4 144 
#define  R_MEP_GNU_VTENTRY 143 
#define  R_MEP_GNU_VTINHERIT 142 
#define  R_MEP_GPREL 141 
#define  R_MEP_HI16S 140 
#define  R_MEP_HI16U 139 
#define  R_MEP_LOW16 138 
#define  R_MEP_PCABS24A2 137 
#define  R_MEP_PCREL12A2 136 
#define  R_MEP_PCREL17A2 135 
#define  R_MEP_PCREL24A2 134 
#define  R_MEP_PCREL8A2 133 
#define  R_MEP_TPREL 132 
#define  R_MEP_TPREL7 131 
#define  R_MEP_TPREL7A2 130 
#define  R_MEP_TPREL7A4 129 
#define  R_MEP_UIMM24 128 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ bfd_big_endian (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_reloc_ok ; 
 int /*<<< orphan*/  bfd_reloc_overflow ; 
 long mep_sdaoff_base (int) ; 
 unsigned long mep_tpoff_base (int) ; 

__attribute__((used)) static bfd_reloc_status_type
mep_final_link_relocate
    (reloc_howto_type *  howto,
     bfd *               input_bfd,
     asection *          input_section,
     bfd_byte *          contents,
     Elf_Internal_Rela * rel,
     bfd_vma             relocation)
{
  unsigned long u;
  long s;
  unsigned char *byte;
  bfd_vma pc;
  bfd_reloc_status_type r = bfd_reloc_ok;
  int e2, e4;

  if (bfd_big_endian (input_bfd))
    {
      e2 = 0;
      e4 = 0;
    }
  else
    {
      e2 = 1;
      e4 = 3;
    }

  pc = (input_section->output_section->vma
	+ input_section->output_offset
	+ rel->r_offset);

  s = relocation + rel->r_addend;

  byte = (unsigned char *)contents + rel->r_offset;

  if (howto->type == R_MEP_PCREL24A2
      && s == 0
      && pc >= 0x800000)
    {
      /* This is an unreachable branch to an undefined weak function.
	 Silently ignore it, since the opcode can't do that but should
	 never be executed anyway.  */
      return bfd_reloc_ok;
    }

  if (howto->pc_relative)
    s -= pc;

  u = (unsigned long) s;

  switch (howto->type)
    {
    /* MEPRELOC:APPLY */
    /* This section generated from bfd/mep-relocs.pl from include/elf/mep.h.  */
    case R_MEP_8: /* 76543210 */
      if (u > 255) r = bfd_reloc_overflow;
      byte[0] = (u & 0xff);
      break;
    case R_MEP_16: /* fedcba9876543210 */
      if (u > 65535) r = bfd_reloc_overflow;
      byte[0^e2] = ((u >> 8) & 0xff);
      byte[1^e2] = (u & 0xff);
      break;
    case R_MEP_32: /* vutsrqponmlkjihgfedcba9876543210 */
      byte[0^e4] = ((u >> 24) & 0xff);
      byte[1^e4] = ((u >> 16) & 0xff);
      byte[2^e4] = ((u >> 8) & 0xff);
      byte[3^e4] = (u & 0xff);
      break;
    case R_MEP_PCREL8A2: /* --------7654321- */
      if (-128 > s || s > 127) r = bfd_reloc_overflow;
      byte[1^e2] = (byte[1^e2] & 0x01) | (s & 0xfe);
      break;
    case R_MEP_PCREL12A2: /* ----ba987654321- */
      if (-2048 > s || s > 2047) r = bfd_reloc_overflow;
      byte[0^e2] = (byte[0^e2] & 0xf0) | ((s >> 8) & 0x0f);
      byte[1^e2] = (byte[1^e2] & 0x01) | (s & 0xfe);
      break;
    case R_MEP_PCREL17A2: /* ----------------gfedcba987654321 */
      if (-65536 > s || s > 65535) r = bfd_reloc_overflow;
      byte[2^e2] = ((s >> 9) & 0xff);
      byte[3^e2] = ((s >> 1) & 0xff);
      break;
    case R_MEP_PCREL24A2: /* -----7654321----nmlkjihgfedcba98 */
      if (-8388608 > s || s > 8388607) r = bfd_reloc_overflow;
      byte[0^e2] = (byte[0^e2] & 0xf8) | ((s >> 5) & 0x07);
      byte[1^e2] = (byte[1^e2] & 0x0f) | ((s << 3) & 0xf0);
      byte[2^e2] = ((s >> 16) & 0xff);
      byte[3^e2] = ((s >> 8) & 0xff);
      break;
    case R_MEP_PCABS24A2: /* -----7654321----nmlkjihgfedcba98 */
      if (u > 16777215) r = bfd_reloc_overflow;
      byte[0^e2] = (byte[0^e2] & 0xf8) | ((u >> 5) & 0x07);
      byte[1^e2] = (byte[1^e2] & 0x0f) | ((u << 3) & 0xf0);
      byte[2^e2] = ((u >> 16) & 0xff);
      byte[3^e2] = ((u >> 8) & 0xff);
      break;
    case R_MEP_LOW16: /* ----------------fedcba9876543210 */
      byte[2^e2] = ((u >> 8) & 0xff);
      byte[3^e2] = (u & 0xff);
      break;
    case R_MEP_HI16U: /* ----------------vutsrqponmlkjihg */
      byte[2^e2] = ((u >> 24) & 0xff);
      byte[3^e2] = ((u >> 16) & 0xff);
      break;
    case R_MEP_HI16S: /* ----------------vutsrqponmlkjihg */
      byte[2^e2] = ((s >> 24) & 0xff);
      byte[3^e2] = ((s >> 16) & 0xff);
      break;
    case R_MEP_GPREL: /* ----------------fedcba9876543210 */
      s -= mep_sdaoff_base(rel->r_offset);
      if (-32768 > s || s > 32767) r = bfd_reloc_overflow;
      byte[2^e2] = ((s >> 8) & 0xff);
      byte[3^e2] = (s & 0xff);
      break;
    case R_MEP_TPREL: /* ----------------fedcba9876543210 */
      s -= mep_tpoff_base(rel->r_offset);
      if (-32768 > s || s > 32767) r = bfd_reloc_overflow;
      byte[2^e2] = ((s >> 8) & 0xff);
      byte[3^e2] = (s & 0xff);
      break;
    case R_MEP_TPREL7: /* ---------6543210 */
      u -= mep_tpoff_base(rel->r_offset);
      if (u > 127) r = bfd_reloc_overflow;
      byte[1^e2] = (byte[1^e2] & 0x80) | (u & 0x7f);
      break;
    case R_MEP_TPREL7A2: /* ---------654321- */
      u -= mep_tpoff_base(rel->r_offset);
      if (u > 127) r = bfd_reloc_overflow;
      byte[1^e2] = (byte[1^e2] & 0x81) | (u & 0x7e);
      break;
    case R_MEP_TPREL7A4: /* ---------65432-- */
      u -= mep_tpoff_base(rel->r_offset);
      if (u > 127) r = bfd_reloc_overflow;
      byte[1^e2] = (byte[1^e2] & 0x83) | (u & 0x7c);
      break;
    case R_MEP_UIMM24: /* --------76543210nmlkjihgfedcba98 */
      if (u > 16777215) r = bfd_reloc_overflow;
      byte[1^e2] = (u & 0xff);
      byte[2^e2] = ((u >> 16) & 0xff);
      byte[3^e2] = ((u >> 8) & 0xff);
      break;
    case R_MEP_ADDR24A4: /* --------765432--nmlkjihgfedcba98 */
      if (u > 16777215) r = bfd_reloc_overflow;
      byte[1^e2] = (byte[1^e2] & 0x03) | (u & 0xfc);
      byte[2^e2] = ((u >> 16) & 0xff);
      byte[3^e2] = ((u >> 8) & 0xff);
      break;
    case R_MEP_GNU_VTINHERIT: /* ---------------- */
      break;
    case R_MEP_GNU_VTENTRY: /* ---------------- */
      break;
    /* MEPRELOC:END */
    default:
      abort ();
    }

  return r;
}