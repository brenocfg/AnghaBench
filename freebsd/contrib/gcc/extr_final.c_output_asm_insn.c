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
 int /*<<< orphan*/  ASM_OUTPUT_OPCODE (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  CONSTANT_ADDRESS_P (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CONST_INT ; 
 int /*<<< orphan*/  GET_CODE (int /*<<< orphan*/ ) ; 
 char* HOST_WIDE_INT_PRINT_DEC ; 
 int INTVAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ISALPHA (char const) ; 
 int /*<<< orphan*/  ISDIGIT (char const) ; 
 int MAX_RECOG_OPERANDS ; 
 int /*<<< orphan*/  NULL_RTX ; 
 int /*<<< orphan*/  PRINT_OPERAND_PUNCT_VALID_P (unsigned char) ; 
 int /*<<< orphan*/  asm_out_file ; 
 int dialect_number ; 
 scalar_t__ flag_print_asm_name ; 
 scalar_t__ flag_verbose_asm ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int insn_counter ; 
 unsigned long insn_noperands ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_addr_const (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_address (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_asm_label (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  output_asm_name () ; 
 int /*<<< orphan*/  output_asm_operand_names (int /*<<< orphan*/ *,int*,int) ; 
 int /*<<< orphan*/  output_operand (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  output_operand_lossage (char*) ; 
 int /*<<< orphan*/  putc (char,int /*<<< orphan*/ ) ; 
 unsigned long strtoul (char const*,char**,int) ; 
 int /*<<< orphan*/  this_is_asm_operands ; 

void
output_asm_insn (const char *template, rtx *operands)
{
  const char *p;
  int c;
#ifdef ASSEMBLER_DIALECT
  int dialect = 0;
#endif
  int oporder[MAX_RECOG_OPERANDS];
  char opoutput[MAX_RECOG_OPERANDS];
  int ops = 0;

  /* An insn may return a null string template
     in a case where no assembler code is needed.  */
  if (*template == 0)
    return;

  memset (opoutput, 0, sizeof opoutput);
  p = template;
  putc ('\t', asm_out_file);

#ifdef ASM_OUTPUT_OPCODE
  ASM_OUTPUT_OPCODE (asm_out_file, p);
#endif

  while ((c = *p++))
    switch (c)
      {
      case '\n':
	if (flag_verbose_asm)
	  output_asm_operand_names (operands, oporder, ops);
	if (flag_print_asm_name)
	  output_asm_name ();

	ops = 0;
	memset (opoutput, 0, sizeof opoutput);

	putc (c, asm_out_file);
#ifdef ASM_OUTPUT_OPCODE
	while ((c = *p) == '\t')
	  {
	    putc (c, asm_out_file);
	    p++;
	  }
	ASM_OUTPUT_OPCODE (asm_out_file, p);
#endif
	break;

#ifdef ASSEMBLER_DIALECT
      case '{':
	{
	  int i;

	  if (dialect)
	    output_operand_lossage ("nested assembly dialect alternatives");
	  else
	    dialect = 1;

	  /* If we want the first dialect, do nothing.  Otherwise, skip
	     DIALECT_NUMBER of strings ending with '|'.  */
	  for (i = 0; i < dialect_number; i++)
	    {
	      while (*p && *p != '}' && *p++ != '|')
		;
	      if (*p == '}')
		break;
	      if (*p == '|')
		p++;
	    }

	  if (*p == '\0')
	    output_operand_lossage ("unterminated assembly dialect alternative");
	}
	break;

      case '|':
	if (dialect)
	  {
	    /* Skip to close brace.  */
	    do
	      {
		if (*p == '\0')
		  {
		    output_operand_lossage ("unterminated assembly dialect alternative");
		    break;
		  }
	      }
	    while (*p++ != '}');
	    dialect = 0;
	  }
	else
	  putc (c, asm_out_file);
	break;

      case '}':
	if (! dialect)
	  putc (c, asm_out_file);
	dialect = 0;
	break;
#endif

      case '%':
	/* %% outputs a single %.  */
	if (*p == '%')
	  {
	    p++;
	    putc (c, asm_out_file);
	  }
	/* %= outputs a number which is unique to each insn in the entire
	   compilation.  This is useful for making local labels that are
	   referred to more than once in a given insn.  */
	else if (*p == '=')
	  {
	    p++;
	    fprintf (asm_out_file, "%d", insn_counter);
	  }
	/* % followed by a letter and some digits
	   outputs an operand in a special way depending on the letter.
	   Letters `acln' are implemented directly.
	   Other letters are passed to `output_operand' so that
	   the PRINT_OPERAND macro can define them.  */
	else if (ISALPHA (*p))
	  {
	    int letter = *p++;
	    unsigned long opnum;
	    char *endptr;

	    opnum = strtoul (p, &endptr, 10);

	    if (endptr == p)
	      output_operand_lossage ("operand number missing "
				      "after %%-letter");
	    else if (this_is_asm_operands && opnum >= insn_noperands)
	      output_operand_lossage ("operand number out of range");
	    else if (letter == 'l')
	      output_asm_label (operands[opnum]);
	    else if (letter == 'a')
	      output_address (operands[opnum]);
	    else if (letter == 'c')
	      {
		if (CONSTANT_ADDRESS_P (operands[opnum]))
		  output_addr_const (asm_out_file, operands[opnum]);
		else
		  output_operand (operands[opnum], 'c');
	      }
	    else if (letter == 'n')
	      {
		if (GET_CODE (operands[opnum]) == CONST_INT)
		  fprintf (asm_out_file, HOST_WIDE_INT_PRINT_DEC,
			   - INTVAL (operands[opnum]));
		else
		  {
		    putc ('-', asm_out_file);
		    output_addr_const (asm_out_file, operands[opnum]);
		  }
	      }
	    else
	      output_operand (operands[opnum], letter);

	    if (!opoutput[opnum])
	      oporder[ops++] = opnum;
	    opoutput[opnum] = 1;

	    p = endptr;
	    c = *p;
	  }
	/* % followed by a digit outputs an operand the default way.  */
	else if (ISDIGIT (*p))
	  {
	    unsigned long opnum;
	    char *endptr;

	    opnum = strtoul (p, &endptr, 10);
	    if (this_is_asm_operands && opnum >= insn_noperands)
	      output_operand_lossage ("operand number out of range");
	    else
	      output_operand (operands[opnum], 0);

	    if (!opoutput[opnum])
	      oporder[ops++] = opnum;
	    opoutput[opnum] = 1;

	    p = endptr;
	    c = *p;
	  }
	/* % followed by punctuation: output something for that
	   punctuation character alone, with no operand.
	   The PRINT_OPERAND macro decides what is actually done.  */
#ifdef PRINT_OPERAND_PUNCT_VALID_P
	else if (PRINT_OPERAND_PUNCT_VALID_P ((unsigned char) *p))
	  output_operand (NULL_RTX, *p++);
#endif
	else
	  output_operand_lossage ("invalid %%-code");
	break;

      default:
	putc (c, asm_out_file);
      }

  /* Write out the variable names for operands, if we know them.  */
  if (flag_verbose_asm)
    output_asm_operand_names (operands, oporder, ops);
  if (flag_print_asm_name)
    output_asm_name ();

  putc ('\n', asm_out_file);
}