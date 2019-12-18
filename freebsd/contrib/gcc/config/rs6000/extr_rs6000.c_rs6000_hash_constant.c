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
typedef  enum machine_mode { ____Placeholder_machine_mode } machine_mode ;
typedef  int /*<<< orphan*/  HOST_WIDE_INT ;

/* Variables and functions */
 size_t CHAR_BIT ; 
#define  CODE_LABEL 130 
#define  CONST_DOUBLE 129 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 int GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int /*<<< orphan*/  INSN_UID (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 128 
 int VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int) ; 
 size_t XWINT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 unsigned int real_hash (int /*<<< orphan*/ ) ; 
 void* strlen (char const*) ; 

__attribute__((used)) static unsigned
rs6000_hash_constant (rtx k)
{
  enum rtx_code code = GET_CODE (k);
  enum machine_mode mode = GET_MODE (k);
  unsigned result = (code << 3) ^ mode;
  const char *format;
  int flen, fidx;

  format = GET_RTX_FORMAT (code);
  flen = strlen (format);
  fidx = 0;

  switch (code)
    {
    case LABEL_REF:
      return result * 1231 + (unsigned) INSN_UID (XEXP (k, 0));

    case CONST_DOUBLE:
      if (mode != VOIDmode)
	return real_hash (CONST_DOUBLE_REAL_VALUE (k)) * result;
      flen = 2;
      break;

    case CODE_LABEL:
      fidx = 3;
      break;

    default:
      break;
    }

  for (; fidx < flen; fidx++)
    switch (format[fidx])
      {
      case 's':
	{
	  unsigned i, len;
	  const char *str = XSTR (k, fidx);
	  len = strlen (str);
	  result = result * 613 + len;
	  for (i = 0; i < len; i++)
	    result = result * 613 + (unsigned) str[i];
	  break;
	}
      case 'u':
      case 'e':
	result = result * 1231 + rs6000_hash_constant (XEXP (k, fidx));
	break;
      case 'i':
      case 'n':
	result = result * 613 + (unsigned) XINT (k, fidx);
	break;
      case 'w':
	if (sizeof (unsigned) >= sizeof (HOST_WIDE_INT))
	  result = result * 613 + (unsigned) XWINT (k, fidx);
	else
	  {
	    size_t i;
	    for (i = 0; i < sizeof (HOST_WIDE_INT) / sizeof (unsigned); i++)
	      result = result * 613 + (unsigned) (XWINT (k, fidx)
						  >> CHAR_BIT * i);
	  }
	break;
      case '0':
	break;
      default:
	gcc_unreachable ();
      }

  return result;
}