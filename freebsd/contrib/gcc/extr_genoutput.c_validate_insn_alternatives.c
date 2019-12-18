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
struct data {int n_operands; int n_alternatives; int /*<<< orphan*/  lineno; TYPE_1__* operand; } ;
struct TYPE_2__ {int n_alternatives; char* constraint; } ;

/* Variables and functions */
 int CONSTRAINT_LEN (char,char const*) ; 
 scalar_t__ ISDIGIT (char const) ; 
 scalar_t__ ISSPACE (char) ; 
 int have_error ; 
 char* indep_constraints ; 
 int mdep_constraint_len (char const*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  message_with_line (int /*<<< orphan*/ ,char*,char const,...) ; 
 scalar_t__ strchr (char*,char const) ; 

__attribute__((used)) static void
validate_insn_alternatives (struct data *d)
{
  int n = 0, start;

  /* Make sure all the operands have the same number of alternatives
     in their constraints.  Let N be that number.  */
  for (start = 0; start < d->n_operands; start++)
    if (d->operand[start].n_alternatives > 0)
      {
	int len, i;
	const char *p;
	char c;
	int which_alternative = 0;
	int alternative_count_unsure = 0;

	for (p = d->operand[start].constraint; (c = *p); p += len)
	  {
#ifdef USE_MD_CONSTRAINTS
	    if (ISSPACE (c) || strchr (indep_constraints, c))
	      len = 1;
	    else if (ISDIGIT (c))
	      {
		const char *q = p;
		do
		  q++;
		while (ISDIGIT (*q));
		len = q - p;
	      }
	    else
	      len = mdep_constraint_len (p, d->lineno, start);
#else
	    len = CONSTRAINT_LEN (c, p);

	    if (len < 1 || (len > 1 && strchr (",#*+=&%!0123456789", c)))
	      {
		message_with_line (d->lineno,
				   "invalid length %d for char '%c' in alternative %d of operand %d",
				    len, c, which_alternative, start);
		len = 1;
		have_error = 1;
	      }
#endif

	    if (c == ',')
	      {
	        which_alternative++;
		continue;
	      }

	    for (i = 1; i < len; i++)
	      if (p[i] == '\0')
		{
		  message_with_line (d->lineno,
				     "NUL in alternative %d of operand %d",
				     which_alternative, start);
		  alternative_count_unsure = 1;
		  break;
		}
	      else if (strchr (",#*", p[i]))
		{
		  message_with_line (d->lineno,
				     "'%c' in alternative %d of operand %d",
				     p[i], which_alternative, start);
		  alternative_count_unsure = 1;
		}
	  }
	if (alternative_count_unsure)
	  have_error = 1;
	else if (n == 0)
	  n = d->operand[start].n_alternatives;
	else if (n != d->operand[start].n_alternatives)
	  {
	    message_with_line (d->lineno,
			       "wrong number of alternatives in operand %d",
			       start);
	    have_error = 1;
	  }
      }

  /* Record the insn's overall number of alternatives.  */
  d->n_alternatives = n;
}