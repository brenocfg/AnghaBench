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
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
 scalar_t__ CONST ; 
 scalar_t__ CONSTANT_P (scalar_t__) ; 
 scalar_t__ CONST_INT ; 
 int /*<<< orphan*/  DISP_IN_RANGE (int) ; 
 scalar_t__ GEN_INT (int) ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 int INTVAL (scalar_t__) ; 
 scalar_t__ LABEL_REF ; 
 scalar_t__ NULL_RTX ; 
 size_t PIC_OFFSET_TABLE_REGNUM ; 
 scalar_t__ PLUS ; 
 int /*<<< orphan*/  Pmode ; 
 scalar_t__ SYMBOL_REF ; 
 scalar_t__ SYMBOL_REF_LOCAL_P (scalar_t__) ; 
 scalar_t__ TARGET_CPU_ZARCH ; 
 int /*<<< orphan*/  TLS_SYMBOLIC_CONST (scalar_t__) ; 
 scalar_t__ UNSPEC ; 
#define  UNSPEC_GOT 132 
#define  UNSPEC_GOTENT 131 
#define  UNSPEC_GOTOFF 130 
#define  UNSPEC_PLT 129 
#define  UNSPEC_PLTOFF 128 
 int /*<<< orphan*/  VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 int XINT (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ const1_rtx ; 
 int /*<<< orphan*/  emit_move_insn (scalar_t__,scalar_t__) ; 
 int flag_pic ; 
 scalar_t__ force_const_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ force_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 scalar_t__ gen_const_mem (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_reg_rtx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gen_rtvec (int,scalar_t__) ; 
 scalar_t__ gen_rtx_CONST (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ gen_rtx_PLUS (int /*<<< orphan*/ ,scalar_t__,scalar_t__) ; 
 scalar_t__ gen_rtx_UNSPEC (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int const) ; 
 scalar_t__ larl_operand (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ pic_offset_table_rtx ; 
 scalar_t__ plus_constant (scalar_t__,int) ; 
 int* regs_ever_live ; 
 scalar_t__ reload_completed ; 
 scalar_t__ reload_in_progress ; 
 int /*<<< orphan*/  s390_load_address (scalar_t__,scalar_t__) ; 

rtx
legitimize_pic_address (rtx orig, rtx reg)
{
  rtx addr = orig;
  rtx new = orig;
  rtx base;

  gcc_assert (!TLS_SYMBOLIC_CONST (addr));

  if (GET_CODE (addr) == LABEL_REF
      || (GET_CODE (addr) == SYMBOL_REF && SYMBOL_REF_LOCAL_P (addr)))
    {
      /* This is a local symbol.  */
      if (TARGET_CPU_ZARCH && larl_operand (addr, VOIDmode))
        {
          /* Access local symbols PC-relative via LARL.
             This is the same as in the non-PIC case, so it is
             handled automatically ...  */
        }
      else
        {
          /* Access local symbols relative to the GOT.  */

          rtx temp = reg? reg : gen_reg_rtx (Pmode);

	  if (reload_in_progress || reload_completed)
	    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

          addr = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTOFF);
          addr = gen_rtx_CONST (Pmode, addr);
          addr = force_const_mem (Pmode, addr);
	  emit_move_insn (temp, addr);

          new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, temp);
          if (reg != 0)
            {
              s390_load_address (reg, new);
              new = reg;
            }
        }
    }
  else if (GET_CODE (addr) == SYMBOL_REF)
    {
      if (reg == 0)
        reg = gen_reg_rtx (Pmode);

      if (flag_pic == 1)
        {
          /* Assume GOT offset < 4k.  This is handled the same way
             in both 31- and 64-bit code (@GOT).  */

	  if (reload_in_progress || reload_completed)
	    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

          new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOT);
          new = gen_rtx_CONST (Pmode, new);
          new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, new);
          new = gen_const_mem (Pmode, new);
          emit_move_insn (reg, new);
          new = reg;
        }
      else if (TARGET_CPU_ZARCH)
        {
          /* If the GOT offset might be >= 4k, we determine the position
             of the GOT entry via a PC-relative LARL (@GOTENT).  */

          rtx temp = gen_reg_rtx (Pmode);

          new = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOTENT);
          new = gen_rtx_CONST (Pmode, new);
          emit_move_insn (temp, new);

          new = gen_const_mem (Pmode, temp);
          emit_move_insn (reg, new);
          new = reg;
        }
      else
        {
          /* If the GOT offset might be >= 4k, we have to load it
             from the literal pool (@GOT).  */

          rtx temp = gen_reg_rtx (Pmode);

	  if (reload_in_progress || reload_completed)
	    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

          addr = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr), UNSPEC_GOT);
          addr = gen_rtx_CONST (Pmode, addr);
          addr = force_const_mem (Pmode, addr);
          emit_move_insn (temp, addr);

          new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, temp);
          new = gen_const_mem (Pmode, new);
          emit_move_insn (reg, new);
          new = reg;
        }
    }
  else
    {
      if (GET_CODE (addr) == CONST)
	{
	  addr = XEXP (addr, 0);
	  if (GET_CODE (addr) == UNSPEC)
	    {
	      gcc_assert (XVECLEN (addr, 0) == 1);
              switch (XINT (addr, 1))
                {
                  /* If someone moved a GOT-relative UNSPEC
                     out of the literal pool, force them back in.  */
                  case UNSPEC_GOTOFF:
                  case UNSPEC_PLTOFF:
                    new = force_const_mem (Pmode, orig);
                    break;

                  /* @GOT is OK as is if small.  */
		  case UNSPEC_GOT:
		    if (flag_pic == 2)
		      new = force_const_mem (Pmode, orig);
		    break;

                  /* @GOTENT is OK as is.  */
                  case UNSPEC_GOTENT:
                    break;

                  /* @PLT is OK as is on 64-bit, must be converted to
                     GOT-relative @PLTOFF on 31-bit.  */
                  case UNSPEC_PLT:
                    if (!TARGET_CPU_ZARCH)
                      {
                        rtx temp = reg? reg : gen_reg_rtx (Pmode);

			if (reload_in_progress || reload_completed)
			  regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

                        addr = XVECEXP (addr, 0, 0);
                        addr = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, addr),
					       UNSPEC_PLTOFF);
                        addr = gen_rtx_CONST (Pmode, addr);
                        addr = force_const_mem (Pmode, addr);
	                emit_move_insn (temp, addr);

                        new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, temp);
                        if (reg != 0)
                          {
                            s390_load_address (reg, new);
                            new = reg;
                          }
                      }
                    break;

                  /* Everything else cannot happen.  */
                  default:
                    gcc_unreachable ();
                }
	    }
	  else 
	    gcc_assert (GET_CODE (addr) == PLUS);
	}
      if (GET_CODE (addr) == PLUS)
	{
	  rtx op0 = XEXP (addr, 0), op1 = XEXP (addr, 1);

	  gcc_assert (!TLS_SYMBOLIC_CONST (op0));
	  gcc_assert (!TLS_SYMBOLIC_CONST (op1));

	  /* Check first to see if this is a constant offset
             from a local symbol reference.  */
	  if ((GET_CODE (op0) == LABEL_REF
		|| (GET_CODE (op0) == SYMBOL_REF && SYMBOL_REF_LOCAL_P (op0)))
	      && GET_CODE (op1) == CONST_INT)
	    {
              if (TARGET_CPU_ZARCH
		  && larl_operand (op0, VOIDmode)
		  && INTVAL (op1) < (HOST_WIDE_INT)1 << 31
		  && INTVAL (op1) >= -((HOST_WIDE_INT)1 << 31))
                {
                  if (INTVAL (op1) & 1)
                    {
                      /* LARL can't handle odd offsets, so emit a
                         pair of LARL and LA.  */
                      rtx temp = reg? reg : gen_reg_rtx (Pmode);

                      if (!DISP_IN_RANGE (INTVAL (op1)))
                        {
                          HOST_WIDE_INT even = INTVAL (op1) - 1;
                          op0 = gen_rtx_PLUS (Pmode, op0, GEN_INT (even));
			  op0 = gen_rtx_CONST (Pmode, op0);
                          op1 = const1_rtx;
                        }

                      emit_move_insn (temp, op0);
                      new = gen_rtx_PLUS (Pmode, temp, op1);

                      if (reg != 0)
                        {
                          s390_load_address (reg, new);
                          new = reg;
                        }
                    }
                  else
                    {
                      /* If the offset is even, we can just use LARL.
                         This will happen automatically.  */
                    }
                }
              else
                {
                  /* Access local symbols relative to the GOT.  */

                  rtx temp = reg? reg : gen_reg_rtx (Pmode);

		  if (reload_in_progress || reload_completed)
		    regs_ever_live[PIC_OFFSET_TABLE_REGNUM] = 1;

                  addr = gen_rtx_UNSPEC (Pmode, gen_rtvec (1, op0),
					 UNSPEC_GOTOFF);
                  addr = gen_rtx_PLUS (Pmode, addr, op1);
                  addr = gen_rtx_CONST (Pmode, addr);
                  addr = force_const_mem (Pmode, addr);
		  emit_move_insn (temp, addr);

                  new = gen_rtx_PLUS (Pmode, pic_offset_table_rtx, temp);
                  if (reg != 0)
                    {
                      s390_load_address (reg, new);
                      new = reg;
                    }
                }
	    }

          /* Now, check whether it is a GOT relative symbol plus offset
             that was pulled out of the literal pool.  Force it back in.  */

	  else if (GET_CODE (op0) == UNSPEC
	           && GET_CODE (op1) == CONST_INT
	           && XINT (op0, 1) == UNSPEC_GOTOFF)
            {
	      gcc_assert (XVECLEN (op0, 0) == 1);

              new = force_const_mem (Pmode, orig);
            }

          /* Otherwise, compute the sum.  */
	  else
	    {
	      base = legitimize_pic_address (XEXP (addr, 0), reg);
	      new  = legitimize_pic_address (XEXP (addr, 1),
					     base == reg ? NULL_RTX : reg);
	      if (GET_CODE (new) == CONST_INT)
		new = plus_constant (base, INTVAL (new));
	      else
		{
		  if (GET_CODE (new) == PLUS && CONSTANT_P (XEXP (new, 1)))
		    {
		      base = gen_rtx_PLUS (Pmode, base, XEXP (new, 0));
		      new = XEXP (new, 1);
		    }
		  new = gen_rtx_PLUS (Pmode, base, new);
		}

	      if (GET_CODE (new) == CONST)
		new = XEXP (new, 0);
              new = force_operand (new, 0);
	    }
	}
    }
  return new;
}