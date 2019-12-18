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
struct type {int dummy; } ;
struct symtabs_and_lines {int dummy; } ;
struct symtab {int dummy; } ;
struct symbol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SYMBOL_TYPE (struct symbol*) ; 
 scalar_t__ TYPE_CODE (struct type*) ; 
 scalar_t__ TYPE_CODE_STRUCT ; 
 scalar_t__ TYPE_CODE_UNION ; 
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ alloca (int) ; 
 struct type* check_typedef (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cplusplus_error (char*,char*,char*) ; 
 int /*<<< orphan*/  error (char*) ; 
 struct symtabs_and_lines find_method (int,char***,char*,char*,struct type*,struct symbol*) ; 
 char* find_template_name_end (char*) ; 
 int /*<<< orphan*/  get_gdb_completer_quote_characters () ; 
 struct symbol* lookup_prefix_sym (char**,char*) ; 
 struct symbol* lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct symtab**) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 char* skip_quoted (char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 struct symtabs_and_lines symbol_found (int,char***,char*,struct symbol*,int /*<<< orphan*/ *,struct symtab*) ; 

__attribute__((used)) static struct symtabs_and_lines
decode_compound (char **argptr, int funfirstline, char ***canonical,
		 char *saved_arg, char *p)
{
  struct symtabs_and_lines values;
  char *p2;
  char *saved_arg2 = *argptr;
  char *temp_end;
  struct symbol *sym;
  /* The symtab that SYM was found in.  */
  struct symtab *sym_symtab;
  char *copy;
  struct symbol *sym_class;
  struct symbol **sym_arr;
  struct type *t;

  /* First check for "global" namespace specification, of the form
     "::foo".  If found, skip over the colons and jump to normal
     symbol processing.  I.e. the whole line specification starts with
     "::" (note the condition that *argptr == p). */
  if (p[0] == ':' 
      && ((*argptr == p) || (p[-1] == ' ') || (p[-1] == '\t')))
    saved_arg2 += 2;

  /* Given our example "AAA::inA::fun", we have two cases to consider:

     1) AAA::inA is the name of a class.  In that case, presumably it
        has a method called "fun"; we then look up that method using
        find_method.

     2) AAA::inA isn't the name of a class.  In that case, either the
        user made a typo or AAA::inA is the name of a namespace.
        Either way, we just look up AAA::inA::fun with lookup_symbol.

     Thus, our first task is to find everything before the last set of
     double-colons and figure out if it's the name of a class.  So we
     first loop through all of the double-colons.  */

  p2 = p;		/* Save for restart.  */

  /* This is very messy. Following the example above we have now the
     following pointers:
     p -> "::inA::fun"
     argptr -> "AAA::inA::fun
     saved_arg -> "AAA::inA::fun
     saved_arg2 -> "AAA::inA::fun
     p2 -> "::inA::fun". */

  /* In the loop below, with these strings, we'll make 2 passes, each
     is marked in comments.*/

  while (1)
    {
      /* Move pointer up to next possible class/namespace token.  */

      p = p2 + 1;	/* Restart with old value +1.  */

      /* PASS1: at this point p2->"::inA::fun", so p->":inA::fun",
	 i.e. if there is a double-colon, p will now point to the
	 second colon. */
      /* PASS2: p2->"::fun", p->":fun" */

      /* Move pointer ahead to next double-colon.  */
      while (*p && (p[0] != ' ') && (p[0] != '\t') && (p[0] != '\''))
	{
	  if (p[0] == '<')
	    {
	      temp_end = find_template_name_end (p);
	      if (!temp_end)
		error ("malformed template specification in command");
	      p = temp_end;
	    }
	  /* Note that, since, at the start of this loop, p would be
	     pointing to the second colon in a double-colon, we only
	     satisfy the condition below if there is another
	     double-colon to the right (after). I.e. there is another
	     component that can be a class or a namespace. I.e, if at
	     the beginning of this loop (PASS1), we had
	     p->":inA::fun", we'll trigger this when p has been
	     advanced to point to "::fun".  */
	  /* PASS2: we will not trigger this. */
	  else if ((p[0] == ':') && (p[1] == ':'))
	    break;	/* Found double-colon.  */
	  else
	    /* PASS2: We'll keep getting here, until p->"", at which point
	       we exit this loop.  */
	    p++;
	}

      if (*p != ':')
	break;		/* Out of the while (1).  This would happen
			   for instance if we have looked up
			   unsuccessfully all the components of the
			   string, and p->""(PASS2)  */

      /* We get here if p points to ' ', '\t', '\'', "::" or ""(i.e
	 string ended). */
      /* Save restart for next time around.  */
      p2 = p;
      /* Restore argptr as it was on entry to this function.  */
      *argptr = saved_arg2;
      /* PASS1: at this point p->"::fun" argptr->"AAA::inA::fun",
	 p2->"::fun".  */

      /* All ready for next pass through the loop.  */
    }			/* while (1) */


  /* Start of lookup in the symbol tables. */

  /* Lookup in the symbol table the substring between argptr and
     p. Note, this call changes the value of argptr.  */
  /* Before the call, argptr->"AAA::inA::fun",
     p->"", p2->"::fun".  After the call: argptr->"fun", p, p2
     unchanged.  */
  sym_class = lookup_prefix_sym (argptr, p2);

  /* If sym_class has been found, and if "AAA::inA" is a class, then
     we're in case 1 above.  So we look up "fun" as a method of that
     class.  */
  if (sym_class &&
      (t = check_typedef (SYMBOL_TYPE (sym_class)),
       (TYPE_CODE (t) == TYPE_CODE_STRUCT
	|| TYPE_CODE (t) == TYPE_CODE_UNION)))
    {
      /* Arg token is not digits => try it as a function name.
	 Find the next token (everything up to end or next
	 blank).  */
      if (**argptr
	  && strchr (get_gdb_completer_quote_characters (),
		     **argptr) != NULL)
	{
	  p = skip_quoted (*argptr);
	  *argptr = *argptr + 1;
	}
      else
	{
	  /* At this point argptr->"fun".  */
	  p = *argptr;
	  while (*p && *p != ' ' && *p != '\t' && *p != ',' && *p != ':')
	    p++;
	  /* At this point p->"".  String ended.  */
	}

      /* Allocate our own copy of the substring between argptr and
	 p. */
      copy = (char *) alloca (p - *argptr + 1);
      memcpy (copy, *argptr, p - *argptr);
      copy[p - *argptr] = '\0';
      if (p != *argptr
	  && copy[p - *argptr - 1]
	  && strchr (get_gdb_completer_quote_characters (),
		     copy[p - *argptr - 1]) != NULL)
	copy[p - *argptr - 1] = '\0';

      /* At this point copy->"fun", p->"" */

      /* No line number may be specified.  */
      while (*p == ' ' || *p == '\t')
	p++;
      *argptr = p;
      /* At this point arptr->"".  */

      /* Look for copy as a method of sym_class. */
      /* At this point copy->"fun", sym_class is "AAA:inA",
	 saved_arg->"AAA::inA::fun".  This concludes the scanning of
	 the string for possible components matches.  If we find it
	 here, we return. If not, and we are at the and of the string,
	 we'll lookup the whole string in the symbol tables.  */

      return find_method (funfirstline, canonical, saved_arg,
			  copy, t, sym_class);

    } /* End if symbol found */


  /* We couldn't find a class, so we're in case 2 above.  We check the
     entire name as a symbol instead.  */

  copy = (char *) alloca (p - saved_arg2 + 1);
  memcpy (copy, saved_arg2, p - saved_arg2);
  /* Note: if is_quoted should be true, we snuff out quote here
     anyway.  */
  copy[p - saved_arg2] = '\000';
  /* Set argptr to skip over the name.  */
  *argptr = (*p == '\'') ? p + 1 : p;

  /* Look up entire name */
  sym = lookup_symbol (copy, 0, VAR_DOMAIN, 0, &sym_symtab);
  if (sym)
    return symbol_found (funfirstline, canonical, copy, sym,
			 NULL, sym_symtab);

  /* Couldn't find any interpretation as classes/namespaces, so give
     up.  The quotes are important if copy is empty.  */
  cplusplus_error (saved_arg,
		   "Can't find member of namespace, class, struct, or union named \"%s\"\n",
		   copy);
}