#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;
struct TYPE_3__ {unsigned int value; } ;
typedef  TYPE_1__ cselib_val ;

/* Variables and functions */
#define  ASM_OPERANDS 145 
#define  CALL 144 
#define  CC0 143 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
#define  CONST_DOUBLE 142 
 scalar_t__ CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_DOUBLE_REAL_VALUE (int /*<<< orphan*/ ) ; 
#define  CONST_INT 141 
#define  CONST_VECTOR 140 
 int /*<<< orphan*/  CONST_VECTOR_ELT (int /*<<< orphan*/ ,int) ; 
 int CONST_VECTOR_NUNITS (int /*<<< orphan*/ ) ; 
 int GET_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ GET_MODE (int /*<<< orphan*/ ) ; 
 char* GET_RTX_FORMAT (int) ; 
 int GET_RTX_LENGTH (int) ; 
 int /*<<< orphan*/  INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 139 
#define  MEM 138 
 int /*<<< orphan*/  MEM_VOLATILE_P (int /*<<< orphan*/ ) ; 
#define  PC 137 
#define  POST_DEC 136 
#define  POST_INC 135 
#define  POST_MODIFY 134 
#define  PRE_DEC 133 
#define  PRE_INC 132 
#define  PRE_MODIFY 131 
#define  REG 130 
#define  SYMBOL_REF 129 
#define  UNSPEC_VOLATILE 128 
 scalar_t__ VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 unsigned int XINT (int /*<<< orphan*/ ,int) ; 
 scalar_t__ XSTR (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int,int) ; 
 int XVECLEN (int /*<<< orphan*/ ,int) ; 
 TYPE_1__* cselib_lookup (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 unsigned int real_hash (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned int
cselib_hash_rtx (rtx x, int create)
{
  cselib_val *e;
  int i, j;
  enum rtx_code code;
  const char *fmt;
  unsigned int hash = 0;

  code = GET_CODE (x);
  hash += (unsigned) code + (unsigned) GET_MODE (x);

  switch (code)
    {
    case MEM:
    case REG:
      e = cselib_lookup (x, GET_MODE (x), create);
      if (! e)
	return 0;

      return e->value;

    case CONST_INT:
      hash += ((unsigned) CONST_INT << 7) + INTVAL (x);
      return hash ? hash : (unsigned int) CONST_INT;

    case CONST_DOUBLE:
      /* This is like the general case, except that it only counts
	 the integers representing the constant.  */
      hash += (unsigned) code + (unsigned) GET_MODE (x);
      if (GET_MODE (x) != VOIDmode)
	hash += real_hash (CONST_DOUBLE_REAL_VALUE (x));
      else
	hash += ((unsigned) CONST_DOUBLE_LOW (x)
		 + (unsigned) CONST_DOUBLE_HIGH (x));
      return hash ? hash : (unsigned int) CONST_DOUBLE;

    case CONST_VECTOR:
      {
	int units;
	rtx elt;

	units = CONST_VECTOR_NUNITS (x);

	for (i = 0; i < units; ++i)
	  {
	    elt = CONST_VECTOR_ELT (x, i);
	    hash += cselib_hash_rtx (elt, 0);
	  }

	return hash;
      }

      /* Assume there is only one rtx object for any given label.  */
    case LABEL_REF:
      /* We don't hash on the address of the CODE_LABEL to avoid bootstrap
	 differences and differences between each stage's debugging dumps.  */
      hash += (((unsigned int) LABEL_REF << 7)
	       + CODE_LABEL_NUMBER (XEXP (x, 0)));
      return hash ? hash : (unsigned int) LABEL_REF;

    case SYMBOL_REF:
      {
	/* Don't hash on the symbol's address to avoid bootstrap differences.
	   Different hash values may cause expressions to be recorded in
	   different orders and thus different registers to be used in the
	   final assembler.  This also avoids differences in the dump files
	   between various stages.  */
	unsigned int h = 0;
	const unsigned char *p = (const unsigned char *) XSTR (x, 0);

	while (*p)
	  h += (h << 7) + *p++; /* ??? revisit */

	hash += ((unsigned int) SYMBOL_REF << 7) + h;
	return hash ? hash : (unsigned int) SYMBOL_REF;
      }

    case PRE_DEC:
    case PRE_INC:
    case POST_DEC:
    case POST_INC:
    case POST_MODIFY:
    case PRE_MODIFY:
    case PC:
    case CC0:
    case CALL:
    case UNSPEC_VOLATILE:
      return 0;

    case ASM_OPERANDS:
      if (MEM_VOLATILE_P (x))
	return 0;

      break;

    default:
      break;
    }

  i = GET_RTX_LENGTH (code) - 1;
  fmt = GET_RTX_FORMAT (code);
  for (; i >= 0; i--)
    {
      switch (fmt[i])
	{
	case 'e':
	  {
	    rtx tem = XEXP (x, i);
	    unsigned int tem_hash = cselib_hash_rtx (tem, create);
	    
	    if (tem_hash == 0)
	      return 0;
	    
	    hash += tem_hash;
	  }
	  break;
	case 'E':
	  for (j = 0; j < XVECLEN (x, i); j++)
	    {
	      unsigned int tem_hash
		= cselib_hash_rtx (XVECEXP (x, i, j), create);
	      
	      if (tem_hash == 0)
		return 0;
	      
	      hash += tem_hash;
	    }
	  break;

	case 's':
	  {
	    const unsigned char *p = (const unsigned char *) XSTR (x, i);
	    
	    if (p)
	      while (*p)
		hash += *p++;
	    break;
	  }
	  
	case 'i':
	  hash += XINT (x, i);
	  break;

	case '0':
	case 't':
	  /* unused */
	  break;
	  
	default:
	  gcc_unreachable ();
	}
    }

  return hash ? hash : 1 + (unsigned int) GET_CODE (x);
}