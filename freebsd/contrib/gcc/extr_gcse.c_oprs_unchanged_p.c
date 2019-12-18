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
struct reg_avail_info {int /*<<< orphan*/  first_set; int /*<<< orphan*/  last_set; int /*<<< orphan*/  last_bb; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
#define  ADDR_DIFF_VEC 145 
#define  ADDR_VEC 144 
#define  CC0 143 
#define  CONST 142 
#define  CONST_DOUBLE 141 
#define  CONST_INT 140 
#define  CONST_VECTOR 139 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  INSN_CUID (scalar_t__) ; 
#define  LABEL_REF 138 
#define  MEM 137 
#define  PC 136 
#define  POST_DEC 135 
#define  POST_INC 134 
#define  POST_MODIFY 133 
#define  PRE_DEC 132 
#define  PRE_INC 131 
#define  PRE_MODIFY 130 
#define  REG 129 
 size_t REGNO (scalar_t__) ; 
#define  SYMBOL_REF 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  current_bb ; 
 int /*<<< orphan*/  load_killed_in_block_p (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int) ; 
 struct reg_avail_info* reg_avail_info ; 

__attribute__((used)) static int
oprs_unchanged_p (rtx x, rtx insn, int avail_p)
{
  int i, j;
  enum rtx_code code;
  const char *fmt;

  if (x == 0)
    return 1;

  code = GET_CODE (x);
  switch (code)
    {
    case REG:
      {
	struct reg_avail_info *info = &reg_avail_info[REGNO (x)];

	if (info->last_bb != current_bb)
	  return 1;
	if (avail_p)
	  return info->last_set < INSN_CUID (insn);
	else
	  return info->first_set >= INSN_CUID (insn);
      }

    case MEM:
      if (load_killed_in_block_p (current_bb, INSN_CUID (insn),
				  x, avail_p))
	return 0;
      else
	return oprs_unchanged_p (XEXP (x, 0), insn, avail_p);

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case PRE_MODIFY:
    case POST_MODIFY:
      return 0;

    case PC:
    case CC0: /*FIXME*/
    case CONST:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case LABEL_REF:
    case ADDR_VEC:
    case ADDR_DIFF_VEC:
      return 1;

    default:
      break;
    }

  for (i = GET_RTX_LENGTH (code) - 1, fmt = GET_RTX_FORMAT (code); i >= 0; i--)
    {
      if (fmt[i] == 'e')
	{
	  /* If we are about to do the last recursive call needed at this
	     level, change it into iteration.  This function is called enough
	     to be worth it.  */
	  if (i == 0)
	    return oprs_unchanged_p (XEXP (x, i), insn, avail_p);

	  else if (! oprs_unchanged_p (XEXP (x, i), insn, avail_p))
	    return 0;
	}
      else if (fmt[i] == 'E')
	for (j = 0; j < XVECLEN (x, i); j++)
	  if (! oprs_unchanged_p (XVECEXP (x, i, j), insn, avail_p))
	    return 0;
    }

  return 1;
}