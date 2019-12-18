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
#define  CONST 132 
 int CONST_INT ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 131 
 int PLUS ; 
#define  SYMBOL_REF 130 
 int /*<<< orphan*/  SYMBOL_REF_TLS_MODEL (int /*<<< orphan*/ ) ; 
 int TARGET_64BIT ; 
 int /*<<< orphan*/  TLS_MODEL_LOCAL_EXEC ; 
 int UNSPEC ; 
#define  UNSPEC_GOTOFF 129 
#define  UNSPEC_TPOFF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int legitimate_pic_address_disp_p (int /*<<< orphan*/ ) ; 

bool
legitimate_pic_operand_p (rtx x)
{
  rtx inner;

  switch (GET_CODE (x))
    {
    case CONST:
      inner = XEXP (x, 0);
      if (GET_CODE (inner) == PLUS
	  && GET_CODE (XEXP (inner, 1)) == CONST_INT)
	inner = XEXP (inner, 0);

      /* Only some unspecs are valid as "constants".  */
      if (GET_CODE (inner) == UNSPEC)
	switch (XINT (inner, 1))
	  {
	  case UNSPEC_GOTOFF:
	    return TARGET_64BIT;
	  case UNSPEC_TPOFF:
	    x = XVECEXP (inner, 0, 0);
	    return (GET_CODE (x) == SYMBOL_REF
		    && SYMBOL_REF_TLS_MODEL (x) == TLS_MODEL_LOCAL_EXEC);
	  default:
	    return false;
	  }
      /* FALLTHRU */

    case SYMBOL_REF:
    case LABEL_REF:
      return legitimate_pic_address_disp_p (x);

    default:
      return true;
    }
}