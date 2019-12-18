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
struct TYPE_2__ {int /*<<< orphan*/  replace; int /*<<< orphan*/  loop_depth; } ;

/* Variables and functions */
#define  ASM_OPERANDS 139 
#define  CC0 138 
#define  CLOBBER 137 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  POST_DEC 136 
#define  POST_INC 135 
#define  POST_MODIFY 134 
#define  PRE_DEC 133 
#define  PRE_INC 132 
#define  PRE_MODIFY 131 
#define  REG 130 
 size_t REGNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  REG_BASIC_BLOCK (size_t) ; 
#define  SET 129 
 int /*<<< orphan*/  SET_SRC (int /*<<< orphan*/ ) ; 
#define  UNSPEC_VOLATILE 128 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  XVECLEN (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* reg_equiv ; 
 int /*<<< orphan*/  rtx_varies_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
equiv_init_movable_p (rtx x, int regno)
{
  int i, j;
  const char *fmt;
  enum rtx_code code = GET_CODE (x);

  switch (code)
    {
    case SET:
      return equiv_init_movable_p (SET_SRC (x), regno);

    case CC0:
    case CLOBBER:
      return 0;

    case PRE_INC:
    case PRE_DEC:
    case POST_INC:
    case POST_DEC:
    case PRE_MODIFY:
    case POST_MODIFY:
      return 0;

    case REG:
      return (reg_equiv[REGNO (x)].loop_depth >= reg_equiv[regno].loop_depth
	      && reg_equiv[REGNO (x)].replace)
	     || (REG_BASIC_BLOCK (REGNO (x)) < 0 && ! rtx_varies_p (x, 0));

    case UNSPEC_VOLATILE:
      return 0;

    case ASM_OPERANDS:
      if (MEM_VOLATILE_P (x))
	return 0;

      /* Fall through.  */

    default:
      break;
    }

  fmt = GET_RTX_FORMAT (code);
  for (i = GET_RTX_LENGTH (code) - 1; i >= 0; i--)
    switch (fmt[i])
      {
      case 'e':
	if (! equiv_init_movable_p (XEXP (x, i), regno))
	  return 0;
	break;
      case 'E':
	for (j = XVECLEN (x, i) - 1; j >= 0; j--)
	  if (! equiv_init_movable_p (XVECEXP (x, i, j), regno))
	    return 0;
	break;
      }

  return 1;
}