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
typedef  scalar_t__ rtx ;

/* Variables and functions */
#define  CM_EMBMEDANY 131 
#define  CM_MEDANY 130 
#define  CM_MEDLOW 129 
#define  CM_MEDMID 128 
 int /*<<< orphan*/  DImode ; 
 int /*<<< orphan*/  GEN_INT (int) ; 
 scalar_t__ GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  REGNO (scalar_t__) ; 
 scalar_t__ TImode ; 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  data_segment_operand (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  emit_insn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (scalar_t__) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/  gen_embmedany_brsum (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_losum (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_sethi (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_texthi (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_textlo (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_textuhi (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_embmedany_textulo (scalar_t__,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_ASHIFT (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_HIGH (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_LO_SUM (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_REG (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtx_SET (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_seth44 (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_sethh (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_sethm (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_setl44 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_setlm (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_setlo (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  gen_setm44 (scalar_t__,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 
 int sparc_cmodel ; 

void
sparc_emit_set_symbolic_const64 (rtx op0, rtx op1, rtx temp)
{
  rtx temp1, temp2, temp3, temp4, temp5;
  rtx ti_temp = 0;

  if (temp && GET_MODE (temp) == TImode)
    {
      ti_temp = temp;
      temp = gen_rtx_REG (DImode, REGNO (temp));
    }

  /* SPARC-V9 code-model support.  */
  switch (sparc_cmodel)
    {
    case CM_MEDLOW:
      /* The range spanned by all instructions in the object is less
	 than 2^31 bytes (2GB) and the distance from any instruction
	 to the location of the label _GLOBAL_OFFSET_TABLE_ is less
	 than 2^31 bytes (2GB).

	 The executable must be in the low 4TB of the virtual address
	 space.

	 sethi	%hi(symbol), %temp1
	 or	%temp1, %lo(symbol), %reg  */
      if (temp)
	temp1 = temp;  /* op0 is allowed.  */
      else
	temp1 = gen_reg_rtx (DImode);

      emit_insn (gen_rtx_SET (VOIDmode, temp1, gen_rtx_HIGH (DImode, op1)));
      emit_insn (gen_rtx_SET (VOIDmode, op0, gen_rtx_LO_SUM (DImode, temp1, op1)));
      break;

    case CM_MEDMID:
      /* The range spanned by all instructions in the object is less
	 than 2^31 bytes (2GB) and the distance from any instruction
	 to the location of the label _GLOBAL_OFFSET_TABLE_ is less
	 than 2^31 bytes (2GB).

	 The executable must be in the low 16TB of the virtual address
	 space.

	 sethi	%h44(symbol), %temp1
	 or	%temp1, %m44(symbol), %temp2
	 sllx	%temp2, 12, %temp3
	 or	%temp3, %l44(symbol), %reg  */
      if (temp)
	{
	  temp1 = op0;
	  temp2 = op0;
	  temp3 = temp;  /* op0 is allowed.  */
	}
      else
	{
	  temp1 = gen_reg_rtx (DImode);
	  temp2 = gen_reg_rtx (DImode);
	  temp3 = gen_reg_rtx (DImode);
	}

      emit_insn (gen_seth44 (temp1, op1));
      emit_insn (gen_setm44 (temp2, temp1, op1));
      emit_insn (gen_rtx_SET (VOIDmode, temp3,
			      gen_rtx_ASHIFT (DImode, temp2, GEN_INT (12))));
      emit_insn (gen_setl44 (op0, temp3, op1));
      break;

    case CM_MEDANY:
      /* The range spanned by all instructions in the object is less
	 than 2^31 bytes (2GB) and the distance from any instruction
	 to the location of the label _GLOBAL_OFFSET_TABLE_ is less
	 than 2^31 bytes (2GB).

	 The executable can be placed anywhere in the virtual address
	 space.

	 sethi	%hh(symbol), %temp1
	 sethi	%lm(symbol), %temp2
	 or	%temp1, %hm(symbol), %temp3
	 sllx	%temp3, 32, %temp4
	 or	%temp4, %temp2, %temp5
	 or	%temp5, %lo(symbol), %reg  */
      if (temp)
	{
	  /* It is possible that one of the registers we got for operands[2]
	     might coincide with that of operands[0] (which is why we made
	     it TImode).  Pick the other one to use as our scratch.  */
	  if (rtx_equal_p (temp, op0))
	    {
	      gcc_assert (ti_temp);
	      temp = gen_rtx_REG (DImode, REGNO (temp) + 1);
	    }
	  temp1 = op0;
	  temp2 = temp;  /* op0 is _not_ allowed, see above.  */
	  temp3 = op0;
	  temp4 = op0;
	  temp5 = op0;
	}
      else
	{
	  temp1 = gen_reg_rtx (DImode);
	  temp2 = gen_reg_rtx (DImode);
	  temp3 = gen_reg_rtx (DImode);
	  temp4 = gen_reg_rtx (DImode);
	  temp5 = gen_reg_rtx (DImode);
	}

      emit_insn (gen_sethh (temp1, op1));
      emit_insn (gen_setlm (temp2, op1));
      emit_insn (gen_sethm (temp3, temp1, op1));
      emit_insn (gen_rtx_SET (VOIDmode, temp4,
			      gen_rtx_ASHIFT (DImode, temp3, GEN_INT (32))));
      emit_insn (gen_rtx_SET (VOIDmode, temp5,
			      gen_rtx_PLUS (DImode, temp4, temp2)));
      emit_insn (gen_setlo (op0, temp5, op1));
      break;

    case CM_EMBMEDANY:
      /* Old old old backwards compatibility kruft here.
	 Essentially it is MEDLOW with a fixed 64-bit
	 virtual base added to all data segment addresses.
	 Text-segment stuff is computed like MEDANY, we can't
	 reuse the code above because the relocation knobs
	 look different.

	 Data segment:	sethi	%hi(symbol), %temp1
			add	%temp1, EMBMEDANY_BASE_REG, %temp2
			or	%temp2, %lo(symbol), %reg  */
      if (data_segment_operand (op1, GET_MODE (op1)))
	{
	  if (temp)
	    {
	      temp1 = temp;  /* op0 is allowed.  */
	      temp2 = op0;
	    }
	  else
	    {
	      temp1 = gen_reg_rtx (DImode);
	      temp2 = gen_reg_rtx (DImode);
	    }

	  emit_insn (gen_embmedany_sethi (temp1, op1));
	  emit_insn (gen_embmedany_brsum (temp2, temp1));
	  emit_insn (gen_embmedany_losum (op0, temp2, op1));
	}

      /* Text segment:	sethi	%uhi(symbol), %temp1
			sethi	%hi(symbol), %temp2
			or	%temp1, %ulo(symbol), %temp3
			sllx	%temp3, 32, %temp4
			or	%temp4, %temp2, %temp5
			or	%temp5, %lo(symbol), %reg  */
      else
	{
	  if (temp)
	    {
	      /* It is possible that one of the registers we got for operands[2]
		 might coincide with that of operands[0] (which is why we made
		 it TImode).  Pick the other one to use as our scratch.  */
	      if (rtx_equal_p (temp, op0))
		{
		  gcc_assert (ti_temp);
		  temp = gen_rtx_REG (DImode, REGNO (temp) + 1);
		}
	      temp1 = op0;
	      temp2 = temp;  /* op0 is _not_ allowed, see above.  */
	      temp3 = op0;
	      temp4 = op0;
	      temp5 = op0;
	    }
	  else
	    {
	      temp1 = gen_reg_rtx (DImode);
	      temp2 = gen_reg_rtx (DImode);
	      temp3 = gen_reg_rtx (DImode);
	      temp4 = gen_reg_rtx (DImode);
	      temp5 = gen_reg_rtx (DImode);
	    }

	  emit_insn (gen_embmedany_textuhi (temp1, op1));
	  emit_insn (gen_embmedany_texthi  (temp2, op1));
	  emit_insn (gen_embmedany_textulo (temp3, temp1, op1));
	  emit_insn (gen_rtx_SET (VOIDmode, temp4,
				  gen_rtx_ASHIFT (DImode, temp3, GEN_INT (32))));
	  emit_insn (gen_rtx_SET (VOIDmode, temp5,
				  gen_rtx_PLUS (DImode, temp4, temp2)));
	  emit_insn (gen_embmedany_textlo  (op0, temp5, op1));
	}
      break;

    default:
      gcc_unreachable ();
    }
}