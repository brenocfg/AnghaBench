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
struct intel_token {char code; char* str; int /*<<< orphan*/  const* reg; } ;
typedef  int /*<<< orphan*/  reg_entry ;
struct TYPE_2__ {char* op_string; } ;

/* Variables and functions */
 char T_BYTE ; 
 char T_CONST ; 
 char T_DWORD ; 
 char T_FWORD ; 
 void* T_ID ; 
 char T_NIL ; 
 void* T_OFFSET ; 
 char T_PTR ; 
 char T_QWORD ; 
 char T_REG ; 
 void* T_SHL ; 
 char T_SHORT ; 
 void* T_SHR ; 
 char T_TBYTE ; 
 char T_WORD ; 
 char T_XMMWORD ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  as_bad (int /*<<< orphan*/ ,...) ; 
 struct intel_token cur_token ; 
 int /*<<< orphan*/  free (char*) ; 
 TYPE_1__ intel_parser ; 
 scalar_t__ is_identifier_char (char) ; 
 scalar_t__ is_space_char (char) ; 
 int /*<<< orphan*/  memcpy (char*,char*,size_t) ; 
 int /*<<< orphan*/ * parse_register (float*,char**) ; 
 struct intel_token prev_token ; 
 scalar_t__ strcasecmp (char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strchr (char*,char) ; 
 int strlen (char*) ; 
 scalar_t__ strncasecmp (char*,char*,int) ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static void
intel_get_token (void)
{
  char *end_op;
  const reg_entry *reg;
  struct intel_token new_token;

  new_token.code = T_NIL;
  new_token.reg = NULL;
  new_token.str = NULL;

  /* Free the memory allocated to the previous token and move
     cur_token to prev_token.  */
  if (prev_token.str)
    free (prev_token.str);

  prev_token = cur_token;

  /* Skip whitespace.  */
  while (is_space_char (*intel_parser.op_string))
    intel_parser.op_string++;

  /* Return an empty token if we find nothing else on the line.  */
  if (*intel_parser.op_string == '\0')
    {
      cur_token = new_token;
      return;
    }

  /* The new token cannot be larger than the remainder of the operand
     string.  */
  new_token.str = (char *) xmalloc (strlen (intel_parser.op_string) + 1);
  new_token.str[0] = '\0';

  if (strchr ("0123456789", *intel_parser.op_string))
    {
      char *p = new_token.str;
      char *q = intel_parser.op_string;
      new_token.code = T_CONST;

      /* Allow any kind of identifier char to encompass floating point and
	 hexadecimal numbers.  */
      while (is_identifier_char (*q))
	*p++ = *q++;
      *p = '\0';

      /* Recognize special symbol names [0-9][bf].  */
      if (strlen (intel_parser.op_string) == 2
	  && (intel_parser.op_string[1] == 'b'
	      || intel_parser.op_string[1] == 'f'))
	new_token.code = T_ID;
    }

  else if ((reg = parse_register (intel_parser.op_string, &end_op)) != NULL)
    {
      size_t len = end_op - intel_parser.op_string;

      new_token.code = T_REG;
      new_token.reg = reg;

      memcpy (new_token.str, intel_parser.op_string, len);
      new_token.str[len] = '\0';
    }

  else if (is_identifier_char (*intel_parser.op_string))
    {
      char *p = new_token.str;
      char *q = intel_parser.op_string;

      /* A '.' or '$' followed by an identifier char is an identifier.
	 Otherwise, it's operator '.' followed by an expression.  */
      if ((*q == '.' || *q == '$') && !is_identifier_char (*(q + 1)))
	{
	  new_token.code = '.';
	  new_token.str[0] = '.';
	  new_token.str[1] = '\0';
	}
      else
	{
	  while (is_identifier_char (*q) || *q == '@')
	    *p++ = *q++;
	  *p = '\0';

	  if (strcasecmp (new_token.str, "NOT") == 0)
	    new_token.code = '~';

	  else if (strcasecmp (new_token.str, "MOD") == 0)
	    new_token.code = '%';

	  else if (strcasecmp (new_token.str, "AND") == 0)
	    new_token.code = '&';

	  else if (strcasecmp (new_token.str, "OR") == 0)
	    new_token.code = '|';

	  else if (strcasecmp (new_token.str, "XOR") == 0)
	    new_token.code = '^';

	  else if (strcasecmp (new_token.str, "SHL") == 0)
	    new_token.code = T_SHL;

	  else if (strcasecmp (new_token.str, "SHR") == 0)
	    new_token.code = T_SHR;

	  else if (strcasecmp (new_token.str, "BYTE") == 0)
	    new_token.code = T_BYTE;

	  else if (strcasecmp (new_token.str, "WORD") == 0)
	    new_token.code = T_WORD;

	  else if (strcasecmp (new_token.str, "DWORD") == 0)
	    new_token.code = T_DWORD;

	  else if (strcasecmp (new_token.str, "FWORD") == 0)
	    new_token.code = T_FWORD;

	  else if (strcasecmp (new_token.str, "QWORD") == 0)
	    new_token.code = T_QWORD;

	  else if (strcasecmp (new_token.str, "TBYTE") == 0
		   /* XXX remove (gcc still uses it) */
		   || strcasecmp (new_token.str, "XWORD") == 0)
	    new_token.code = T_TBYTE;

	  else if (strcasecmp (new_token.str, "XMMWORD") == 0
		   || strcasecmp (new_token.str, "OWORD") == 0)
	    new_token.code = T_XMMWORD;

	  else if (strcasecmp (new_token.str, "PTR") == 0)
	    new_token.code = T_PTR;

	  else if (strcasecmp (new_token.str, "SHORT") == 0)
	    new_token.code = T_SHORT;

	  else if (strcasecmp (new_token.str, "OFFSET") == 0)
	    {
	      new_token.code = T_OFFSET;

	      /* ??? This is not mentioned in the MASM grammar but gcc
		     makes use of it with -mintel-syntax.  OFFSET may be
		     followed by FLAT:  */
	      if (strncasecmp (q, " FLAT:", 6) == 0)
		strcat (new_token.str, " FLAT:");
	    }

	  /* ??? This is not mentioned in the MASM grammar.  */
	  else if (strcasecmp (new_token.str, "FLAT") == 0)
	    {
	      new_token.code = T_OFFSET;
	      if (*q == ':')
		strcat (new_token.str, ":");
	      else
		as_bad (_("`:' expected"));
	    }

	  else
	    new_token.code = T_ID;
	}
    }

  else if (strchr ("+-/*%|&^:[]()~", *intel_parser.op_string))
    {
      new_token.code = *intel_parser.op_string;
      new_token.str[0] = *intel_parser.op_string;
      new_token.str[1] = '\0';
    }

  else if (strchr ("<>", *intel_parser.op_string)
	   && *intel_parser.op_string == *(intel_parser.op_string + 1))
    {
      new_token.code = *intel_parser.op_string == '<' ? T_SHL : T_SHR;
      new_token.str[0] = *intel_parser.op_string;
      new_token.str[1] = *intel_parser.op_string;
      new_token.str[2] = '\0';
    }

  else
    as_bad (_("Unrecognized token `%s'"), intel_parser.op_string);

  intel_parser.op_string += strlen (new_token.str);
  cur_token = new_token;
}