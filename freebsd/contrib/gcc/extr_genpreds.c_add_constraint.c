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
struct constraint_data {size_t namelen; char const* name; int lineno; char const* c_name; char const* regclass; int is_register; int is_const_int; int is_const_dbl; int is_extra; int is_memory; int is_address; struct constraint_data* next_textual; struct constraint_data* next_this_letter; scalar_t__ exp; } ;
typedef  scalar_t__ rtx ;
typedef  enum rtx_code { ____Placeholder_rtx_code } rtx_code ;

/* Variables and functions */
 scalar_t__ AND ; 
 int CONST_DOUBLE ; 
 int CONST_INT ; 
 scalar_t__ GET_CODE (scalar_t__) ; 
 char const* GET_RTX_NAME (int) ; 
 int /*<<< orphan*/  ISALNUM (char const) ; 
 int /*<<< orphan*/  ISALPHA (char const) ; 
 scalar_t__ MATCH_CODE ; 
 int /*<<< orphan*/  MAX (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ XEXP (scalar_t__,int /*<<< orphan*/ ) ; 
 char const* XSTR (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  const_dbl_constraints ; 
 int /*<<< orphan*/  const_int_constraints ; 
 int /*<<< orphan*/  constraint_max_namelen ; 
 struct constraint_data** constraints_by_letter_table ; 
 int /*<<< orphan*/  generic_constraint_letters ; 
 int have_address_constraints ; 
 int have_const_dbl_constraints ; 
 int have_const_int_constraints ; 
 int have_error ; 
 int have_extra_constraints ; 
 int have_memory_constraints ; 
 int have_register_constraints ; 
 struct constraint_data** last_constraint_ptr ; 
 char const* mangle (char const*) ; 
 int /*<<< orphan*/  message_with_line (int,char*,...) ; 
 struct constraint_data* obstack_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtl_obstack ; 
 scalar_t__ strchr (int /*<<< orphan*/ ,char const) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,size_t) ; 
 scalar_t__ validate_exp (scalar_t__,char const*,int) ; 

__attribute__((used)) static void
add_constraint (const char *name, const char *regclass,
		rtx exp, bool is_memory, bool is_address,
		int lineno)
{
  struct constraint_data *c, **iter, **slot;
  const char *p;
  bool need_mangled_name = false;
  bool is_const_int;
  bool is_const_dbl;
  size_t namelen;

  if (exp && validate_exp (exp, name, lineno))
    return;

  if (!ISALPHA (name[0]) && name[0] != '_')
    {
      if (name[1] == '\0')
	message_with_line (lineno, "constraint name '%s' is not "
			   "a letter or underscore", name);
      else
	message_with_line (lineno, "constraint name '%s' does not begin "
			   "with a letter or underscore", name);
      have_error = 1;
      return;
    }
  for (p = name; *p; p++)
    if (!ISALNUM (*p))
      {
	if (*p == '<' || *p == '>' || *p == '_')
	  need_mangled_name = true;
	else
	  {
	    message_with_line (lineno,
			       "constraint name '%s' must be composed of "
			       "letters, digits, underscores, and "
			       "angle brackets", name);
	    have_error = 1;
	    return;
	  }
      }

  if (strchr (generic_constraint_letters, name[0]))
    {
      if (name[1] == '\0')
	message_with_line (lineno, "constraint letter '%s' cannot be "
			   "redefined by the machine description", name);
      else
	message_with_line (lineno, "constraint name '%s' cannot be defined by "
			   "the machine description, as it begins with '%c'",
			   name, name[0]);
      have_error = 1;
      return;
    }

  
  namelen = strlen (name);
  slot = &constraints_by_letter_table[(unsigned int)name[0]];
  for (iter = slot; *iter; iter = &(*iter)->next_this_letter)
    {
      /* This causes slot to end up pointing to the
	 next_this_letter field of the last constraint with a name
	 of equal or greater length than the new constraint; hence
	 the new constraint will be inserted after all previous
	 constraints with names of the same length.  */
      if ((*iter)->namelen >= namelen)
	slot = iter;

      if (!strcmp ((*iter)->name, name))
	{
	  message_with_line (lineno, "redefinition of constraint '%s'", name);
	  message_with_line ((*iter)->lineno, "previous definition is here");
	  have_error = 1;
	  return;
	}
      else if (!strncmp ((*iter)->name, name, (*iter)->namelen))
	{
	  message_with_line (lineno, "defining constraint '%s' here", name);
	  message_with_line ((*iter)->lineno, "renders constraint '%s' "
			     "(defined here) a prefix", (*iter)->name);
	  have_error = 1;
	  return;
	}
      else if (!strncmp ((*iter)->name, name, namelen))
	{
	  message_with_line (lineno, "constraint '%s' is a prefix", name);
	  message_with_line ((*iter)->lineno, "of constraint '%s' "
			     "(defined here)", (*iter)->name);
	  have_error = 1;
	  return;
	}
    }

  is_const_int = strchr (const_int_constraints, name[0]) != 0;
  is_const_dbl = strchr (const_dbl_constraints, name[0]) != 0;

  if (is_const_int || is_const_dbl)
    {
      enum rtx_code appropriate_code
	= is_const_int ? CONST_INT : CONST_DOUBLE;

      /* Consider relaxing this requirement in the future.  */
      if (regclass
	  || GET_CODE (exp) != AND
	  || GET_CODE (XEXP (exp, 0)) != MATCH_CODE
	  || strcmp (XSTR (XEXP (exp, 0), 0),
		     GET_RTX_NAME (appropriate_code)))
	{
	  if (name[1] == '\0')
	    message_with_line (lineno, "constraint letter '%c' is reserved "
			       "for %s constraints",
			       name[0], GET_RTX_NAME (appropriate_code));
	  else
	    message_with_line (lineno, "constraint names beginning with '%c' "
			       "(%s) are reserved for %s constraints",
			       name[0], name, 
			       GET_RTX_NAME (appropriate_code));

	  have_error = 1;
	  return;
	}

      if (is_memory)
	{
	  if (name[1] == '\0')
	    message_with_line (lineno, "constraint letter '%c' cannot be a "
			       "memory constraint", name[0]);
	  else
	    message_with_line (lineno, "constraint name '%s' begins with '%c', "
			       "and therefore cannot be a memory constraint",
			       name, name[0]);

	  have_error = 1;
	  return;
	}
      else if (is_address)
	{
	  if (name[1] == '\0')
	    message_with_line (lineno, "constraint letter '%c' cannot be a "
			       "memory constraint", name[0]);
	  else
	    message_with_line (lineno, "constraint name '%s' begins with '%c', "
			       "and therefore cannot be a memory constraint",
			       name, name[0]);

	  have_error = 1;
	  return;
	}
    }

  
  c = obstack_alloc (rtl_obstack, sizeof (struct constraint_data));
  c->name = name;
  c->c_name = need_mangled_name ? mangle (name) : name;
  c->lineno = lineno;
  c->namelen = namelen;
  c->regclass = regclass;
  c->exp = exp;
  c->is_register = regclass != 0;
  c->is_const_int = is_const_int;
  c->is_const_dbl = is_const_dbl;
  c->is_extra = !(regclass || is_const_int || is_const_dbl);
  c->is_memory = is_memory;
  c->is_address = is_address;

  c->next_this_letter = *slot;
  *slot = c;

  /* Insert this constraint in the list of all constraints in textual
     order.  */
  c->next_textual = 0;
  *last_constraint_ptr = c;
  last_constraint_ptr = &c->next_textual;

  constraint_max_namelen = MAX (constraint_max_namelen, strlen (name));
  have_register_constraints |= c->is_register;
  have_const_int_constraints |= c->is_const_int;
  have_const_dbl_constraints |= c->is_const_dbl;
  have_extra_constraints |= c->is_extra;
  have_memory_constraints |= c->is_memory;
  have_address_constraints |= c->is_address;
}