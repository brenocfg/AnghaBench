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
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_2__ {int /*<<< orphan*/  replacement; } ;

/* Variables and functions */
#define  CC0 140 
#define  CONST 139 
#define  CONST_DOUBLE 138 
#define  CONST_INT 137 
#define  CONST_VECTOR 136 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  HIGH 135 
#define  LABEL_REF 134 
#define  LO_SUM 133 
#define  MEM 132 
 int /*<<< orphan*/  MEM_P (int /*<<< orphan*/ ) ; 
#define  PC 131 
#define  REG 130 
 size_t REGNO (int /*<<< orphan*/ ) ; 
#define  SET 129 
 int /*<<< orphan*/  SET_DEST (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* reg_equiv ; 
 int /*<<< orphan*/  rtx_varies_p ; 
 int /*<<< orphan*/  true_dependence (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
memref_referenced_p (rtx memref, rtx x)
{
  int i, j;
  const char *fmt;
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case CONST_INT:
    case CONST:
    case LABEL_REF:
    case SYMBOL_REF:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case PC:
    case CC0:
    case HIGH:
    case LO_SUM:
      return 0;

    case REG:
      return (reg_equiv[REGNO (x)].replacement
	      && memref_referenced_p (memref,
				      reg_equiv[REGNO (x)].replacement));

    case MEM:
      if (true_dependence (memref, VOIDmode, x, rtx_varies_p))
	return 1;
      break;

    case SET:
      /* If we are setting a MEM, it doesn't count (its address does), but any
	 other SET_DEST that has a MEM in it is referencing the MEM.  */
      if (MEM_P (SET_DEST (x)))
	{
	  if (memref_referenced_p (memref, XEXP (SET_DEST (x), 0)))
	    return 1;
	}
      else if (memref_referenced_p (memref, SET_DEST (x)))
	return 1;

      return memref_referenced_p (memref, SET_SRC (x));

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    switch (fmt[i])
      {
      case 'e':
	if (memref_referenced_p (memref, XEXP (x, i)))
	  return 1;
	break;
      case 'E':
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  if (memref_referenced_p (memref, XVECEXP (x, i, j)))
	    return 1;
	break;
      }

  return 0;
}