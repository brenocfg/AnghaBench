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
struct symtabs_and_lines {int /*<<< orphan*/ * sals; } ;
struct symtab {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  VAR_DOMAIN ; 
 scalar_t__ alloca (int) ; 
 struct symtabs_and_lines decode_all_digits (char**,struct symtab*,int,char***,struct symtab*,char*) ; 
 struct symtabs_and_lines decode_compound (char**,int,char***,char*,char*) ; 
 struct symtabs_and_lines decode_dollar (char*,int,struct symtab*,char***,struct symtab*) ; 
 struct symtabs_and_lines decode_indirect (char**) ; 
 struct symtabs_and_lines decode_objc (char**,int,int /*<<< orphan*/ *,char***,char*) ; 
 struct symtabs_and_lines decode_variable (char*,int,char***,struct symtab*,int*) ; 
 int /*<<< orphan*/  error (char*) ; 
 int /*<<< orphan*/  get_gdb_completer_quote_characters () ; 
 int /*<<< orphan*/  initialize_defaults (struct symtab**,int*) ; 
 scalar_t__ is_objc_method_format (char*) ; 
 char* locate_first_half (char**,int*) ; 
 scalar_t__ lookup_symbol (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  set_flags (char*,int*,char**) ; 
 char* skip_quoted (char*) ; 
 char* skip_quoted_chars (char*,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * strchr (int /*<<< orphan*/ ,char) ; 
 scalar_t__ sym ; 
 int /*<<< orphan*/  sym_symtab ; 
 struct symtabs_and_lines symbol_found (int,char***,char*,scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct symtab* symtab_from_filename (char**,char*,int,int*) ; 

struct symtabs_and_lines
decode_line_1 (char **argptr, int funfirstline, struct symtab *default_symtab,
	       int default_line, char ***canonical, int *not_found_ptr)
{
  char *p;
  char *q;
  /* If a file name is specified, this is its symtab.  */
  struct symtab *file_symtab = NULL;

  char *copy;
  /* This is NULL if there are no parens in *ARGPTR, or a pointer to
     the closing parenthesis if there are parens.  */
  char *paren_pointer;
  /* This says whether or not something in *ARGPTR is quoted with
     completer_quotes (i.e. with single quotes).  */
  int is_quoted;
  /* Is part of *ARGPTR is enclosed in double quotes?  */
  int is_quote_enclosed;
  int is_objc_method = 0;
  char *saved_arg = *argptr;

  if (not_found_ptr)
    *not_found_ptr = 0;

  /* Defaults have defaults.  */

  initialize_defaults (&default_symtab, &default_line);
  
  /* See if arg is *PC.  */

  if (**argptr == '*')
    return decode_indirect (argptr);

  /* Set various flags.  'paren_pointer' is important for overload
     checking, where we allow things like:
        (gdb) break c::f(int)
  */

  set_flags (*argptr, &is_quoted, &paren_pointer);

  /* Check to see if it's a multipart linespec (with colons or
     periods).  */

  /* Locate the end of the first half of the linespec.
     After the call, for instance, if the argptr string is "foo.c:123"
     p will point at "123".  If there is only one part, like "foo", p
     will point to "". If this is a C++ name, like "A::B::foo", p will
     point to "::B::foo". Argptr is not changed by this call.  */

  p = locate_first_half (argptr, &is_quote_enclosed);

  /* Check if this is an Objective-C method (anything that starts with
     a '+' or '-' and a '[').  */
  if (is_objc_method_format (p))
    {
      is_objc_method = 1;
      paren_pointer  = NULL; /* Just a category name.  Ignore it.  */
    }

  /* Check if the symbol could be an Objective-C selector.  */

  {
    struct symtabs_and_lines values;
    values = decode_objc (argptr, funfirstline, NULL,
			  canonical, saved_arg);
    if (values.sals != NULL)
      return values;
  }

  /* Does it look like there actually were two parts?  */

  if ((p[0] == ':' || p[0] == '.') && paren_pointer == NULL)
    {
      if (is_quoted)
	*argptr = *argptr + 1;
      
      /* Is it a C++ or Java compound data structure?
	 The check on p[1] == ':' is capturing the case of "::",
	 since p[0]==':' was checked above.  
	 Note that the call to decode_compound does everything
	 for us, including the lookup on the symbol table, so we
	 can return now. */
	
      if (p[0] == '.' || p[1] == ':')
	return decode_compound (argptr, funfirstline, canonical,
				saved_arg, p);

      /* No, the first part is a filename; set s to be that file's
	 symtab.  Also, move argptr past the filename.  */

      file_symtab = symtab_from_filename (argptr, p, is_quote_enclosed, 
		      			  not_found_ptr);
    }
#if 0
  /* No one really seems to know why this was added. It certainly
     breaks the command line, though, whenever the passed
     name is of the form ClassName::Method. This bit of code
     singles out the class name, and if funfirstline is set (for
     example, you are setting a breakpoint at this function),
     you get an error. This did not occur with earlier
     verions, so I am ifdef'ing this out. 3/29/99 */
  else
    {
      /* Check if what we have till now is a symbol name */

      /* We may be looking at a template instantiation such
         as "foo<int>".  Check here whether we know about it,
         instead of falling through to the code below which
         handles ordinary function names, because that code
         doesn't like seeing '<' and '>' in a name -- the
         skip_quoted call doesn't go past them.  So see if we
         can figure it out right now. */

      copy = (char *) alloca (p - *argptr + 1);
      memcpy (copy, *argptr, p - *argptr);
      copy[p - *argptr] = '\000';
      sym = lookup_symbol (copy, 0, VAR_DOMAIN, 0, &sym_symtab);
      if (sym)
	{
	  *argptr = (*p == '\'') ? p + 1 : p;
	  return symbol_found (funfirstline, canonical, copy, sym,
			       NULL, sym_symtab);
	}
      /* Otherwise fall out from here and go to file/line spec
         processing, etc. */
    }
#endif

  /* S is specified file's symtab, or 0 if no file specified.
     arg no longer contains the file name.  */

  /* Check whether arg is all digits (and sign).  */

  q = *argptr;
  if (*q == '-' || *q == '+')
    q++;
  while (*q >= '0' && *q <= '9')
    q++;

  if (q != *argptr && (*q == 0 || *q == ' ' || *q == '\t' || *q == ','))
    /* We found a token consisting of all digits -- at least one digit.  */
    return decode_all_digits (argptr, default_symtab, default_line,
			      canonical, file_symtab, q);

  /* Arg token is not digits => try it as a variable name
     Find the next token (everything up to end or next whitespace).  */

  if (**argptr == '$')		/* May be a convenience variable.  */
    /* One or two $ chars possible.  */
    p = skip_quoted (*argptr + (((*argptr)[1] == '$') ? 2 : 1));
  else if (is_quoted)
    {
      p = skip_quoted (*argptr);
      if (p[-1] != '\'')
	error ("Unmatched single quote.");
    }
  else if (is_objc_method)
    {
      /* allow word separators in method names for Obj-C */
      p = skip_quoted_chars (*argptr, NULL, "");
    }
  else if (paren_pointer != NULL)
    {
      p = paren_pointer + 1;
    }
  else
    {
      p = skip_quoted (*argptr);
    }

  copy = (char *) alloca (p - *argptr + 1);
  memcpy (copy, *argptr, p - *argptr);
  copy[p - *argptr] = '\0';
  if (p != *argptr
      && copy[0]
      && copy[0] == copy[p - *argptr - 1]
      && strchr (get_gdb_completer_quote_characters (), copy[0]) != NULL)
    {
      copy[p - *argptr - 1] = '\0';
      copy++;
    }
  while (*p == ' ' || *p == '\t')
    p++;
  *argptr = p;

  /* If it starts with $: may be a legitimate variable or routine name
     (e.g. HP-UX millicode routines such as $$dyncall), or it may
     be history value, or it may be a convenience variable.  */

  if (*copy == '$')
    return decode_dollar (copy, funfirstline, default_symtab,
			  canonical, file_symtab);

  /* Look up that token as a variable.
     If file specified, use that file's per-file block to start with.  */

  return decode_variable (copy, funfirstline, canonical,
			  file_symtab, not_found_ptr);
}