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
struct data {char* name; char* filename; int lineno; int output_format; char* template; int code_number; int operand_number; int n_operands; int n_dups; int n_alternatives; struct data* next; } ;

/* Variables and functions */
#define  INSN_OUTPUT_FORMAT_FUNCTION 131 
#define  INSN_OUTPUT_FORMAT_MULTI 130 
#define  INSN_OUTPUT_FORMAT_NONE 129 
#define  INSN_OUTPUT_FORMAT_SINGLE 128 
 int /*<<< orphan*/  IS_VSPACE (char const) ; 
 int /*<<< orphan*/  gcc_unreachable () ; 
 struct data* idata ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  putchar (char const) ; 

__attribute__((used)) static void
output_insn_data (void)
{
  struct data *d;
  int name_offset = 0;
  int next_name_offset;
  const char * last_name = 0;
  const char * next_name = 0;
  struct data *n;

  for (n = idata, next_name_offset = 1; n; n = n->next, next_name_offset++)
    if (n->name)
      {
	next_name = n->name;
	break;
      }

  printf ("#if GCC_VERSION >= 2007\n__extension__\n#endif\n");
  printf ("\nconst struct insn_data insn_data[] = \n{\n");

  for (d = idata; d; d = d->next)
    {
      printf ("  /* %s:%d */\n", d->filename, d->lineno);
      printf ("  {\n");

      if (d->name)
	{
	  printf ("    \"%s\",\n", d->name);
	  name_offset = 0;
	  last_name = d->name;
	  next_name = 0;
	  for (n = d->next, next_name_offset = 1; n;
	       n = n->next, next_name_offset++)
	    {
	      if (n->name)
		{
		  next_name = n->name;
		  break;
		}
	    }
	}
      else
	{
	  name_offset++;
	  if (next_name && (last_name == 0
			    || name_offset > next_name_offset / 2))
	    printf ("    \"%s-%d\",\n", next_name,
		    next_name_offset - name_offset);
	  else
	    printf ("    \"%s+%d\",\n", last_name, name_offset);
	}

      switch (d->output_format)
	{
	case INSN_OUTPUT_FORMAT_NONE:
	  printf ("#if HAVE_DESIGNATED_INITIALIZERS\n");
	  printf ("    { 0 },\n");
	  printf ("#else\n");
	  printf ("    { 0, 0, 0 },\n");
	  printf ("#endif\n");
	  break;
	case INSN_OUTPUT_FORMAT_SINGLE:
	  {
	    const char *p = d->template;
	    char prev = 0;

	    printf ("#if HAVE_DESIGNATED_INITIALIZERS\n");
	    printf ("    { .single =\n");
	    printf ("#else\n");
	    printf ("    {\n");
	    printf ("#endif\n");
	    printf ("    \"");
	    while (*p)
	      {
		if (IS_VSPACE (*p) && prev != '\\')
		  {
		    /* Preserve two consecutive \n's or \r's, but treat \r\n
		       as a single newline.  */
		    if (*p == '\n' && prev != '\r')
		      printf ("\\n\\\n");
		  }
		else
		  putchar (*p);
		prev = *p;
		++p;
	      }
	    printf ("\",\n");
	    printf ("#if HAVE_DESIGNATED_INITIALIZERS\n");
	    printf ("    },\n");
	    printf ("#else\n");
	    printf ("    0, 0 },\n");
	    printf ("#endif\n");
	  }
	  break;
	case INSN_OUTPUT_FORMAT_MULTI:
	  printf ("#if HAVE_DESIGNATED_INITIALIZERS\n");
	  printf ("    { .multi = output_%d },\n", d->code_number);
	  printf ("#else\n");
	  printf ("    { 0, output_%d, 0 },\n", d->code_number);
	  printf ("#endif\n");
	  break;
	case INSN_OUTPUT_FORMAT_FUNCTION:
	  printf ("#if HAVE_DESIGNATED_INITIALIZERS\n");
	  printf ("    { .function = output_%d },\n", d->code_number);
	  printf ("#else\n");
	  printf ("    { 0, 0, output_%d },\n", d->code_number);
	  printf ("#endif\n");
	  break;
	default:
	  gcc_unreachable ();
	}

      if (d->name && d->name[0] != '*')
	printf ("    (insn_gen_fn) gen_%s,\n", d->name);
      else
	printf ("    0,\n");

      printf ("    &operand_data[%d],\n", d->operand_number);
      printf ("    %d,\n", d->n_operands);
      printf ("    %d,\n", d->n_dups);
      printf ("    %d,\n", d->n_alternatives);
      printf ("    %d\n", d->output_format);

      printf("  },\n");
    }
  printf ("};\n\n\n");
}