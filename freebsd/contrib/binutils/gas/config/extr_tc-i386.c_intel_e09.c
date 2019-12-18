#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {char code; } ;
struct TYPE_11__ {TYPE_1__* start; } ;
struct TYPE_10__ {int* types; char suffix; scalar_t__ base_reg; } ;
struct TYPE_9__ {int op_modifier; int got_a_float; char* next_operand; char* op_string; scalar_t__ in_offset; scalar_t__ in_bracket; int /*<<< orphan*/  disp; } ;
struct TYPE_8__ {scalar_t__ code; int /*<<< orphan*/  str; } ;
struct TYPE_7__ {char* name; int opcode_modifier; int base_opcode; int* operand_types; } ;

/* Variables and functions */
 char BYTE_MNEM_SUFFIX ; 
 scalar_t__ CODE_16BIT ; 
 int /*<<< orphan*/  DATA_PREFIX_OPCODE ; 
 int Jump ; 
 int JumpAbsolute ; 
 int JumpDword ; 
 int JumpInterSegment ; 
 char LONG_DOUBLE_MNEM_SUFFIX ; 
 char LONG_MNEM_SUFFIX ; 
 int NUM_ADDRESS_REGS ; 
 char QWORD_MNEM_SUFFIX ; 
 scalar_t__ REGNAM_AL ; 
 char SHORT_MNEM_SUFFIX ; 
 scalar_t__ T_BYTE ; 
 int T_CONST ; 
 scalar_t__ T_DWORD ; 
 scalar_t__ T_FWORD ; 
 char T_NIL ; 
 int T_OFFSET ; 
 char T_PTR ; 
 scalar_t__ T_QWORD ; 
 scalar_t__ T_REG ; 
 int T_SHORT ; 
 scalar_t__ T_TBYTE ; 
 scalar_t__ T_WORD ; 
 scalar_t__ T_XMMWORD ; 
 char WORD_MNEM_SUFFIX ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  add_prefix (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 TYPE_6__ cur_token ; 
 TYPE_5__* current_templates ; 
 scalar_t__ flag_code ; 
 TYPE_4__ i ; 
 scalar_t__ i386_regtab ; 
 int /*<<< orphan*/  intel_e10 () ; 
 int intel_match_token (char) ; 
 TYPE_3__ intel_parser ; 
 int /*<<< orphan*/  intel_putback_token () ; 
 TYPE_2__ prev_token ; 
 int /*<<< orphan*/  strcat (int /*<<< orphan*/ ,char*) ; 
 size_t this_operand ; 

__attribute__((used)) static int
intel_e09 (void)
{
  int nregs = ~NUM_ADDRESS_REGS;
  int in_offset = 0;

  for (;;)
    {
      /* Don't consume constants here.  */
      if (cur_token.code == '+' || cur_token.code == '-')
	{
	  /* Need to look one token ahead - if the next token
	     is a constant, the current token is its sign.  */
	  int next_code;

	  intel_match_token (cur_token.code);
	  next_code = cur_token.code;
	  intel_putback_token ();
	  if (next_code == T_CONST)
	    break;
	}

      /* e09  OFFSET e09  */
      if (cur_token.code == T_OFFSET)
	{
	  if (!in_offset++)
	    ++intel_parser.in_offset;
	}

      /* e09  SHORT e09  */
      else if (cur_token.code == T_SHORT)
	intel_parser.op_modifier |= 1 << T_SHORT;

      /* e09  + e09  */
      else if (cur_token.code == '+')
	strcat (intel_parser.disp, "+");

      /* e09  - e09
	      | ~ e09
	      | NOT e09  */
      else if (cur_token.code == '-' || cur_token.code == '~')
	{
	  char str[2];

	  if (nregs < 0)
	    nregs = ~nregs;
	  str[0] = cur_token.code;
	  str[1] = 0;
	  strcat (intel_parser.disp, str);
	}

      /* e09  e10 e09'  */
      else
	break;

      intel_match_token (cur_token.code);
    }

  for (;;)
    {
      if (!intel_e10 ())
	return 0;

      /* e09'  PTR e10 e09' */
      if (cur_token.code == T_PTR)
	{
	  char suffix;

	  if (prev_token.code == T_BYTE)
	    suffix = BYTE_MNEM_SUFFIX;

	  else if (prev_token.code == T_WORD)
	    {
	      if (current_templates->start->name[0] == 'l'
		  && current_templates->start->name[2] == 's'
		  && current_templates->start->name[3] == 0)
		suffix = BYTE_MNEM_SUFFIX; /* so it will cause an error */
	      else if (intel_parser.got_a_float == 2)	/* "fi..." */
		suffix = SHORT_MNEM_SUFFIX;
	      else
		suffix = WORD_MNEM_SUFFIX;
	    }

	  else if (prev_token.code == T_DWORD)
	    {
	      if (current_templates->start->name[0] == 'l'
		  && current_templates->start->name[2] == 's'
		  && current_templates->start->name[3] == 0)
		suffix = WORD_MNEM_SUFFIX;
	      else if (flag_code == CODE_16BIT
		       && (current_templates->start->opcode_modifier
			   & (Jump | JumpDword)))
		suffix = LONG_DOUBLE_MNEM_SUFFIX;
	      else if (intel_parser.got_a_float == 1)	/* "f..." */
		suffix = SHORT_MNEM_SUFFIX;
	      else
		suffix = LONG_MNEM_SUFFIX;
	    }

	  else if (prev_token.code == T_FWORD)
	    {
	      if (current_templates->start->name[0] == 'l'
		  && current_templates->start->name[2] == 's'
		  && current_templates->start->name[3] == 0)
		suffix = LONG_MNEM_SUFFIX;
	      else if (!intel_parser.got_a_float)
		{
		  if (flag_code == CODE_16BIT)
		    add_prefix (DATA_PREFIX_OPCODE);
		  suffix = LONG_DOUBLE_MNEM_SUFFIX;
		}
	      else
		suffix = BYTE_MNEM_SUFFIX; /* so it will cause an error */
	    }

	  else if (prev_token.code == T_QWORD)
	    {
	      if (intel_parser.got_a_float == 1)	/* "f..." */
		suffix = LONG_MNEM_SUFFIX;
	      else
		suffix = QWORD_MNEM_SUFFIX;
	    }

	  else if (prev_token.code == T_TBYTE)
	    {
	      if (intel_parser.got_a_float == 1)
		suffix = LONG_DOUBLE_MNEM_SUFFIX;
	      else
		suffix = BYTE_MNEM_SUFFIX; /* so it will cause an error */
	    }

	  else if (prev_token.code == T_XMMWORD)
	    {
	      /* XXX ignored for now, but accepted since gcc uses it */
	      suffix = 0;
	    }

	  else
	    {
	      as_bad (_("Unknown operand modifier `%s'"), prev_token.str);
	      return 0;
	    }

	  /* Operands for jump/call using 'ptr' notation denote absolute
	     addresses.  */
	  if (current_templates->start->opcode_modifier & (Jump | JumpDword))
	    i.types[this_operand] |= JumpAbsolute;

	  if (current_templates->start->base_opcode == 0x8d /* lea */)
	    ;
	  else if (!i.suffix)
	    i.suffix = suffix;
	  else if (i.suffix != suffix)
	    {
	      as_bad (_("Conflicting operand modifiers"));
	      return 0;
	    }

	}

      /* e09'  : e10 e09'  */
      else if (cur_token.code == ':')
	{
	  if (prev_token.code != T_REG)
	    {
	      /* While {call,jmp} SSSS:OOOO is MASM syntax only when SSSS is a
		 segment/group identifier (which we don't have), using comma
		 as the operand separator there is even less consistent, since
		 there all branches only have a single operand.  */
	      if (this_operand != 0
		  || intel_parser.in_offset
		  || intel_parser.in_bracket
		  || (!(current_templates->start->opcode_modifier
			& (Jump|JumpDword|JumpInterSegment))
		      && !(current_templates->start->operand_types[0]
			   & JumpAbsolute)))
		return intel_match_token (T_NIL);
	      /* Remember the start of the 2nd operand and terminate 1st
		 operand here.
		 XXX This isn't right, yet (when SSSS:OOOO is right operand of
		 another expression), but it gets at least the simplest case
		 (a plain number or symbol on the left side) right.  */
	      intel_parser.next_operand = intel_parser.op_string;
	      *--intel_parser.op_string = '\0';
	      return intel_match_token (':');
	    }
	}

      /* e09'  Empty  */
      else
	break;

      intel_match_token (cur_token.code);

    }

  if (in_offset)
    {
      --intel_parser.in_offset;
      if (nregs < 0)
	nregs = ~nregs;
      if (NUM_ADDRESS_REGS > nregs)
	{
	  as_bad (_("Invalid operand to `OFFSET'"));
	  return 0;
	}
      intel_parser.op_modifier |= 1 << T_OFFSET;
    }

  if (nregs >= 0 && NUM_ADDRESS_REGS > nregs)
    i.base_reg = i386_regtab + REGNAM_AL + 3; /* bl is invalid as base */
  return 1;
}