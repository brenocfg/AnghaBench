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
typedef  int /*<<< orphan*/  rtx ;

/* Variables and functions */
#define  CONST 137 
 int const CONST_INT ; 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 136 
 int const PLUS ; 
 int /*<<< orphan*/  Pmode ; 
#define  SYMBOL_REF 135 
 int /*<<< orphan*/  SYMBOL_REF_FAR_ADDR_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 scalar_t__ TARGET_64BIT ; 
 scalar_t__ TARGET_MACHO ; 
 int /*<<< orphan*/  TLS_MODEL_INITIAL_EXEC ; 
 int /*<<< orphan*/  TLS_MODEL_LOCAL_DYNAMIC ; 
 int /*<<< orphan*/  TLS_MODEL_LOCAL_EXEC ; 
 int const UNSPEC ; 
#define  UNSPEC_DTPOFF 134 
#define  UNSPEC_GOT 133 
#define  UNSPEC_GOTNTPOFF 132 
#define  UNSPEC_GOTOFF 131 
 int UNSPEC_GOTPCREL ; 
#define  UNSPEC_GOTTPOFF 130 
#define  UNSPEC_INDNTPOFF 129 
#define  UNSPEC_NTPOFF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ darwin_local_data_pic (int /*<<< orphan*/ ) ; 
 int local_symbolic_operand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
legitimate_pic_address_disp_p (rtx disp)
{
  bool saw_plus;

  /* In 64bit mode we can allow direct addresses of symbols and labels
     when they are not dynamic symbols.  */
  if (TARGET_64BIT)
    {
      rtx op0 = disp, op1;

      switch (GET_CODE (disp))
	{
	case LABEL_REF:
	  return true;

	case CONST:
	  if (GET_CODE (XEXP (disp, 0)) != PLUS)
	    break;
	  op0 = XEXP (XEXP (disp, 0), 0);
	  op1 = XEXP (XEXP (disp, 0), 1);
	  if (GET_CODE (op1) != CONST_INT
	      || INTVAL (op1) >= 16*1024*1024
	      || INTVAL (op1) < -16*1024*1024)
            break;
	  if (GET_CODE (op0) == LABEL_REF)
	    return true;
	  if (GET_CODE (op0) != SYMBOL_REF)
	    break;
	  /* FALLTHRU */

	case SYMBOL_REF:
	  /* TLS references should always be enclosed in UNSPEC.  */
	  if (SYMBOL_REF_TLS_MODEL (op0))
	    return false;
	  if (!SYMBOL_REF_FAR_ADDR_P (op0) && SYMBOL_REF_LOCAL_P (op0))
	    return true;
	  break;

	default:
	  break;
	}
    }
  if (GET_CODE (disp) != CONST)
    return 0;
  disp = XEXP (disp, 0);

  if (TARGET_64BIT)
    {
      /* We are unsafe to allow PLUS expressions.  This limit allowed distance
         of GOT tables.  We should not need these anyway.  */
      if (GET_CODE (disp) != UNSPEC
	  || (XINT (disp, 1) != UNSPEC_GOTPCREL
	      && XINT (disp, 1) != UNSPEC_GOTOFF))
	return 0;

      if (GET_CODE (XVECEXP (disp, 0, 0)) != SYMBOL_REF
	  && GET_CODE (XVECEXP (disp, 0, 0)) != LABEL_REF)
	return 0;
      return 1;
    }

  saw_plus = false;
  if (GET_CODE (disp) == PLUS)
    {
      if (GET_CODE (XEXP (disp, 1)) != CONST_INT)
	return 0;
      disp = XEXP (disp, 0);
      saw_plus = true;
    }

  if (TARGET_MACHO && darwin_local_data_pic (disp))
    return 1;

  if (GET_CODE (disp) != UNSPEC)
    return 0;

  switch (XINT (disp, 1))
    {
    case UNSPEC_GOT:
      if (saw_plus)
	return false;
      return GET_CODE (XVECEXP (disp, 0, 0)) == SYMBOL_REF;
    case UNSPEC_GOTOFF:
      /* Refuse GOTOFF in 64bit mode since it is always 64bit when used.
	 While ABI specify also 32bit relocation but we don't produce it in
	 small PIC model at all.  */
      if ((GET_CODE (XVECEXP (disp, 0, 0)) == SYMBOL_REF
	   || GET_CODE (XVECEXP (disp, 0, 0)) == LABEL_REF)
	  && !TARGET_64BIT)
        return local_symbolic_operand (XVECEXP (disp, 0, 0), Pmode);
      return false;
    case UNSPEC_GOTTPOFF:
    case UNSPEC_GOTNTPOFF:
    case UNSPEC_INDNTPOFF:
      if (saw_plus)
	return false;
      disp = XVECEXP (disp, 0, 0);
      return (GET_CODE (disp) == SYMBOL_REF
	      && SYMBOL_REF_TLS_MODEL (disp) == TLS_MODEL_INITIAL_EXEC);
    case UNSPEC_NTPOFF:
      disp = XVECEXP (disp, 0, 0);
      return (GET_CODE (disp) == SYMBOL_REF
	      && SYMBOL_REF_TLS_MODEL (disp) == TLS_MODEL_LOCAL_EXEC);
    case UNSPEC_DTPOFF:
      disp = XVECEXP (disp, 0, 0);
      return (GET_CODE (disp) == SYMBOL_REF
	      && SYMBOL_REF_TLS_MODEL (disp) == TLS_MODEL_LOCAL_DYNAMIC);
    }

  return 0;
}