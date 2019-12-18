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
struct symtabs_and_lines {int nelts; struct symtab_and_line* sals; } ;
struct symtab_and_line {int line; scalar_t__ pc; struct symtab* symtab; } ;
struct symtab {int dummy; } ;

/* Variables and functions */
 int atoi (char*) ; 
 int /*<<< orphan*/  build_canonical_line_spec (struct symtab_and_line*,int /*<<< orphan*/ *,char***) ; 
 struct symtab* find_line_symtab (struct symtab*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_sal (struct symtab_and_line*) ; 
 int /*<<< orphan*/  initialize_defaults (struct symtab**,int*) ; 
 int /*<<< orphan*/  set_default_source_symtab_and_line () ; 
 scalar_t__ xmalloc (int) ; 

__attribute__((used)) static struct symtabs_and_lines
decode_all_digits (char **argptr, struct symtab *default_symtab,
		   int default_line, char ***canonical,
		   struct symtab *file_symtab, char *q)

{
  struct symtabs_and_lines values;
  struct symtab_and_line val;

  enum sign
    {
      none, plus, minus
    }
  sign = none;

  /* We might need a canonical line spec if no file was specified.  */
  int need_canonical = (file_symtab == 0) ? 1 : 0;

  init_sal (&val);

  /* This is where we need to make sure that we have good defaults.
     We must guarantee that this section of code is never executed
     when we are called with just a function name, since
     set_default_source_symtab_and_line uses
     select_source_symtab that calls us with such an argument.  */

  if (file_symtab == 0 && default_symtab == 0)
    {
      /* Make sure we have at least a default source file.  */
      set_default_source_symtab_and_line ();
      initialize_defaults (&default_symtab, &default_line);
    }

  if (**argptr == '+')
    sign = plus, (*argptr)++;
  else if (**argptr == '-')
    sign = minus, (*argptr)++;
  val.line = atoi (*argptr);
  switch (sign)
    {
    case plus:
      if (q == *argptr)
	val.line = 5;
      if (file_symtab == 0)
	val.line = default_line + val.line;
      break;
    case minus:
      if (q == *argptr)
	val.line = 15;
      if (file_symtab == 0)
	val.line = default_line - val.line;
      else
	val.line = 1;
      break;
    case none:
      break;		/* No need to adjust val.line.  */
    }

  while (*q == ' ' || *q == '\t')
    q++;
  *argptr = q;
  if (file_symtab == 0)
    file_symtab = default_symtab;

  /* It is possible that this source file has more than one symtab, 
     and that the new line number specification has moved us from the
     default (in file_symtab) to a new one.  */
  val.symtab = find_line_symtab (file_symtab, val.line, NULL, NULL);
  if (val.symtab == 0)
    val.symtab = file_symtab;

  val.pc = 0;
  values.sals = (struct symtab_and_line *)
    xmalloc (sizeof (struct symtab_and_line));
  values.sals[0] = val;
  values.nelts = 1;
  if (need_canonical)
    build_canonical_line_spec (values.sals, NULL, canonical);
  return values;
}