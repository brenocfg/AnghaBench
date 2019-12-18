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
struct TYPE_2__ {int replace; } ;

/* Variables and functions */
#define  CC0 137 
#define  CONST 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_VECTOR 133 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  HIGH 132 
#define  LABEL_REF 131 
#define  PC 130 
#define  REG 129 
 size_t REGNO (int /*<<< orphan*/ ) ; 
#define  SYMBOL_REF 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* reg_equiv ; 

__attribute__((used)) static int
contains_replace_regs (rtx x)
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
      return 0;

    case REG:
      return reg_equiv[REGNO (x)].replace;

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    switch (fmt[i])
      {
      case 'e':
	if (contains_replace_regs (XEXP (x, i)))
	  return 1;
	break;
      case 'E':
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  if (contains_replace_regs (XVECEXP (x, i, j)))
	    return 1;
	break;
      }

  return 0;
}