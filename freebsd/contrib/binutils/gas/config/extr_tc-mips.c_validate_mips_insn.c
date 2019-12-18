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
struct mips_opcode {char* args; unsigned long mask; unsigned long match; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  OP_MASK_ALN ; 
 int /*<<< orphan*/  OP_MASK_BCC ; 
 int /*<<< orphan*/  OP_MASK_BITIND ; 
 int /*<<< orphan*/  OP_MASK_BP ; 
 int /*<<< orphan*/  OP_MASK_CACHE ; 
 int /*<<< orphan*/  OP_MASK_CCC ; 
 int /*<<< orphan*/  OP_MASK_CODE ; 
 int /*<<< orphan*/  OP_MASK_CODE19 ; 
 int /*<<< orphan*/  OP_MASK_CODE2 ; 
 int /*<<< orphan*/  OP_MASK_CODE20 ; 
 int /*<<< orphan*/  OP_MASK_COPZ ; 
 int /*<<< orphan*/  OP_MASK_DELTA ; 
 int /*<<< orphan*/  OP_MASK_DSPACC ; 
 int /*<<< orphan*/  OP_MASK_DSPACC_S ; 
 int /*<<< orphan*/  OP_MASK_DSPSFT ; 
 int /*<<< orphan*/  OP_MASK_DSPSFT_7 ; 
 int /*<<< orphan*/  OP_MASK_EXTMSBD ; 
 int /*<<< orphan*/  OP_MASK_FD ; 
 int /*<<< orphan*/  OP_MASK_FR ; 
 int /*<<< orphan*/  OP_MASK_FS ; 
 int /*<<< orphan*/  OP_MASK_FT ; 
 int /*<<< orphan*/  OP_MASK_IMM10 ; 
 int /*<<< orphan*/  OP_MASK_IMM8 ; 
 int /*<<< orphan*/  OP_MASK_IMMEDIATE ; 
 int /*<<< orphan*/  OP_MASK_INSMSB ; 
 int /*<<< orphan*/  OP_MASK_MTACC_D ; 
 int /*<<< orphan*/  OP_MASK_MTACC_T ; 
 int /*<<< orphan*/  OP_MASK_MT_H ; 
 int /*<<< orphan*/  OP_MASK_MT_U ; 
 int /*<<< orphan*/  OP_MASK_PERFREG ; 
 int /*<<< orphan*/  OP_MASK_PREFX ; 
 int /*<<< orphan*/  OP_MASK_RD ; 
 int /*<<< orphan*/  OP_MASK_RDDSP ; 
 int /*<<< orphan*/  OP_MASK_RS ; 
 int /*<<< orphan*/  OP_MASK_RT ; 
 int /*<<< orphan*/  OP_MASK_SA3 ; 
 int /*<<< orphan*/  OP_MASK_SA4 ; 
 int /*<<< orphan*/  OP_MASK_SEL ; 
 int /*<<< orphan*/  OP_MASK_SHAMT ; 
 int /*<<< orphan*/  OP_MASK_TARGET ; 
 int /*<<< orphan*/  OP_MASK_UDI1 ; 
 int /*<<< orphan*/  OP_MASK_UDI2 ; 
 int /*<<< orphan*/  OP_MASK_UDI3 ; 
 int /*<<< orphan*/  OP_MASK_UDI4 ; 
 int /*<<< orphan*/  OP_MASK_VECALIGN ; 
 int /*<<< orphan*/  OP_MASK_VECBYTE ; 
 int /*<<< orphan*/  OP_MASK_VSEL ; 
 int /*<<< orphan*/  OP_MASK_WRDSP ; 
 int /*<<< orphan*/  OP_SH_ALN ; 
 int /*<<< orphan*/  OP_SH_BCC ; 
 int /*<<< orphan*/  OP_SH_BITIND ; 
 int /*<<< orphan*/  OP_SH_BP ; 
 int /*<<< orphan*/  OP_SH_CACHE ; 
 int /*<<< orphan*/  OP_SH_CCC ; 
 int /*<<< orphan*/  OP_SH_CODE ; 
 int /*<<< orphan*/  OP_SH_CODE19 ; 
 int /*<<< orphan*/  OP_SH_CODE2 ; 
 int /*<<< orphan*/  OP_SH_CODE20 ; 
 int /*<<< orphan*/  OP_SH_COPZ ; 
 int /*<<< orphan*/  OP_SH_DELTA ; 
 int /*<<< orphan*/  OP_SH_DSPACC ; 
 int /*<<< orphan*/  OP_SH_DSPACC_S ; 
 int /*<<< orphan*/  OP_SH_DSPSFT ; 
 int /*<<< orphan*/  OP_SH_DSPSFT_7 ; 
 int /*<<< orphan*/  OP_SH_EXTMSBD ; 
 int /*<<< orphan*/  OP_SH_FD ; 
 int /*<<< orphan*/  OP_SH_FR ; 
 int /*<<< orphan*/  OP_SH_FS ; 
 int /*<<< orphan*/  OP_SH_FT ; 
 int /*<<< orphan*/  OP_SH_IMM10 ; 
 int /*<<< orphan*/  OP_SH_IMM8 ; 
 int /*<<< orphan*/  OP_SH_IMMEDIATE ; 
 int /*<<< orphan*/  OP_SH_INSMSB ; 
 int /*<<< orphan*/  OP_SH_MTACC_D ; 
 int /*<<< orphan*/  OP_SH_MTACC_T ; 
 int /*<<< orphan*/  OP_SH_MT_H ; 
 int /*<<< orphan*/  OP_SH_MT_U ; 
 int /*<<< orphan*/  OP_SH_PERFREG ; 
 int /*<<< orphan*/  OP_SH_PREFX ; 
 int /*<<< orphan*/  OP_SH_RD ; 
 int /*<<< orphan*/  OP_SH_RDDSP ; 
 int /*<<< orphan*/  OP_SH_RS ; 
 int /*<<< orphan*/  OP_SH_RT ; 
 int /*<<< orphan*/  OP_SH_SA3 ; 
 int /*<<< orphan*/  OP_SH_SA4 ; 
 int /*<<< orphan*/  OP_SH_SEL ; 
 int /*<<< orphan*/  OP_SH_SHAMT ; 
 int /*<<< orphan*/  OP_SH_TARGET ; 
 int /*<<< orphan*/  OP_SH_UDI1 ; 
 int /*<<< orphan*/  OP_SH_UDI2 ; 
 int /*<<< orphan*/  OP_SH_UDI3 ; 
 int /*<<< orphan*/  OP_SH_UDI4 ; 
 int /*<<< orphan*/  OP_SH_VECALIGN ; 
 int /*<<< orphan*/  OP_SH_VECBYTE ; 
 int /*<<< orphan*/  OP_SH_VSEL ; 
 int /*<<< orphan*/  OP_SH_WRDSP ; 
 int /*<<< orphan*/  USE_BITS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,unsigned long,char*,...) ; 

__attribute__((used)) static int
validate_mips_insn (const struct mips_opcode *opc)
{
  const char *p = opc->args;
  char c;
  unsigned long used_bits = opc->mask;

  if ((used_bits & opc->match) != opc->match)
    {
      as_bad (_("internal: bad mips opcode (mask error): %s %s"),
	      opc->name, opc->args);
      return 0;
    }
#define USE_BITS(mask,shift)	(used_bits |= ((mask) << (shift)))
  while (*p)
    switch (c = *p++)
      {
      case ',': break;
      case '(': break;
      case ')': break;
      case '^': USE_BITS (OP_MASK_BITIND,       OP_SH_BITIND);   break;
      case '~': USE_BITS (OP_MASK_BITIND,       OP_SH_BITIND);   break;
      case '+':
    	switch (c = *p++)
	  {
	  case '1': USE_BITS (OP_MASK_UDI1,     OP_SH_UDI1); 	break;
	  case '2': USE_BITS (OP_MASK_UDI2,	OP_SH_UDI2); 	break;
	  case '3': USE_BITS (OP_MASK_UDI3,	OP_SH_UDI3); 	break;
	  case '4': USE_BITS (OP_MASK_UDI4,	OP_SH_UDI4); 	break;
	  case 'A': USE_BITS (OP_MASK_SHAMT,	OP_SH_SHAMT);	break;
	  case 'B': USE_BITS (OP_MASK_INSMSB,	OP_SH_INSMSB);	break;
	  case 'C': USE_BITS (OP_MASK_EXTMSBD,	OP_SH_EXTMSBD);	break;
	  case 'D': USE_BITS (OP_MASK_RD,	OP_SH_RD);
		    USE_BITS (OP_MASK_SEL,	OP_SH_SEL);	break;
	  case 'E': USE_BITS (OP_MASK_SHAMT,	OP_SH_SHAMT);	break;
	  case 'F': USE_BITS (OP_MASK_INSMSB,	OP_SH_INSMSB);	break;
	  case 'G': USE_BITS (OP_MASK_EXTMSBD,	OP_SH_EXTMSBD);	break;
	  case 'H': USE_BITS (OP_MASK_EXTMSBD,	OP_SH_EXTMSBD);	break;
	  case 'I': break;
	  case 't': USE_BITS (OP_MASK_RT,	OP_SH_RT);	break;
	  case 'T': USE_BITS (OP_MASK_RT,	OP_SH_RT);
		    USE_BITS (OP_MASK_SEL,	OP_SH_SEL);	break;
	  default:
	    as_bad (_("internal: bad mips opcode (unknown extension operand type `+%c'): %s %s"),
		    c, opc->name, opc->args);
	    return 0;
	  }
	break;
      case '<': USE_BITS (OP_MASK_SHAMT,	OP_SH_SHAMT);	break;
      case '>':	USE_BITS (OP_MASK_SHAMT,	OP_SH_SHAMT);	break;
      case 'A': break;
      case 'B': USE_BITS (OP_MASK_CODE20,       OP_SH_CODE20);  break;
      case 'C':	USE_BITS (OP_MASK_COPZ,		OP_SH_COPZ);	break;
      case 'D':	USE_BITS (OP_MASK_FD,		OP_SH_FD);	break;
      case 'E':	USE_BITS (OP_MASK_RT,		OP_SH_RT);	break;
      case 'F': break;
      case 'G':	USE_BITS (OP_MASK_RD,		OP_SH_RD);	break;
      case 'H': USE_BITS (OP_MASK_SEL,		OP_SH_SEL);	break;
      case 'I': break;
      case 'J': USE_BITS (OP_MASK_CODE19,       OP_SH_CODE19);  break;
      case 'K':	USE_BITS (OP_MASK_RD,		OP_SH_RD);	break;
      case 'L': break;
      case 'M':	USE_BITS (OP_MASK_CCC,		OP_SH_CCC);	break;
      case 'N':	USE_BITS (OP_MASK_BCC,		OP_SH_BCC);	break;
      case 'O':	USE_BITS (OP_MASK_ALN,		OP_SH_ALN);	break;
      case 'Q':	USE_BITS (OP_MASK_VSEL,		OP_SH_VSEL);
		USE_BITS (OP_MASK_FT,		OP_SH_FT);	break;
      case 'R':	USE_BITS (OP_MASK_FR,		OP_SH_FR);	break;
      case 'S':	USE_BITS (OP_MASK_FS,		OP_SH_FS);	break;
      case 'T':	USE_BITS (OP_MASK_FT,		OP_SH_FT);	break;
      case 'V':	USE_BITS (OP_MASK_FS,		OP_SH_FS);	break;
      case 'W':	USE_BITS (OP_MASK_FT,		OP_SH_FT);	break;
      case 'X':	USE_BITS (OP_MASK_FD,		OP_SH_FD);	break;
      case 'Y':	USE_BITS (OP_MASK_FS,		OP_SH_FS);	break;
      case 'Z':	USE_BITS (OP_MASK_FT,		OP_SH_FT);	break;
      case 'a':	USE_BITS (OP_MASK_TARGET,	OP_SH_TARGET);	break;
      case 'b':	USE_BITS (OP_MASK_RS,		OP_SH_RS);	break;
      case 'c':	USE_BITS (OP_MASK_CODE,		OP_SH_CODE);	break;
      case 'd':	USE_BITS (OP_MASK_RD,		OP_SH_RD);	break;
      case 'f': break;
      case 'h':	USE_BITS (OP_MASK_PREFX,	OP_SH_PREFX);	break;
      case 'i':	USE_BITS (OP_MASK_IMMEDIATE,	OP_SH_IMMEDIATE); break;
      case 'j':	USE_BITS (OP_MASK_DELTA,	OP_SH_DELTA);	break;
      case 'k':	USE_BITS (OP_MASK_CACHE,	OP_SH_CACHE);	break;
      case 'l': break;
      case 'o': USE_BITS (OP_MASK_DELTA,	OP_SH_DELTA);	break;
      case 'p':	USE_BITS (OP_MASK_DELTA,	OP_SH_DELTA);	break;
      case 'q':	USE_BITS (OP_MASK_CODE2,	OP_SH_CODE2);	break;
      case 'r': USE_BITS (OP_MASK_RS,		OP_SH_RS);	break;
      case 's':	USE_BITS (OP_MASK_RS,		OP_SH_RS);	break;
      case 't':	USE_BITS (OP_MASK_RT,		OP_SH_RT);	break;
      case 'u':	USE_BITS (OP_MASK_IMMEDIATE,	OP_SH_IMMEDIATE); break;
      case 'v':	USE_BITS (OP_MASK_RS,		OP_SH_RS);	break;
      case 'w':	USE_BITS (OP_MASK_RT,		OP_SH_RT);	break;
      case 'x': break;
      case 'y': USE_BITS (OP_MASK_CODE2,        OP_SH_CODE2);   break;
      case 'z': break;
      case 'P': USE_BITS (OP_MASK_PERFREG,	OP_SH_PERFREG);	break;
      case 'U': USE_BITS (OP_MASK_RD,           OP_SH_RD);
	        USE_BITS (OP_MASK_RT,           OP_SH_RT);	break;
      case 'e': USE_BITS (OP_MASK_VECBYTE,	OP_SH_VECBYTE);	break;
      case '%': USE_BITS (OP_MASK_VECALIGN,	OP_SH_VECALIGN); break;
      case '[': break;
      case ']': break;
      case '2': USE_BITS (OP_MASK_BP,		OP_SH_BP);	break;
      case '3': USE_BITS (OP_MASK_SA3,  	OP_SH_SA3);	break;
      case '4': USE_BITS (OP_MASK_SA4,  	OP_SH_SA4);	break;
      case '5': USE_BITS (OP_MASK_IMM8, 	OP_SH_IMM8);	break;
      case '6': USE_BITS (OP_MASK_RS,		OP_SH_RS);	break;
      case '7': USE_BITS (OP_MASK_DSPACC,	OP_SH_DSPACC);	break;
      case '8': USE_BITS (OP_MASK_WRDSP,	OP_SH_WRDSP);	break;
      case '9': USE_BITS (OP_MASK_DSPACC_S,	OP_SH_DSPACC_S);break;
      case '0': USE_BITS (OP_MASK_DSPSFT,	OP_SH_DSPSFT);	break;
      case '\'': USE_BITS (OP_MASK_RDDSP,	OP_SH_RDDSP);	break;
      case ':': USE_BITS (OP_MASK_DSPSFT_7,	OP_SH_DSPSFT_7);break;
      case '@': USE_BITS (OP_MASK_IMM10,	OP_SH_IMM10);	break;
      case '!': USE_BITS (OP_MASK_MT_U,		OP_SH_MT_U);	break;
      case '$': USE_BITS (OP_MASK_MT_H,		OP_SH_MT_H);	break;
      case '*': USE_BITS (OP_MASK_MTACC_T,	OP_SH_MTACC_T);	break;
      case '&': USE_BITS (OP_MASK_MTACC_D,	OP_SH_MTACC_D);	break;
      case 'g': USE_BITS (OP_MASK_RD,		OP_SH_RD);	break;
      default:
	as_bad (_("internal: bad mips opcode (unknown operand type `%c'): %s %s"),
		c, opc->name, opc->args);
	return 0;
      }
#undef USE_BITS
  if (used_bits != 0xffffffff)
    {
      as_bad (_("internal: bad mips opcode (bits 0x%lx undefined): %s %s"),
	      ~used_bits & 0xffffffff, opc->name, opc->args);
      return 0;
    }
  return 1;
}