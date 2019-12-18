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

/* Variables and functions */
#define  CC0 137 
#define  CODE_LABEL 136 
#define  CONST_DOUBLE 135 
#define  CONST_INT 134 
#define  CONST_VECTOR 133 
 int GET_CODE (scalar_t__) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
#define  MEM 132 
 int /*<<< orphan*/  MEM_P (scalar_t__) ; 
#define  PC 131 
#define  REG 130 
#define  SET 129 
 scalar_t__ SET_DEST (scalar_t__) ; 
 scalar_t__ SET_SRC (scalar_t__) ; 
#define  SYMBOL_REF 128 
 scalar_t__ XEXP (scalar_t__,int) ; 
 scalar_t__ XVECEXP (scalar_t__,int,int) ; 
 int XVECLEN (scalar_t__,int) ; 
 int /*<<< orphan*/  rtx_equal_p (scalar_t__,scalar_t__) ; 

int
count_occurrences (rtx x, rtx find, int count_dest)
{
  int i, j;
  enum rtx_code code;
  const char *format_ptr;
  int count;

  if (x == find)
    return 1;

  code = GET_CODE (x);

  switch (code)
    {
    case REG:
    case CONST_INT:
    case CONST_DOUBLE:
    case CONST_VECTOR:
    case SYMBOL_REF:
    case CODE_LABEL:
    case PC:
    case CC0:
      return 0;

    case MEM:
      if (MEM_P (find) && rtx_equal_p (x, find))
	return 1;
      break;

    case SET:
      if (SET_DEST (x) == find && ! count_dest)
	return count_occurrences (SET_SRC (x), find, count_dest);
      break;

    default:
      break;
    }

  format_ptr = GET_RTX_FORMAT (code);
  count = 0;

  for (i = 0; i < GET_RTX_LENGTH (code); i++)
    {
      switch (*format_ptr++)
	{
	case 'e':
	  count += count_occurrences (XEXP (x, i), find, count_dest);
	  break;

	case 'E':
	  for (j = 0; j < XVECLEN (x, i); j++)
	    count += count_occurrences (XVECEXP (x, i, j), find, count_dest);
	  break;
	}
    }
  return count;
}