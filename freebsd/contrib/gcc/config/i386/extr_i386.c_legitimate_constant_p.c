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
#define  CONST 135 
 int /*<<< orphan*/  CONST0_RTX (int /*<<< orphan*/ ) ; 
#define  CONST_DOUBLE 134 
 int CONST_INT ; 
#define  CONST_VECTOR 133 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int LABEL_REF ; 
 int PLUS ; 
#define  SYMBOL_REF 132 
 int /*<<< orphan*/  SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_MACHO ; 
 int /*<<< orphan*/  TImode ; 
 int /*<<< orphan*/  TLS_MODEL_LOCAL_DYNAMIC ; 
 int /*<<< orphan*/  TLS_MODEL_LOCAL_EXEC ; 
 int UNSPEC ; 
#define  UNSPEC_DTPOFF 131 
#define  UNSPEC_GOTOFF 130 
#define  UNSPEC_NTPOFF 129 
#define  UNSPEC_TPOFF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  darwin_local_data_pic (int /*<<< orphan*/ ) ; 

bool
legitimate_constant_p (rtx x)
{
  switch (GET_CODE (x))
    {
    case CONST:
      x = XEXP (x, 0);

      if (GET_CODE (x) == PLUS)
	{
	  if (GET_CODE (XEXP (x, 1)) != CONST_INT)
	    return false;
	  x = XEXP (x, 0);
	}

      if (TARGET_MACHO && darwin_local_data_pic (x))
	return true;

      /* Only some unspecs are valid as "constants".  */
      if (GET_CODE (x) == UNSPEC)
	switch (XINT (x, 1))
	  {
	  case UNSPEC_GOTOFF:
	    return TARGET_64BIT;
	  case UNSPEC_TPOFF:
	  case UNSPEC_NTPOFF:
	    x = XVECEXP (x, 0, 0);
	    return (GET_CODE (x) == SYMBOL_REF
		    && SYMBOL_REF_TLS_MODEL (x) == TLS_MODEL_LOCAL_EXEC);
	  case UNSPEC_DTPOFF:
	    x = XVECEXP (x, 0, 0);
	    return (GET_CODE (x) == SYMBOL_REF
		    && SYMBOL_REF_TLS_MODEL (x) == TLS_MODEL_LOCAL_DYNAMIC);
	  default:
	    return false;
	  }

      /* We must have drilled down to a symbol.  */
      if (GET_CODE (x) == LABEL_REF)
	return true;
      if (GET_CODE (x) != SYMBOL_REF)
	return false;
      /* FALLTHRU */

    case SYMBOL_REF:
      /* TLS symbols are never valid.  */
      if (SYMBOL_REF_TLS_MODEL (x))
	return false;
      break;

    case CONST_DOUBLE:
      if (GET_MODE (x) == TImode
	  && x != CONST0_RTX (TImode)
          && !TARGET_64BIT)
	return false;
      break;

    case CONST_VECTOR:
      if (x == CONST0_RTX (GET_MODE (x)))
	return true;
      return false;

    default:
      break;
    }

  /* Otherwise we handle everything else in the move patterns.  */
  return true;
}