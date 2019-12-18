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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;

/* Variables and functions */
#define  ASM_OPERANDS 147 
 scalar_t__ ASM_OPERANDS_INPUT (scalar_t__,int) ; 
 scalar_t__ ASM_OPERANDS_INPUT_CONSTRAINT (scalar_t__,int) ; 
 int ASM_OPERANDS_INPUT_LENGTH (scalar_t__) ; 
 scalar_t__ ASM_OPERANDS_OUTPUT_CONSTRAINT (scalar_t__) ; 
 scalar_t__ ASM_OPERANDS_OUTPUT_IDX (scalar_t__) ; 
 scalar_t__ ASM_OPERANDS_TEMPLATE (scalar_t__) ; 
 int BLKmode ; 
#define  CALL 146 
#define  CC0 145 
 int /*<<< orphan*/  CLASS_LIKELY_SPILLED_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (scalar_t__) ; 
#define  CONST_DOUBLE 144 
 scalar_t__ CONST_DOUBLE_HIGH (scalar_t__) ; 
 scalar_t__ CONST_DOUBLE_LOW (scalar_t__) ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (scalar_t__) ; 
#define  CONST_INT 143 
#define  CONST_VECTOR 142 
 scalar_t__ CONST_VECTOR_ELT (scalar_t__,int) ; 
 int CONST_VECTOR_NUNITS (scalar_t__) ; 
 unsigned int FIRST_PSEUDO_REGISTER ; 
 int GET_CODE (scalar_t__) ; 
 int GET_MODE (scalar_t__) ; 
 int /*<<< orphan*/  GET_MODE_CLASS (int) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 scalar_t__ INTVAL (scalar_t__) ; 
#define  LABEL_REF 141 
#define  MEM 140 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
 int /*<<< orphan*/  MEM_READONLY_P (scalar_t__) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (scalar_t__) ; 
 int /*<<< orphan*/  MODE_CC ; 
#define  PC 139 
#define  POST_DEC 138 
#define  POST_INC 137 
#define  POST_MODIFY 136 
#define  PRE_DEC 135 
#define  PRE_INC 134 
#define  PRE_MODIFY 133 
#define  REG 132 
 unsigned int REGNO (scalar_t__) ; 
 int /*<<< orphan*/  REGNO_REG_CLASS (unsigned int) ; 
 int /*<<< orphan*/  REG_P (scalar_t__) ; 
 scalar_t__ REG_QTY (unsigned int) ; 
 int /*<<< orphan*/  SMALL_REGISTER_CLASSES ; 
#define  SUBREG 131 
 unsigned int SUBREG_BYTE (scalar_t__) ; 
 scalar_t__ SUBREG_REG (scalar_t__) ; 
#define  SYMBOL_REF 130 
 unsigned int UNITS_PER_WORD ; 
#define  UNSPEC_VOLATILE 129 
#define  USE 128 
 int VOIDmode ; 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XINT (scalar_t__,int) ; 
 scalar_t__ XSTR (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 scalar_t__ arg_pointer_rtx ; 
 int /*<<< orphan*/ * fixed_regs ; 
 scalar_t__ frame_pointer_rtx ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 int /*<<< orphan*/ * global_regs ; 
 scalar_t__ hard_frame_pointer_rtx ; 
 unsigned int hash_rtx_string (scalar_t__) ; 
 scalar_t__ pic_offset_table_rtx ; 
 unsigned int real_hash (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reload_completed ; 
 scalar_t__ stack_pointer_rtx ; 

unsigned
hash_rtx (rtx x, enum machine_mode mode, int *do_not_record_p,
	  int *hash_arg_in_memory_p, bool have_reg_qty)
{
  int i, j;
  unsigned hash = 0;
  enum rtx_code code;
  const char *fmt;

  /* Used to turn recursion into iteration.  We can't rely on GCC's
     tail-recursion elimination since we need to keep accumulating values
     in HASH.  */
 repeat:
  if (x == 0)
    return hash;

  code = GET_CODE (x);
  switch (code)
    {
    case REG:
      {
	unsigned int regno = REGNO (x);

	if (!reload_completed)
	  {
	    /* On some machines, we can't record any non-fixed hard register,
	       because extending its life will cause reload problems.  We
	       consider ap, fp, sp, gp to be fixed for this purpose.

	       We also consider CCmode registers to be fixed for this purpose;
	       failure to do so leads to failure to simplify 0<100 type of
	       conditionals.

	       On all machines, we can't record any global registers.
	       Nor should we record any register that is in a small
	       class, as defined by CLASS_LIKELY_SPILLED_P.  */
	    bool record;

	    if (regno >= FIRST_PSEUDO_REGISTER)
	      record = true;
	    else if (x == frame_pointer_rtx
		     || x == hard_frame_pointer_rtx
		     || x == arg_pointer_rtx
		     || x == stack_pointer_rtx
		     || x == pic_offset_table_rtx)
	      record = true;
	    else if (global_regs[regno])
	      record = false;
	    else if (fixed_regs[regno])
	      record = true;
	    else if (GET_MODE_CLASS (GET_MODE (x)) == MODE_CC)
	      record = true;
	    else if (SMALL_REGISTER_CLASSES)
	      record = false;
	    else if (CLASS_LIKELY_SPILLED_P (REGNO_REG_CLASS (regno)))
	      record = false;
	    else
	      record = true;

	    if (!record)
	      {
		*do_not_record_p = 1;
		return 0;
	      }
	  }

	hash += ((unsigned int) REG << 7);
        hash += (have_reg_qty ? (unsigned) REG_QTY (regno) : regno);
	return hash;
      }

    /* We handle SUBREG of a REG specially because the underlying
       reg changes its hash value with every value change; we don't
       want to have to forget unrelated subregs when one subreg changes.  */
    case SUBREG:
      {
	if (REG_P (SUBREG_REG (x)))
	  {
	    hash += (((unsigned int) SUBREG << 7)
		     + REGNO (SUBREG_REG (x))
		     + (SUBREG_BYTE (x) / UNITS_PER_WORD));
	    return hash;
	  }
	break;
      }

    case CONST_INT:
      hash += (((unsigned int) CONST_INT << 7) + (unsigned int) mode
               + (unsigned int) INTVAL (x));
      return hash;

    case CONST_DOUBLE:
      /* This is like the general case, except that it only counts
	 the integers representing the constant.  */
      hash += (unsigned int) code + (unsigned int) GET_MODE (x);
      if (GET_MODE (x) != VOIDmode)
	hash += real_hash (CONST_DOUBLE_REAL_VALUE (x));
      else
	hash += ((unsigned int) CONST_DOUBLE_LOW (x)
		 + (unsigned int) CONST_DOUBLE_HIGH (x));
      return hash;

    case CONST_VECTOR:
      {
	int units;
	rtx elt;

	units = CONST_VECTOR_NUNITS (x);

	for (i = 0; i < units; ++i)
	  {
	    elt = CONST_VECTOR_ELT (x, i);
	    hash += hash_rtx (elt, GET_MODE (elt), do_not_record_p,
			      hash_arg_in_memory_p, have_reg_qty);
	  }

	return hash;
      }

      /* Assume there is only one rtx object for any given label.  */
    case LABEL_REF:
      /* We don't hash on the address of the CODE_LABEL to avoid bootstrap
	 differences and differences between each stage's debugging dumps.  */
	 hash += (((unsigned int) LABEL_REF << 7)
		  + CODE_LABEL_NUMBER (XEXP (x, 0)));
      return hash;

    case SYMBOL_REF:
      {
	/* Don't hash on the symbol's address to avoid bootstrap differences.
	   Different hash values may cause expressions to be recorded in
	   different orders and thus different registers to be used in the
	   final assembler.  This also avoids differences in the dump files
	   between various stages.  */
	unsigned int h = 0;
	const unsigned char *p = (const unsigned char *) XSTR (x, 0);

	while (*p)
	  h += (h << 7) + *p++; /* ??? revisit */

	hash += ((unsigned int) SYMBOL_REF << 7) + h;
	return hash;
      }

    case MEM:
      /* We don't record if marked volatile or if BLKmode since we don't
	 know the size of the move.  */
      if (MEM_VOLATILE_P (x) || GET_MODE (x) == BLKmode)
	{
	  *do_not_record_p = 1;
	  return 0;
	}
      if (hash_arg_in_memory_p && !MEM_READONLY_P (x))
	*hash_arg_in_memory_p = 1;

      /* Now that we have already found this special case,
	 might as well speed it up as much as possible.  */
      hash += (unsigned) MEM;
      x = XEXP (x, 0);
      goto repeat;

    case USE:
      /* A USE that mentions non-volatile memory needs special
	 handling since the MEM may be BLKmode which normally
	 prevents an entry from being made.  Pure calls are
	 marked by a USE which mentions BLKmode memory.
	 See calls.c:emit_call_1.  */
      if (MEM_P (XEXP (x, 0))
	  && ! MEM_VOLATILE_P (XEXP (x, 0)))
	{
	  hash += (unsigned) USE;
	  x = XEXP (x, 0);

	  if (hash_arg_in_memory_p && !MEM_READONLY_P (x))
	    *hash_arg_in_memory_p = 1;

	  /* Now that we have already found this special case,
	     might as well speed it up as much as possible.  */
	  hash += (unsigned) MEM;
	  x = XEXP (x, 0);
	  goto repeat;
	}
      break;

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case PRE_MODIFY:
    case POST_MODIFY:
    case PC:
    case CC0:
    case CALL:
    case UNSPEC_VOLATILE:
      *do_not_record_p = 1;
      return 0;

    case ASM_OPERANDS:
      if (MEM_VOLATILE_P (x))
	{
	  *do_not_record_p = 1;
	  return 0;
	}
      else
	{
	  /* We don't want to take the filename and line into account.  */
	  hash += (unsigned) code + (unsigned) GET_MODE (x)
	    + hash_rtx_string (ASM_OPERANDS_TEMPLATE (x))
	    + hash_rtx_string (ASM_OPERANDS_OUTPUT_CONSTRAINT (x))
	    + (unsigned) ASM_OPERANDS_OUTPUT_IDX (x);

	  if (ASM_OPERANDS_INPUT_LENGTH (x))
	    {
	      for (i = 1; i < ASM_OPERANDS_INPUT_LENGTH (x); i++)
		{
		  hash += (hash_rtx (ASM_OPERANDS_INPUT (x, i),
				     GET_MODE (ASM_OPERANDS_INPUT (x, i)),
				     do_not_record_p, hash_arg_in_memory_p,
				     have_reg_qty)
			   + hash_rtx_string
				(ASM_OPERANDS_INPUT_CONSTRAINT (x, i)));
		}

	      hash += hash_rtx_string (ASM_OPERANDS_INPUT_CONSTRAINT (x, 0));
	      x = ASM_OPERANDS_INPUT (x, 0);
	      mode = GET_MODE (x);
	      goto repeat;
	    }

	  return hash;
	}
      break;

    default:
      break;
    }

  i = GET_RTX_LENGTH (code) - 1;
  hash += (unsigned) code + (unsigned) GET_MODE (x);
  fmt = GET_RTX_FORMAT (code);
  for (; i >= 0; i--)
    {
      switch (fmt[i])
	{
	case 'e':
	  /* If we are about to do the last recursive call
	     needed at this level, change it into iteration.
	     This function  is called enough to be worth it.  */
	  if (i == 0)
	    {
	      x = XEXP (x, i);
	      goto repeat;
	    }

	  hash += hash_rtx (XEXP (x, i), 0, do_not_record_p,
			    hash_arg_in_memory_p, have_reg_qty);
	  break;

	case 'E':
	  for (j = 0; j < XVECLEN (x, i); j++)
	    hash += hash_rtx (XVECEXP (x, i, j), 0, do_not_record_p,
			      hash_arg_in_memory_p, have_reg_qty);
	  break;

	case 's':
	  hash += hash_rtx_string (XSTR (x, i));
	  break;

	case 'i':
	  hash += (unsigned int) XINT (x, i);
	  break;

	case '0': case 't':
	  /* Unused.  */
	  break;

	default:
	  gcc_unreachable ();
	}
    }

  return hash;
}