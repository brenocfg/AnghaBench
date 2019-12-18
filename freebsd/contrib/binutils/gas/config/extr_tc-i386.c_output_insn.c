#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  valueT ;
typedef  int /*<<< orphan*/  offsetT ;
typedef  int /*<<< orphan*/  fragS ;
struct TYPE_10__ {int base; int index; int scale; } ;
struct TYPE_8__ {int regmem; int reg; int mode; } ;
struct TYPE_7__ {int opcode_modifier; int cpu_flags; int base_opcode; } ;
struct TYPE_11__ {unsigned int* prefix; scalar_t__ imm_operands; scalar_t__ disp_operands; TYPE_4__ sib; TYPE_3__* base_reg; TYPE_2__ rm; TYPE_1__ tm; } ;
struct TYPE_9__ {int reg_type; } ;

/* Variables and functions */
 int CpuABM ; 
 int CpuAES ; 
 int CpuPCLMUL ; 
 int CpuPadLock ; 
 int CpuSSE4 ; 
 int CpuSSSE3 ; 
 int ESCAPE_TO_TWO_BYTE_ADDRESSING ; 
 int /*<<< orphan*/  FRAG_APPEND_1_CHAR (int) ; 
 int Jump ; 
 int JumpByte ; 
 int JumpDword ; 
 int JumpInterSegment ; 
 size_t LOCKREP_PREFIX ; 
 int Modrm ; 
 unsigned int REPE_PREFIX_OPCODE ; 
 int Reg16 ; 
 int /*<<< orphan*/  add_prefix (unsigned int) ; 
 int /*<<< orphan*/  dwarf2_emit_insn (int /*<<< orphan*/ ) ; 
 scalar_t__ fits_in_unsigned_byte (int) ; 
 scalar_t__ flag_debug ; 
 char* frag_more (int) ; 
 int /*<<< orphan*/ * frag_now ; 
 int /*<<< orphan*/  frag_now_fix () ; 
 TYPE_5__ i ; 
 int /*<<< orphan*/  md_number_to_chars (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_branch () ; 
 int /*<<< orphan*/  output_disp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_imm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_interseg_jump () ; 
 int /*<<< orphan*/  output_jump () ; 
 int /*<<< orphan*/  pi (char*,TYPE_5__*) ; 

__attribute__((used)) static void
output_insn (void)
{
  fragS *insn_start_frag;
  offsetT insn_start_off;

  /* Tie dwarf2 debug info to the address at the start of the insn.
     We can't do this after the insn has been output as the current
     frag may have been closed off.  eg. by frag_var.  */
  dwarf2_emit_insn (0);

  insn_start_frag = frag_now;
  insn_start_off = frag_now_fix ();

  /* Output jumps.  */
  if (i.tm.opcode_modifier & Jump)
    output_branch ();
  else if (i.tm.opcode_modifier & (JumpByte | JumpDword))
    output_jump ();
  else if (i.tm.opcode_modifier & JumpInterSegment)
    output_interseg_jump ();
  else
    {
      /* Output normal instructions here.  */
      char *p;
      unsigned char *q;
      unsigned int prefix;

      /* All opcodes on i386 have either 1 or 2 bytes.  SSSE3 and
	 SSE4 instructions have 3 bytes.  We may use one more higher
	 byte to specify a prefix the instruction requires.  Exclude
	 instructions which are in both SSE4 and ABM.  */
      if ((i.tm.cpu_flags & (CpuSSSE3 | CpuSSE4 | CpuAES | CpuPCLMUL)) != 0
	  && (i.tm.cpu_flags & CpuABM) == 0)
	{
	  if (i.tm.base_opcode & 0xff000000)
	    {
	      prefix = (i.tm.base_opcode >> 24) & 0xff;
	      goto check_prefix;
	    }
	}
      else if (i.tm.base_opcode == 0x660f3880 || i.tm.base_opcode == 0x660f3881
	  || i.tm.base_opcode == 0x660f3882)
	{
	  /* invept and invvpid are 3 byte instructions with a
	     mandatory prefix. */
	  if (i.tm.base_opcode & 0xff000000)
	    {
	      prefix = (i.tm.base_opcode >> 24) & 0xff;
	      add_prefix (prefix);
	    }
	}
      else if ((i.tm.base_opcode & 0xff0000) != 0)
	{
	  prefix = (i.tm.base_opcode >> 16) & 0xff;
	  if ((i.tm.cpu_flags & CpuPadLock) != 0)
	    {
	    check_prefix:
	      if (prefix != REPE_PREFIX_OPCODE
		  || i.prefix[LOCKREP_PREFIX] != REPE_PREFIX_OPCODE)
		add_prefix (prefix);
	    }
	  else
	    add_prefix (prefix);
	}

      /* The prefix bytes.  */
      for (q = i.prefix;
	   q < i.prefix + sizeof (i.prefix) / sizeof (i.prefix[0]);
	   q++)
	{
	  if (*q)
	    {
	      p = frag_more (1);
	      md_number_to_chars (p, (valueT) *q, 1);
	    }
	}

      /* Now the opcode; be careful about word order here!  */
      if (fits_in_unsigned_byte (i.tm.base_opcode))
	{
	  FRAG_APPEND_1_CHAR (i.tm.base_opcode);
	}
      else
	{
	  if ((i.tm.cpu_flags & (CpuSSSE3 | CpuSSE4 | CpuAES | CpuPCLMUL)) != 0
	      && (i.tm.cpu_flags & CpuABM) == 0)
	    {
	      p = frag_more (3);
	      *p++ = (i.tm.base_opcode >> 16) & 0xff;
	    }
	  else if (i.tm.base_opcode == 0x660f3880 ||
		   i.tm.base_opcode == 0x660f3881 ||
		   i.tm.base_opcode == 0x660f3882)
	    {
	      p = frag_more (3);
	      *p++ = (i.tm.base_opcode >> 16) & 0xff;
	    }
	  else
	    p = frag_more (2);

	  /* Put out high byte first: can't use md_number_to_chars!  */
	  *p++ = (i.tm.base_opcode >> 8) & 0xff;
	  *p = i.tm.base_opcode & 0xff;
	}

      /* Now the modrm byte and sib byte (if present).  */
      if (i.tm.opcode_modifier & Modrm)
	{
	  p = frag_more (1);
	  md_number_to_chars (p,
			      (valueT) (i.rm.regmem << 0
					| i.rm.reg << 3
					| i.rm.mode << 6),
			      1);
	  /* If i.rm.regmem == ESP (4)
	     && i.rm.mode != (Register mode)
	     && not 16 bit
	     ==> need second modrm byte.  */
	  if (i.rm.regmem == ESCAPE_TO_TWO_BYTE_ADDRESSING
	      && i.rm.mode != 3
	      && !(i.base_reg && (i.base_reg->reg_type & Reg16) != 0))
	    {
	      p = frag_more (1);
	      md_number_to_chars (p,
				  (valueT) (i.sib.base << 0
					    | i.sib.index << 3
					    | i.sib.scale << 6),
				  1);
	    }
	}

      if (i.disp_operands)
	output_disp (insn_start_frag, insn_start_off);

      if (i.imm_operands)
	output_imm (insn_start_frag, insn_start_off);
    }

#ifdef DEBUG386
  if (flag_debug)
    {
      pi ("" /*line*/, &i);
    }
#endif /* DEBUG386  */
}