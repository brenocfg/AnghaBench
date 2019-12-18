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
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  CC0 139 
#define  CLOBBER 138 
#define  CONST 137 
#define  CONST_DOUBLE 136 
#define  CONST_INT 135 
#define  CONST_VECTOR 134 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE_SIZE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  LABEL_REF 133 
#define  PC 132 
#define  REG 131 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_P (int /*<<< orphan*/ ) ; 
#define  SUBREG 130 
 int /*<<< orphan*/  SUBREG_REG (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 129 
#define  USE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * reg_max_ref_width ; 

__attribute__((used)) static void
scan_paradoxical_subregs (rtx x)
{
  int i;
  const char *fmt;
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case REG:
    case CONST_INT:
    case CONST:
    case SYMBOL_REF:
    case LABEL_REF:
    case CONST_DOUBLE:
    case CONST_VECTOR: /* shouldn't happen, but just in case.  */
    case CC0:
    case PC:
    case USE:
    case CLOBBER:
      return;

    case SUBREG:
      if (REG_P (SUBREG_REG (x))
	  && (GET_MODE_SIZE (GET_MODE (x))
	      > reg_max_ref_width[REGNO (SUBREG_REG (x))]))
	reg_max_ref_width[REGNO (SUBREG_REG (x))]
	  = GET_MODE_SIZE (GET_MODE (x));
      return;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    {
      if (fmt[i] == 'e')
	scan_paradoxical_subregs (XEXP (x, i));
      else if (fmt[i] == 'E')
	{
	  int j;
	  for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	    scan_paradoxical_subregs (XVECEXP (x, i, j));
	}
    }
}