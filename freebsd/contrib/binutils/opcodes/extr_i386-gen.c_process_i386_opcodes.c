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
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (char**) ; 
 scalar_t__ ISSPACE (char) ; 
 int MAX_OPERANDS ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  fail (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fgets (char*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 char* next_field (char*,char**) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 char* remove_leading_whitespaces (char*) ; 
 int /*<<< orphan*/  remove_trailing_whitespaces (char*) ; 
 int strlen (char*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static void
process_i386_opcodes (void)
{
  FILE *fp = fopen ("i386-opc.tbl", "r");
  char buf[2048];
  unsigned int i;
  char *str, *p, *last;
  char *name, *operands, *base_opcode, *extension_opcode;
  char *cpu_flags, *opcode_modifier, *operand_types [MAX_OPERANDS];

  if (fp == NULL)
    fail (_("can't find i386-opc.tbl for reading\n"));

  printf ("\n/* i386 opcode table.  */\n\n");
  printf ("const template i386_optab[] =\n{\n");

  while (!feof (fp))
    {
      if (fgets (buf, sizeof (buf), fp) == NULL)
	break;

      p = remove_leading_whitespaces (buf);

      /* Skip comments.  */
      str = strstr (p, "//");
      if (str != NULL)
	str[0] = '\0';

      /* Remove trailing white spaces.  */
      remove_trailing_whitespaces (p);

      switch (p[0])
	{
	case '#':
	  printf ("%s\n", p);
	case '\0':
	  continue;
	  break;
	default:
	  break;
	}

      last = p + strlen (p);

      /* Find name.  */
      name = next_field (p, &str);

      if (str >= last)
	abort ();

      /* Find number of operands.  */
      operands = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find base_opcode.  */
      base_opcode = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find extension_opcode.  */
      extension_opcode = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find cpu_flags.  */
      cpu_flags = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Find opcode_modifier.  */
      opcode_modifier = next_field (str, &str);

      if (str >= last)
	abort ();

      /* Remove the first {.  */
      str = remove_leading_whitespaces (str);
      if (*str != '{')
	abort ();
      str = remove_leading_whitespaces (str + 1);

      i = strlen (str);

      /* There are at least "X}".  */
      if (i < 2)
	abort ();

      /* Remove trailing white spaces and }. */
      do
	{
	  i--;
	  if (ISSPACE (str[i]) || str[i] == '}')
	    str[i] = '\0';
	  else
	    break;
	}
      while (i != 0);

      last = str + i;

      /* Find operand_types.  */
      for (i = 0; i < ARRAY_SIZE (operand_types); i++)
	{
	  if (str >= last)
	    {
	      operand_types [i] = NULL;
	      break;
	    }

	  operand_types [i] = next_field (str, &str);
	  if (*operand_types[i] == '0')
	    {
	      if (i != 0)
		operand_types[i] = NULL;
	      break;
	    }
	}

      printf ("  { \"%s\", %s, %s, %s, %s,\n",
	      name, operands, base_opcode, extension_opcode,
	      cpu_flags);

      printf ("    %s,\n", opcode_modifier);

      printf ("    { ");

      for (i = 0; i < ARRAY_SIZE (operand_types); i++)
	{
	  if (operand_types[i] == NULL
	      || *operand_types[i] == '0')
	    {
	      if (i == 0)
		printf ("0");
	      break;
	    }

	  if (i != 0)
	    printf (",\n      ");

	  printf ("%s", operand_types[i]);
	}
      printf (" } },\n");
    }

  printf ("  { NULL, 0, 0, 0, 0, 0, { 0 } }\n");
  printf ("};\n");
}