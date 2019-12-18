#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  symbolS ;
struct TYPE_7__ {int reg_type; char* reg_name; int /*<<< orphan*/  reg_num; } ;
typedef  TYPE_2__ reg_entry ;
struct TYPE_10__ {int code; char* str; TYPE_2__* reg; } ;
struct TYPE_9__ {size_t mem_operands; int* types; TYPE_2__ const* index_reg; int /*<<< orphan*/  reg_operands; TYPE_1__* op; TYPE_2__ const* base_reg; int /*<<< orphan*/ ** seg; } ;
struct TYPE_8__ {char* disp; int is_mem; int /*<<< orphan*/  in_bracket; int /*<<< orphan*/  in_offset; TYPE_2__* reg; } ;
struct TYPE_6__ {TYPE_2__ const* regs; } ;

/* Variables and functions */
 int BaseIndex ; 
 scalar_t__ REGNAM_AX ; 
 scalar_t__ REGNAM_EAX ; 
 int Reg16 ; 
 int SReg2 ; 
 int SReg3 ; 
 int /*<<< orphan*/  S_GET_SEGMENT (int /*<<< orphan*/ *) ; 
#define  T_BYTE 137 
#define  T_CONST 136 
#define  T_DWORD 135 
#define  T_FWORD 134 
#define  T_ID 133 
 int const T_PTR ; 
#define  T_QWORD 132 
#define  T_REG 131 
#define  T_TBYTE 130 
#define  T_WORD 129 
#define  T_XMMWORD 128 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  absolute_section ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  as_warn (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cs ; 
 TYPE_5__ cur_token ; 
 int /*<<< orphan*/  ds ; 
 int /*<<< orphan*/  es ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  fs ; 
 int /*<<< orphan*/  gs ; 
 TYPE_4__ i ; 
 scalar_t__ i386_regtab ; 
 int /*<<< orphan*/  i386_scale (char*) ; 
 int intel_bracket_expr () ; 
 int /*<<< orphan*/  intel_expr () ; 
 int /*<<< orphan*/  intel_match_token (int const) ; 
 TYPE_3__ intel_parser ; 
 int /*<<< orphan*/  intel_putback_token () ; 
 int /*<<< orphan*/  ss ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/ * symbol_find (char*) ; 
 size_t this_operand ; 
 scalar_t__ xmalloc (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
intel_e11 (void)
{
  switch (cur_token.code)
    {
    /* e11  ( expr ) */
    case '(':
      intel_match_token ('(');
      strcat (intel_parser.disp, "(");

      if (intel_expr () && intel_match_token (')'))
	{
	  strcat (intel_parser.disp, ")");
	  return 1;
	}
      return 0;

    /* e11  [ expr ] */
    case '[':
      return intel_bracket_expr ();

    /* e11  $
	    | .  */
    case '.':
      strcat (intel_parser.disp, cur_token.str);
      intel_match_token (cur_token.code);

      /* Mark as a memory operand only if it's not already known to be an
	 offset expression.  */
      if (!intel_parser.in_offset)
	intel_parser.is_mem = 1;

      return 1;

    /* e11  register  */
    case T_REG:
      {
	const reg_entry *reg = intel_parser.reg = cur_token.reg;

	intel_match_token (T_REG);

	/* Check for segment change.  */
	if (cur_token.code == ':')
	  {
	    if (!(reg->reg_type & (SReg2 | SReg3)))
	      {
		as_bad (_("`%s' is not a valid segment register"),
			reg->reg_name);
		return 0;
	      }
	    else if (i.seg[i.mem_operands])
	      as_warn (_("Extra segment override ignored"));
	    else
	      {
		if (!intel_parser.in_offset)
		  intel_parser.is_mem = 1;
		switch (reg->reg_num)
		  {
		  case 0:
		    i.seg[i.mem_operands] = &es;
		    break;
		  case 1:
		    i.seg[i.mem_operands] = &cs;
		    break;
		  case 2:
		    i.seg[i.mem_operands] = &ss;
		    break;
		  case 3:
		    i.seg[i.mem_operands] = &ds;
		    break;
		  case 4:
		    i.seg[i.mem_operands] = &fs;
		    break;
		  case 5:
		    i.seg[i.mem_operands] = &gs;
		    break;
		  }
	      }
	  }

	/* Not a segment register. Check for register scaling.  */
	else if (cur_token.code == '*')
	  {
	    if (!intel_parser.in_bracket)
	      {
		as_bad (_("Register scaling only allowed in memory operands"));
		return 0;
	      }

	    if (reg->reg_type & Reg16) /* Disallow things like [si*1]. */
	      reg = i386_regtab + REGNAM_AX + 4; /* sp is invalid as index */
	    else if (i.index_reg)
	      reg = i386_regtab + REGNAM_EAX + 4; /* esp is invalid as index */

	    /* What follows must be a valid scale.  */
	    intel_match_token ('*');
	    i.index_reg = reg;
	    i.types[this_operand] |= BaseIndex;

	    /* Set the scale after setting the register (otherwise,
	       i386_scale will complain)  */
	    if (cur_token.code == '+' || cur_token.code == '-')
	      {
		char *str, sign = cur_token.code;
		intel_match_token (cur_token.code);
		if (cur_token.code != T_CONST)
		  {
		    as_bad (_("Syntax error: Expecting a constant, got `%s'"),
			    cur_token.str);
		    return 0;
		  }
		str = (char *) xmalloc (strlen (cur_token.str) + 2);
		strcpy (str + 1, cur_token.str);
		*str = sign;
		if (!i386_scale (str))
		  return 0;
		free (str);
	      }
	    else if (!i386_scale (cur_token.str))
	      return 0;
	    intel_match_token (cur_token.code);
	  }

	/* No scaling. If this is a memory operand, the register is either a
	   base register (first occurrence) or an index register (second
	   occurrence).  */
	else if (intel_parser.in_bracket)
	  {

	    if (!i.base_reg)
	      i.base_reg = reg;
	    else if (!i.index_reg)
	      i.index_reg = reg;
	    else
	      {
		as_bad (_("Too many register references in memory operand"));
		return 0;
	      }

	    i.types[this_operand] |= BaseIndex;
	  }

	/* It's neither base nor index.  */
	else if (!intel_parser.in_offset && !intel_parser.is_mem)
	  {
	    i.types[this_operand] |= reg->reg_type & ~BaseIndex;
	    i.op[this_operand].regs = reg;
	    i.reg_operands++;
	  }
	else
	  {
	    as_bad (_("Invalid use of register"));
	    return 0;
	  }

	/* Since registers are not part of the displacement string (except
	   when we're parsing offset operands), we may need to remove any
	   preceding '+' from the displacement string.  */
	if (*intel_parser.disp != '\0'
	    && !intel_parser.in_offset)
	  {
	    char *s = intel_parser.disp;
	    s += strlen (s) - 1;
	    if (*s == '+')
	      *s = '\0';
	  }

	return 1;
      }

    /* e11  BYTE
	    | WORD
	    | DWORD
	    | FWORD
	    | QWORD
	    | TBYTE
	    | OWORD
	    | XMMWORD  */
    case T_BYTE:
    case T_WORD:
    case T_DWORD:
    case T_FWORD:
    case T_QWORD:
    case T_TBYTE:
    case T_XMMWORD:
      intel_match_token (cur_token.code);

      if (cur_token.code == T_PTR)
	return 1;

      /* It must have been an identifier.  */
      intel_putback_token ();
      cur_token.code = T_ID;
      /* FALLTHRU */

    /* e11  id
	    | constant  */
    case T_ID:
      if (!intel_parser.in_offset && intel_parser.is_mem <= 0)
	{
	  symbolS *symbolP;

	  /* The identifier represents a memory reference only if it's not
	     preceded by an offset modifier and if it's not an equate.  */
	  symbolP = symbol_find(cur_token.str);
	  if (!symbolP || S_GET_SEGMENT(symbolP) != absolute_section)
	    intel_parser.is_mem = 1;
	}
	/* FALLTHRU */

    case T_CONST:
    case '-':
    case '+':
      {
	char *save_str, sign = 0;

	/* Allow constants that start with `+' or `-'.  */
	if (cur_token.code == '-' || cur_token.code == '+')
	  {
	    sign = cur_token.code;
	    intel_match_token (cur_token.code);
	    if (cur_token.code != T_CONST)
	      {
		as_bad (_("Syntax error: Expecting a constant, got `%s'"),
			cur_token.str);
		return 0;
	      }
	  }

	save_str = (char *) xmalloc (strlen (cur_token.str) + 2);
	strcpy (save_str + !!sign, cur_token.str);
	if (sign)
	  *save_str = sign;

	/* Get the next token to check for register scaling.  */
	intel_match_token (cur_token.code);

	/* Check if this constant is a scaling factor for an
	   index register.  */
	if (cur_token.code == '*')
	  {
	    if (intel_match_token ('*') && cur_token.code == T_REG)
	      {
		const reg_entry *reg = cur_token.reg;

		if (!intel_parser.in_bracket)
		  {
		    as_bad (_("Register scaling only allowed "
			      "in memory operands"));
		    return 0;
		  }

		 /* Disallow things like [1*si].
		    sp and esp are invalid as index.  */
		if (reg->reg_type & Reg16)
		  reg = i386_regtab + REGNAM_AX + 4;
		else if (i.index_reg)
		  reg = i386_regtab + REGNAM_EAX + 4;

		/* The constant is followed by `* reg', so it must be
		   a valid scale.  */
		i.index_reg = reg;
		i.types[this_operand] |= BaseIndex;

		/* Set the scale after setting the register (otherwise,
		   i386_scale will complain)  */
		if (!i386_scale (save_str))
		  return 0;
		intel_match_token (T_REG);

		/* Since registers are not part of the displacement
		   string, we may need to remove any preceding '+' from
		   the displacement string.  */
		if (*intel_parser.disp != '\0')
		  {
		    char *s = intel_parser.disp;
		    s += strlen (s) - 1;
		    if (*s == '+')
		      *s = '\0';
		  }

		free (save_str);

		return 1;
	      }

	    /* The constant was not used for register scaling. Since we have
	       already consumed the token following `*' we now need to put it
	       back in the stream.  */
	    intel_putback_token ();
	  }

	/* Add the constant to the displacement string.  */
	strcat (intel_parser.disp, save_str);
	free (save_str);

	return 1;
      }
    }

  as_bad (_("Unrecognized token '%s'"), cur_token.str);
  return 0;
}