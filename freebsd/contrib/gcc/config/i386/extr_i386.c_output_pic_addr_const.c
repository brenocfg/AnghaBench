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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  ASM_GENERATE_INTERNAL_LABEL (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ASM_INTEL ; 
 int /*<<< orphan*/  ASSEMBLER_DIALECT ; 
#define  CODE_LABEL 146 
 int /*<<< orphan*/  CODE_LABEL_NUMBER (int /*<<< orphan*/ ) ; 
#define  CONST 145 
#define  CONST_DOUBLE 144 
 scalar_t__ CONST_DOUBLE_HIGH (int /*<<< orphan*/ ) ; 
 scalar_t__ CONST_DOUBLE_LOW (int /*<<< orphan*/ ) ; 
#define  CONST_INT 143 
 int const GET_CODE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GET_MODE (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 scalar_t__ INTVAL (int /*<<< orphan*/ ) ; 
#define  LABEL_REF 142 
 int /*<<< orphan*/  MACHOPIC_INDIRECT ; 
 int /*<<< orphan*/  MACHOPIC_UNDEFINED_FUNCTION ; 
#define  MINUS 141 
#define  PC 140 
#define  PLUS 139 
#define  SYMBOL_REF 138 
 int /*<<< orphan*/  SYMBOL_REF_DECL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SYMBOL_REF_LOCAL_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TARGET_64BIT ; 
 int /*<<< orphan*/  TARGET_MACHO ; 
#define  UNSPEC 137 
#define  UNSPEC_DTPOFF 136 
#define  UNSPEC_GOT 135 
#define  UNSPEC_GOTNTPOFF 134 
#define  UNSPEC_GOTOFF 133 
#define  UNSPEC_GOTPCREL 132 
#define  UNSPEC_GOTTPOFF 131 
#define  UNSPEC_INDNTPOFF 130 
#define  UNSPEC_NTPOFF 129 
#define  UNSPEC_TPOFF 128 
 int /*<<< orphan*/  VOIDmode ; 
 int /*<<< orphan*/  XEXP (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  XINT (int /*<<< orphan*/ ,int) ; 
 char* XSTR (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  XVECEXP (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int XVECLEN (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * asm_out_file ; 
 int /*<<< orphan*/  assemble_name (int /*<<< orphan*/ *,char const*) ; 
 int flag_pic ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,unsigned long,...) ; 
 int /*<<< orphan*/  fputs (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gcc_assert (int) ; 
 int /*<<< orphan*/  machopic_classify_symbol (int /*<<< orphan*/ ) ; 
 char* machopic_indirection_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mark_decl_referenced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
output_pic_addr_const (FILE *file, rtx x, int code)
{
  char buf[256];

  switch (GET_CODE (x))
    {
    case PC:
      gcc_assert (flag_pic);
      putc ('.', file);
      break;

    case SYMBOL_REF:
      if (! TARGET_MACHO || TARGET_64BIT)
	output_addr_const (file, x);
      else
	{
	  const char *name = XSTR (x, 0);

	  /* Mark the decl as referenced so that cgraph will output the function.  */
	  if (SYMBOL_REF_DECL (x))
	    mark_decl_referenced (SYMBOL_REF_DECL (x));

#if TARGET_MACHO
	  if (MACHOPIC_INDIRECT
	      && machopic_classify_symbol (x) == MACHOPIC_UNDEFINED_FUNCTION)
	    name = machopic_indirection_name (x, /*stub_p=*/true);
#endif
	  assemble_name (file, name);
	}
      if (!TARGET_MACHO && code == 'P' && ! SYMBOL_REF_LOCAL_P (x))
	fputs ("@PLT", file);
      break;

    case LABEL_REF:
      x = XEXP (x, 0);
      /* FALLTHRU */
    case CODE_LABEL:
      ASM_GENERATE_INTERNAL_LABEL (buf, "L", CODE_LABEL_NUMBER (x));
      assemble_name (asm_out_file, buf);
      break;

    case CONST_INT:
      fprintf (file, HOST_WIDE_INT_PRINT_DEC, INTVAL (x));
      break;

    case CONST:
      /* This used to output parentheses around the expression,
	 but that does not work on the 386 (either ATT or BSD assembler).  */
      output_pic_addr_const (file, XEXP (x, 0), code);
      break;

    case CONST_DOUBLE:
      if (GET_MODE (x) == VOIDmode)
	{
	  /* We can use %d if the number is <32 bits and positive.  */
	  if (CONST_DOUBLE_HIGH (x) || CONST_DOUBLE_LOW (x) < 0)
	    fprintf (file, "0x%lx%08lx",
		     (unsigned long) CONST_DOUBLE_HIGH (x),
		     (unsigned long) CONST_DOUBLE_LOW (x));
	  else
	    fprintf (file, HOST_WIDE_INT_PRINT_DEC, CONST_DOUBLE_LOW (x));
	}
      else
	/* We can't handle floating point constants;
	   PRINT_OPERAND must handle them.  */
	output_operand_lossage ("floating constant misused");
      break;

    case PLUS:
      /* Some assemblers need integer constants to appear first.  */
      if (GET_CODE (XEXP (x, 0)) == CONST_INT)
	{
	  output_pic_addr_const (file, XEXP (x, 0), code);
	  putc ('+', file);
	  output_pic_addr_const (file, XEXP (x, 1), code);
	}
      else
	{
	  gcc_assert (GET_CODE (XEXP (x, 1)) == CONST_INT);
	  output_pic_addr_const (file, XEXP (x, 1), code);
	  putc ('+', file);
	  output_pic_addr_const (file, XEXP (x, 0), code);
	}
      break;

    case MINUS:
      if (!TARGET_MACHO)
	putc (ASSEMBLER_DIALECT == ASM_INTEL ? '(' : '[', file);
      output_pic_addr_const (file, XEXP (x, 0), code);
      putc ('-', file);
      output_pic_addr_const (file, XEXP (x, 1), code);
      if (!TARGET_MACHO)
	putc (ASSEMBLER_DIALECT == ASM_INTEL ? ')' : ']', file);
      break;

     case UNSPEC:
       gcc_assert (XVECLEN (x, 0) == 1);
       output_pic_addr_const (file, XVECEXP (x, 0, 0), code);
       switch (XINT (x, 1))
	{
	case UNSPEC_GOT:
	  fputs ("@GOT", file);
	  break;
	case UNSPEC_GOTOFF:
	  fputs ("@GOTOFF", file);
	  break;
	case UNSPEC_GOTPCREL:
	  fputs ("@GOTPCREL(%rip)", file);
	  break;
	case UNSPEC_GOTTPOFF:
	  /* FIXME: This might be @TPOFF in Sun ld too.  */
	  fputs ("@GOTTPOFF", file);
	  break;
	case UNSPEC_TPOFF:
	  fputs ("@TPOFF", file);
	  break;
	case UNSPEC_NTPOFF:
	  if (TARGET_64BIT)
	    fputs ("@TPOFF", file);
	  else
	    fputs ("@NTPOFF", file);
	  break;
	case UNSPEC_DTPOFF:
	  fputs ("@DTPOFF", file);
	  break;
	case UNSPEC_GOTNTPOFF:
	  if (TARGET_64BIT)
	    fputs ("@GOTTPOFF(%rip)", file);
	  else
	    fputs ("@GOTNTPOFF", file);
	  break;
	case UNSPEC_INDNTPOFF:
	  fputs ("@INDNTPOFF", file);
	  break;
	default:
	  output_operand_lossage ("invalid UNSPEC as operand");
	  break;
	}
       break;

    default:
      output_operand_lossage ("invalid expression as operand");
    }
}