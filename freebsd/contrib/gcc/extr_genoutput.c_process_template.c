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
struct data {char const* template; int code_number; int n_alternatives; int /*<<< orphan*/  output_format; int /*<<< orphan*/  lineno; } ;

/* Variables and functions */
 int /*<<< orphan*/  INSN_OUTPUT_FORMAT_FUNCTION ; 
 int /*<<< orphan*/  INSN_OUTPUT_FORMAT_MULTI ; 
 int /*<<< orphan*/  INSN_OUTPUT_FORMAT_SINGLE ; 
 scalar_t__ ISSPACE (char const) ; 
 int /*<<< orphan*/  IS_VSPACE (char const) ; 
 int have_error ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  print_rtx_ptr_loc (char const*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char const) ; 
 int /*<<< orphan*/  puts (char const*) ; 

__attribute__((used)) static void
process_template (struct data *d, const char *template)
{
  const char *cp;
  int i;

  /* Templates starting with * contain straight code to be run.  */
  if (template[0] == '*')
    {
      d->template = 0;
      d->output_format = INSN_OUTPUT_FORMAT_FUNCTION;

      puts ("\nstatic const char *");
      printf ("output_%d (rtx *operands ATTRIBUTE_UNUSED, rtx insn ATTRIBUTE_UNUSED)\n",
	      d->code_number);
      puts ("{");
      print_rtx_ptr_loc (template);
      puts (template + 1);
      puts ("}");
    }

  /* If the assembler code template starts with a @ it is a newline-separated
     list of assembler code templates, one for each alternative.  */
  else if (template[0] == '@')
    {
      d->template = 0;
      d->output_format = INSN_OUTPUT_FORMAT_MULTI;

      printf ("\nstatic const char * const output_%d[] = {\n", d->code_number);

      for (i = 0, cp = &template[1]; *cp; )
	{
	  const char *ep, *sp;

	  while (ISSPACE (*cp))
	    cp++;

	  printf ("  \"");

	  for (ep = sp = cp; !IS_VSPACE (*ep) && *ep != '\0'; ++ep)
	    if (!ISSPACE (*ep))
	      sp = ep + 1;

	  if (sp != ep)
	    message_with_line (d->lineno,
			       "trailing whitespace in output template");

	  while (cp < sp)
	    {
	      putchar (*cp);
	      cp++;
	    }

	  printf ("\",\n");
	  i++;
	}
      if (i == 1)
	message_with_line (d->lineno,
			   "'@' is redundant for output template with single alternative");
      if (i != d->n_alternatives)
	{
	  message_with_line (d->lineno,
			     "wrong number of alternatives in the output template");
	  have_error = 1;
	}

      printf ("};\n");
    }
  else
    {
      d->template = template;
      d->output_format = INSN_OUTPUT_FORMAT_SINGLE;
    }
}