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
struct reg_flags {int is_write; int /*<<< orphan*/  is_sibcall; } ;
typedef  int /*<<< orphan*/  rtx ;
struct TYPE_2__ {int /*<<< orphan*/  write_count; } ;
typedef  int HOST_WIDE_INT ;

/* Variables and functions */
#define  ABS 232 
#define  AND 231 
 size_t AR_EC_REGNUM ; 
 size_t AR_PFS_REGNUM ; 
 int AR_UNAT_BIT_0 ; 
 int AR_UNAT_REGNUM ; 
#define  ASHIFT 230 
#define  ASHIFTRT 229 
#define  ASM_INPUT 228 
#define  ASM_OPERANDS 227 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ASM_OPERANDS_INPUT_LENGTH (int /*<<< orphan*/ ) ; 
#define  CALL 226 
#define  CLOBBER 225 
#define  COMPARE 224 
#define  COND_EXEC 223 
 int /*<<< orphan*/  COND_EXEC_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  COND_EXEC_TEST (int /*<<< orphan*/ ) ; 
#define  CONST 222 
#define  CONST_DOUBLE 221 
#define  CONST_INT 220 
#define  CONST_VECTOR 219 
#define  DIV 218 
#define  EQ 217 
#define  FFS 216 
#define  FIX 215 
#define  FLOAT 214 
#define  FLOAT_EXTEND 213 
#define  FLOAT_TRUNCATE 212 
#define  GE 211 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int const) ; 
 int /*<<< orphan*/  GET_RTX_LENGTH (int const) ; 
#define  GEU 210 
#define  GT 209 
#define  GTU 208 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  IOR 207 
#define  LABEL_REF 206 
#define  LE 205 
#define  LEU 204 
#define  LSHIFTRT 203 
#define  LT 202 
#define  LTU 201 
#define  MEM 200 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  MINUS 199 
#define  MOD 198 
#define  MULT 197 
#define  NE 196 
#define  NEG 195 
#define  NOT 194 
#define  PARALLEL 193 
#define  PLUS 192 
#define  POPCOUNT 191 
#define  POST_DEC 190 
#define  POST_INC 189 
#define  POST_MODIFY 188 
 int /*<<< orphan*/  PR_REGS ; 
#define  REG 187 
 int REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REGNO_REG_CLASS (int) ; 
 size_t REG_AR_CFM ; 
 size_t REG_RP ; 
 size_t REG_VOLATILE ; 
#define  RETURN 186 
#define  ROTATE 185 
#define  ROTATERT 184 
#define  SET 183 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  SIGN_EXTEND 182 
#define  SMAX 181 
#define  SMIN 180 
#define  SQRT 179 
#define  SUBREG 178 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 177 
 int /*<<< orphan*/  TARGET_VOL_ASM_STOP ; 
#define  TRUNCATE 176 
#define  UDIV 175 
#define  UMAX 174 
#define  UMIN 173 
#define  UMOD 172 
#define  UNSIGNED_FIX 171 
#define  UNSIGNED_FLOAT 170 
#define  UNSPEC 169 
#define  UNSPECV_ALLOC 168 
#define  UNSPECV_BLOCKAGE 167 
#define  UNSPECV_BREAK 166 
#define  UNSPECV_INSN_GROUP_BARRIER 165 
#define  UNSPECV_PSAC_ALL 164 
#define  UNSPECV_PSAC_NORMAL 163 
#define  UNSPECV_SET_BSP 162 
#define  UNSPEC_ADDP4 161 
#define  UNSPEC_BSP_VALUE 160 
#define  UNSPEC_BUNDLE_SELECTOR 159 
#define  UNSPEC_CHKACLR 158 
#define  UNSPEC_CHKS 157 
#define  UNSPEC_CMPXCHG_ACQ 156 
#define  UNSPEC_COPYSIGN 155 
#define  UNSPEC_DTPREL 154 
#define  UNSPEC_FETCHADD_ACQ 153 
#define  UNSPEC_FLUSHRS 152 
#define  UNSPEC_FR_RECIP_APPROX 151 
#define  UNSPEC_FR_RESTORE 150 
#define  UNSPEC_FR_SPILL 149 
#define  UNSPEC_FR_SQRT_RECIP_APPROX 148 
#define  UNSPEC_GETF_EXP 147 
#define  UNSPEC_GR_RESTORE 146 
#define  UNSPEC_GR_SPILL 145 
#define  UNSPEC_LDA 144 
#define  UNSPEC_LDS 143 
#define  UNSPEC_LDSA 142 
#define  UNSPEC_LTOFF_DTPMOD 141 
#define  UNSPEC_LTOFF_DTPREL 140 
#define  UNSPEC_LTOFF_TPREL 139 
#define  UNSPEC_MF 138 
#define  UNSPEC_PIC_CALL 137 
#define  UNSPEC_PRED_REL_MUTEX 136 
#define  UNSPEC_SETF_EXP 135 
#define  UNSPEC_SHRP 134 
#define  UNSPEC_TPREL 133 
#define  UNSPEC_VOLATILE 132 
#define  USE 131 
#define  VEC_SELECT 130 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int const XINT (int /*<<< orphan*/ ,int) ; 
#define  XOR 129 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
#define  ZERO_EXTEND 128 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int rws_access_reg (int /*<<< orphan*/ ,struct reg_flags,int) ; 
 int rws_access_regno (size_t,struct reg_flags,int) ; 
 TYPE_1__* rws_insn ; 
 int set_src_needs_barrier (int /*<<< orphan*/ ,struct reg_flags,int) ; 
 int /*<<< orphan*/  update_set_flags (int /*<<< orphan*/ ,struct reg_flags*) ; 

__attribute__((used)) static int
rtx_needs_barrier (rtx x, struct reg_flags flags, int pred)
{
  int i, j;
  int is_complemented = 0;
  int need_barrier = 0;
  const char *format_ptr;
  struct reg_flags new_flags;
  rtx cond;

  if (! x)
    return 0;

  new_flags = flags;

  switch (GET_CODE (x))
    {
    case SET:
      update_set_flags (x, &new_flags);
      need_barrier = set_src_needs_barrier (x, new_flags, pred);
      if (GET_CODE (SET_SRC (x)) != CALL)
	{
	  new_flags.is_write = 1;
	  need_barrier |= rtx_needs_barrier (SET_DEST (x), new_flags, pred);
	}
      break;

    case CALL:
      new_flags.is_write = 0;
      need_barrier |= rws_access_regno (AR_EC_REGNUM, new_flags, pred);

      /* Avoid multiple register writes, in case this is a pattern with
	 multiple CALL rtx.  This avoids a failure in rws_access_reg.  */
      if (! flags.is_sibcall && ! rws_insn[REG_AR_CFM].write_count)
	{
	  new_flags.is_write = 1;
	  need_barrier |= rws_access_regno (REG_RP, new_flags, pred);
	  need_barrier |= rws_access_regno (AR_PFS_REGNUM, new_flags, pred);
	  need_barrier |= rws_access_regno (REG_AR_CFM, new_flags, pred);
	}
      break;

    case COND_EXEC:
      /* X is a predicated instruction.  */

      cond = COND_EXEC_TEST (x);
      gcc_assert (!pred);
      need_barrier = rtx_needs_barrier (cond, flags, 0);

      if (GET_CODE (cond) == EQ)
	is_complemented = 1;
      cond = XEXP (cond, 0);
      gcc_assert (GET_CODE (cond) == REG
		  && REGNO_REG_CLASS (REGNO (cond)) == PR_REGS);
      pred = REGNO (cond);
      if (is_complemented)
	++pred;

      need_barrier |= rtx_needs_barrier (COND_EXEC_CODE (x), flags, pred);
      return need_barrier;

    case CLOBBER:
    case USE:
      /* Clobber & use are for earlier compiler-phases only.  */
      break;

    case ASM_OPERANDS:
    case ASM_INPUT:
      /* We always emit stop bits for traditional asms.  We emit stop bits
	 for volatile extended asms if TARGET_VOL_ASM_STOP is true.  */
      if (GET_CODE (x) != ASM_OPERANDS
	  || (MEM_VOLATILE_P (x) && TARGET_VOL_ASM_STOP))
	{
	  /* Avoid writing the register multiple times if we have multiple
	     asm outputs.  This avoids a failure in rws_access_reg.  */
	  if (! rws_insn[REG_VOLATILE].write_count)
	    {
	      new_flags.is_write = 1;
	      rws_access_regno (REG_VOLATILE, new_flags, pred);
	    }
	  return 1;
	}

      /* For all ASM_OPERANDS, we must traverse the vector of input operands.
	 We cannot just fall through here since then we would be confused
	 by the ASM_INPUT rtx inside ASM_OPERANDS, which do not indicate
	 traditional asms unlike their normal usage.  */

      for (i = ASM_OPERANDS_INPUT_LENGTH (x) - 1; i >= 0; --i)
	if (rtx_needs_barrier (ASM_OPERANDS_INPUT (x, i), flags, pred))
	  need_barrier = 1;
      break;

    case PARALLEL:
      for (i = XVECLEN (x, 0) - 1; i >= 0; --i)
	{
	  rtx pat = XVECEXP (x, 0, i);
	  switch (GET_CODE (pat))
	    {
	    case SET:
	      update_set_flags (pat, &new_flags);
	      need_barrier |= set_src_needs_barrier (pat, new_flags, pred);
	      break;

	    case USE:
	    case CALL:
	    case ASM_OPERANDS:
	      need_barrier |= rtx_needs_barrier (pat, flags, pred);
	      break;

	    case CLOBBER:
	    case RETURN:
	      break;

	    default:
	      gcc_unreachable ();
	    }
	}
      for (i = XVECLEN (x, 0) - 1; i >= 0; --i)
	{
	  rtx pat = XVECEXP (x, 0, i);
	  if (GET_CODE (pat) == SET)
	    {
	      if (GET_CODE (SET_SRC (pat)) != CALL)
		{
		  new_flags.is_write = 1;
		  need_barrier |= rtx_needs_barrier (SET_DEST (pat), new_flags,
						     pred);
		}
	    }
	  else if (GET_CODE (pat) == CLOBBER || GET_CODE (pat) == RETURN)
	    need_barrier |= rtx_needs_barrier (pat, flags, pred);
	}
      break;

    case SUBREG:
      need_barrier |= rtx_needs_barrier (SUBREG_REG (x), flags, pred);
      break;
    case REG:
      if (REGNO (x) == AR_UNAT_REGNUM)
	{
	  for (i = 0; i < 64; ++i)
	    need_barrier |= rws_access_regno (AR_UNAT_BIT_0 + i, flags, pred);
	}
      else
	need_barrier = rws_access_reg (x, flags, pred);
      break;

    case MEM:
      /* Find the regs used in memory address computation.  */
      new_flags.is_write = 0;
      need_barrier = rtx_needs_barrier (XEXP (x, 0), new_flags, pred);
      break;

    case CONST_INT:   case CONST_DOUBLE:  case CONST_VECTOR:
    case SYMBOL_REF:  case LABEL_REF:     case CONST:
      break;

      /* Operators with side-effects.  */
    case POST_INC:    case POST_DEC:
      gcc_assert (GET_CODE (XEXP (x, 0)) == REG);

      new_flags.is_write = 0;
      need_barrier  = rws_access_reg (XEXP (x, 0), new_flags, pred);
      new_flags.is_write = 1;
      need_barrier |= rws_access_reg (XEXP (x, 0), new_flags, pred);
      break;

    case POST_MODIFY:
      gcc_assert (GET_CODE (XEXP (x, 0)) == REG);

      new_flags.is_write = 0;
      need_barrier  = rws_access_reg (XEXP (x, 0), new_flags, pred);
      need_barrier |= rtx_needs_barrier (XEXP (x, 1), new_flags, pred);
      new_flags.is_write = 1;
      need_barrier |= rws_access_reg (XEXP (x, 0), new_flags, pred);
      break;

      /* Handle common unary and binary ops for efficiency.  */
    case COMPARE:  case PLUS:    case MINUS:   case MULT:      case DIV:
    case MOD:      case UDIV:    case UMOD:    case AND:       case IOR:
    case XOR:      case ASHIFT:  case ROTATE:  case ASHIFTRT:  case LSHIFTRT:
    case ROTATERT: case SMIN:    case SMAX:    case UMIN:      case UMAX:
    case NE:       case EQ:      case GE:      case GT:        case LE:
    case LT:       case GEU:     case GTU:     case LEU:       case LTU:
      need_barrier = rtx_needs_barrier (XEXP (x, 0), new_flags, pred);
      need_barrier |= rtx_needs_barrier (XEXP (x, 1), new_flags, pred);
      break;

    case NEG:      case NOT:	        case SIGN_EXTEND:     case ZERO_EXTEND:
    case TRUNCATE: case FLOAT_EXTEND:   case FLOAT_TRUNCATE:  case FLOAT:
    case FIX:      case UNSIGNED_FLOAT: case UNSIGNED_FIX:    case ABS:
    case SQRT:     case FFS:		case POPCOUNT:
      need_barrier = rtx_needs_barrier (XEXP (x, 0), flags, pred);
      break;

    case VEC_SELECT:
      /* VEC_SELECT's second argument is a PARALLEL with integers that
	 describe the elements selected.  On ia64, those integers are
	 always constants.  Avoid walking the PARALLEL so that we don't
	 get confused with "normal" parallels and then die.  */
      need_barrier = rtx_needs_barrier (XEXP (x, 0), flags, pred);
      break;

    case UNSPEC:
      switch (XINT (x, 1))
	{
	case UNSPEC_LTOFF_DTPMOD:
	case UNSPEC_LTOFF_DTPREL:
	case UNSPEC_DTPREL:
	case UNSPEC_LTOFF_TPREL:
	case UNSPEC_TPREL:
	case UNSPEC_PRED_REL_MUTEX:
	case UNSPEC_PIC_CALL:
        case UNSPEC_MF:
        case UNSPEC_FETCHADD_ACQ:
	case UNSPEC_BSP_VALUE:
	case UNSPEC_FLUSHRS:
	case UNSPEC_BUNDLE_SELECTOR:
          break;

	case UNSPEC_GR_SPILL:
	case UNSPEC_GR_RESTORE:
	  {
	    HOST_WIDE_INT offset = INTVAL (XVECEXP (x, 0, 1));
	    HOST_WIDE_INT bit = (offset >> 3) & 63;

	    need_barrier = rtx_needs_barrier (XVECEXP (x, 0, 0), flags, pred);
	    new_flags.is_write = (XINT (x, 1) == UNSPEC_GR_SPILL);
	    need_barrier |= rws_access_regno (AR_UNAT_BIT_0 + bit,
					      new_flags, pred);
	    break;
	  }

	case UNSPEC_FR_SPILL:
	case UNSPEC_FR_RESTORE:
	case UNSPEC_GETF_EXP:
	case UNSPEC_SETF_EXP:
        case UNSPEC_ADDP4:
	case UNSPEC_FR_SQRT_RECIP_APPROX:
	case UNSPEC_LDA:
	case UNSPEC_LDS:
	case UNSPEC_LDSA:
	case UNSPEC_CHKACLR:
        case UNSPEC_CHKS:
	  need_barrier = rtx_needs_barrier (XVECEXP (x, 0, 0), flags, pred);
	  break;

	case UNSPEC_FR_RECIP_APPROX:
	case UNSPEC_SHRP:
	case UNSPEC_COPYSIGN:
	  need_barrier = rtx_needs_barrier (XVECEXP (x, 0, 0), flags, pred);
	  need_barrier |= rtx_needs_barrier (XVECEXP (x, 0, 1), flags, pred);
	  break;

        case UNSPEC_CMPXCHG_ACQ:
	  need_barrier = rtx_needs_barrier (XVECEXP (x, 0, 1), flags, pred);
	  need_barrier |= rtx_needs_barrier (XVECEXP (x, 0, 2), flags, pred);
	  break;

	default:
	  gcc_unreachable ();
	}
      break;

    case UNSPEC_VOLATILE:
      switch (XINT (x, 1))
	{
	case UNSPECV_ALLOC:
	  /* Alloc must always be the first instruction of a group.
	     We force this by always returning true.  */
	  /* ??? We might get better scheduling if we explicitly check for
	     input/local/output register dependencies, and modify the
	     scheduler so that alloc is always reordered to the start of
	     the current group.  We could then eliminate all of the
	     first_instruction code.  */
	  rws_access_regno (AR_PFS_REGNUM, flags, pred);

	  new_flags.is_write = 1;
	  rws_access_regno (REG_AR_CFM, new_flags, pred);
	  return 1;

	case UNSPECV_SET_BSP:
	  need_barrier = 1;
          break;

	case UNSPECV_BLOCKAGE:
	case UNSPECV_INSN_GROUP_BARRIER:
	case UNSPECV_BREAK:
	case UNSPECV_PSAC_ALL:
	case UNSPECV_PSAC_NORMAL:
	  return 0;

	default:
	  gcc_unreachable ();
	}
      break;

    case RETURN:
      new_flags.is_write = 0;
      need_barrier  = rws_access_regno (REG_RP, flags, pred);
      need_barrier |= rws_access_regno (AR_PFS_REGNUM, flags, pred);

      new_flags.is_write = 1;
      need_barrier |= rws_access_regno (AR_EC_REGNUM, new_flags, pred);
      need_barrier |= rws_access_regno (REG_AR_CFM, new_flags, pred);
      break;

    default:
      format_ptr = GET_RTX_FORMAT (GET_CODE (x));
      for (i = GET_RTX_LENGTH (GET_CODE (x)) - 1; i >= 0; i--)
	switch (format_ptr[i])
	  {
	  case '0':	/* unused field */
	  case 'i':	/* integer */
	  case 'n':	/* note */
	  case 'w':	/* wide integer */
	  case 's':	/* pointer to string */
	  case 'S':	/* optional pointer to string */
	    break;

	  case 'e':
	    if (rtx_needs_barrier (XEXP (x, i), flags, pred))
	      need_barrier = 1;
	    break;

	  case 'E':
	    for (j = XVECLEN (x, i) - 1; j >= 0; --j)
	      if (rtx_needs_barrier (XVECEXP (x, i, j), flags, pred))
		need_barrier = 1;
	    break;

	  default:
	    gcc_unreachable ();
	  }
      break;
    }
  return need_barrier;
}