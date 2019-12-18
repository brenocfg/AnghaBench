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
struct stab_tag {char* name; struct stab_tag* next; int /*<<< orphan*/  slot; } ;
struct stab_handle {int gcc_compiled; long symcount; struct stab_tag* tags; int /*<<< orphan*/  self_crossref; int /*<<< orphan*/ ** syms; int /*<<< orphan*/  abfd; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  int /*<<< orphan*/  bfd_vma ;
typedef  int /*<<< orphan*/  bfd_boolean ;
typedef  int /*<<< orphan*/  asymbol ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_GLOBAL ; 
 int /*<<< orphan*/  DEBUG_LOCAL ; 
 int /*<<< orphan*/  DEBUG_LOCAL_STATIC ; 
 int /*<<< orphan*/  DEBUG_PARM_REFERENCE ; 
 int /*<<< orphan*/  DEBUG_PARM_REF_REG ; 
 int /*<<< orphan*/  DEBUG_PARM_REG ; 
 int /*<<< orphan*/  DEBUG_PARM_STACK ; 
 int /*<<< orphan*/  DEBUG_REGISTER ; 
 int /*<<< orphan*/  DEBUG_STATIC ; 
 int /*<<< orphan*/  DEBUG_TYPE_NULL ; 
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ISDIGIT (char const) ; 
 int N_FUN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  atof (char const*) ; 
 int /*<<< orphan*/  atoi (char const*) ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 char* bfd_asymbol_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bfd_asymbol_value (int /*<<< orphan*/ *) ; 
 char bfd_get_symbol_leading_char (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_make_function_type (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_make_pointer_type (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_name_type (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_float_const (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_function (void*,char*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_int_const (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_label (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_parameter (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_record_typed_const (void*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debug_tag_type (void*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_stab_type (void*,struct stab_handle*,char const*,char const**,int /*<<< orphan*/ **) ; 
 char* savestring (char const*,int) ; 
 int /*<<< orphan*/  stab_record_variable (void*,struct stab_handle*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bfd_boolean
parse_stab_string (void *dhandle, struct stab_handle *info, int stabtype,
		   int desc, bfd_vma value, const char *string)
{
  const char *p;
  char *name;
  int type;
  debug_type dtype;
  bfd_boolean synonym;
  bfd_boolean self_crossref;
  unsigned int lineno;
  debug_type *slot;

  p = strchr (string, ':');
  if (p == NULL)
    return TRUE;

  while (p[1] == ':')
    {
      p += 2;
      p = strchr (p, ':');
      if (p == NULL)
	{
	  bad_stab (string);
	  return FALSE;
	}
    }

  /* GCC 2.x puts the line number in desc.  SunOS apparently puts in
     the number of bytes occupied by a type or object, which we
     ignore.  */
  if (info->gcc_compiled >= 2)
    lineno = desc;
  else
    lineno = 0;

  /* FIXME: Sometimes the special C++ names start with '.'.  */
  name = NULL;
  if (string[0] == '$')
    {
      switch (string[1])
	{
	case 't':
	  name = "this";
	  break;
	case 'v':
	  /* Was: name = "vptr"; */
	  break;
	case 'e':
	  name = "eh_throw";
	  break;
	case '_':
	  /* This was an anonymous type that was never fixed up.  */
	  break;
	case 'X':
	  /* SunPRO (3.0 at least) static variable encoding.  */
	  break;
	default:
	  warn_stab (string, _("unknown C++ encoded name"));
	  break;
	}
    }

  if (name == NULL)
    {
      if (p == string || (string[0] == ' ' && p == string + 1))
	name = NULL;
      else
	name = savestring (string, p - string);
    }

  ++p;
  if (ISDIGIT (*p) || *p == '(' || *p == '-')
    type = 'l';
  else
    type = *p++;

  switch (type)
    {
    case 'c':
      /* c is a special case, not followed by a type-number.
	 SYMBOL:c=iVALUE for an integer constant symbol.
	 SYMBOL:c=rVALUE for a floating constant symbol.
	 SYMBOL:c=eTYPE,INTVALUE for an enum constant symbol.
	 e.g. "b:c=e6,0" for "const b = blob1"
	 (where type 6 is defined by "blobs:t6=eblob1:0,blob2:1,;").  */
      if (*p != '=')
	{
	  bad_stab (string);
	  return FALSE;
	}
      ++p;
      switch (*p++)
	{
	case 'r':
	  /* Floating point constant.  */
	  if (! debug_record_float_const (dhandle, name, atof (p)))
	    return FALSE;
	  break;
	case 'i':
	  /* Integer constant.  */
	  /* Defining integer constants this way is kind of silly,
	     since 'e' constants allows the compiler to give not only
	     the value, but the type as well.  C has at least int,
	     long, unsigned int, and long long as constant types;
	     other languages probably should have at least unsigned as
	     well as signed constants.  */
	  if (! debug_record_int_const (dhandle, name, atoi (p)))
	    return FALSE;
	  break;
	case 'e':
	  /* SYMBOL:c=eTYPE,INTVALUE for a constant symbol whose value
	     can be represented as integral.
	     e.g. "b:c=e6,0" for "const b = blob1"
	     (where type 6 is defined by "blobs:t6=eblob1:0,blob2:1,;").  */
	  dtype = parse_stab_type (dhandle, info, (const char *) NULL,
				   &p, (debug_type **) NULL);
	  if (dtype == DEBUG_TYPE_NULL)
	    return FALSE;
	  if (*p != ',')
	    {
	      bad_stab (string);
	      return FALSE;
	    }
	  if (! debug_record_typed_const (dhandle, name, dtype, atoi (p)))
	    return FALSE;
	  break;
	default:
	  bad_stab (string);
	  return FALSE;
	}

      break;

    case 'C':
      /* The name of a caught exception.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL,
			       &p, (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_label (dhandle, name, dtype, value))
	return FALSE;
      break;

    case 'f':
    case 'F':
      /* A function definition.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_function (dhandle, name, dtype, type == 'F', value))
	return FALSE;

      /* Sun acc puts declared types of arguments here.  We don't care
	 about their actual types (FIXME -- we should remember the whole
	 function prototype), but the list may define some new types
	 that we have to remember, so we must scan it now.  */
      while (*p == ';')
	{
	  ++p;
	  if (parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL)
	      == DEBUG_TYPE_NULL)
	    return FALSE;
	}

      break;

    case 'G':
      {
	char leading;
	long c;
	asymbol **ps;

	/* A global symbol.  The value must be extracted from the
	   symbol table.  */
	dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
				 (debug_type **) NULL);
	if (dtype == DEBUG_TYPE_NULL)
	  return FALSE;
	leading = bfd_get_symbol_leading_char (info->abfd);
	for (c = info->symcount, ps = info->syms; c > 0; --c, ++ps)
	  {
	    const char *n;

	    n = bfd_asymbol_name (*ps);
	    if (leading != '\0' && *n == leading)
	      ++n;
	    if (*n == *name && strcmp (n, name) == 0)
	      break;
	  }
	if (c > 0)
	  value = bfd_asymbol_value (*ps);
	if (! stab_record_variable (dhandle, info, name, dtype, DEBUG_GLOBAL,
				    value))
	  return FALSE;
      }
      break;

      /* This case is faked by a conditional above, when there is no
	 code letter in the dbx data.  Dbx data never actually
	 contains 'l'.  */
    case 'l':
    case 's':
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! stab_record_variable (dhandle, info, name, dtype, DEBUG_LOCAL,
				  value))
	return FALSE;
      break;

    case 'p':
      /* A function parameter.  */
      if (*p != 'F')
	dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
				 (debug_type **) NULL);
      else
	{
	/* pF is a two-letter code that means a function parameter in
	   Fortran.  The type-number specifies the type of the return
	   value.  Translate it into a pointer-to-function type.  */
	  ++p;
	  dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
				   (debug_type **) NULL);
	  if (dtype != DEBUG_TYPE_NULL)
	    {
	      debug_type ftype;

	      ftype = debug_make_function_type (dhandle, dtype,
						(debug_type *) NULL, FALSE);
	      dtype = debug_make_pointer_type (dhandle, ftype);
	    }
	}
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_parameter (dhandle, name, dtype, DEBUG_PARM_STACK,
				    value))
	return FALSE;

      /* FIXME: At this point gdb considers rearranging the parameter
	 address on a big endian machine if it is smaller than an int.
	 We have no way to do that, since we don't really know much
	 about the target.  */
      break;

    case 'P':
      if (stabtype == N_FUN)
	{
	  /* Prototype of a function referenced by this file.  */
	  while (*p == ';')
	    {
	      ++p;
	      if (parse_stab_type (dhandle, info, (const char *) NULL, &p,
				   (debug_type **) NULL)
		  == DEBUG_TYPE_NULL)
		return FALSE;
	    }
	  break;
	}
      /* Fall through.  */
    case 'R':
      /* Parameter which is in a register.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_parameter (dhandle, name, dtype, DEBUG_PARM_REG,
				    value))
	return FALSE;
      break;

    case 'r':
      /* Register variable (either global or local).  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! stab_record_variable (dhandle, info, name, dtype, DEBUG_REGISTER,
				  value))
	return FALSE;

      /* FIXME: At this point gdb checks to combine pairs of 'p' and
	 'r' stabs into a single 'P' stab.  */
      break;

    case 'S':
      /* Static symbol at top level of file.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! stab_record_variable (dhandle, info, name, dtype, DEBUG_STATIC,
				  value))
	return FALSE;
      break;

    case 't':
      /* A typedef.  */
      dtype = parse_stab_type (dhandle, info, name, &p, &slot);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (name == NULL)
	{
	  /* A nameless type.  Nothing to do.  */
	  return TRUE;
	}

      dtype = debug_name_type (dhandle, name, dtype);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;

      if (slot != NULL)
	*slot = dtype;

      break;

    case 'T':
      /* Struct, union, or enum tag.  For GNU C++, this can be be followed
	 by 't' which means we are typedef'ing it as well.  */
      if (*p != 't')
	{
	  synonym = FALSE;
	  /* FIXME: gdb sets synonym to TRUE if the current language
             is C++.  */
	}
      else
	{
	  synonym = TRUE;
	  ++p;
	}

      dtype = parse_stab_type (dhandle, info, name, &p, &slot);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (name == NULL)
	return TRUE;

      /* INFO->SELF_CROSSREF is set by parse_stab_type if this type is
         a cross reference to itself.  These are generated by some
         versions of g++.  */
      self_crossref = info->self_crossref;

      dtype = debug_tag_type (dhandle, name, dtype);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (slot != NULL)
	*slot = dtype;

      /* See if we have a cross reference to this tag which we can now
         fill in.  Avoid filling in a cross reference to ourselves,
         because that would lead to circular debugging information.  */
      if (! self_crossref)
	{
	  register struct stab_tag **pst;

	  for (pst = &info->tags; *pst != NULL; pst = &(*pst)->next)
	    {
	      if ((*pst)->name[0] == name[0]
		  && strcmp ((*pst)->name, name) == 0)
		{
		  (*pst)->slot = dtype;
		  *pst = (*pst)->next;
		  break;
		}
	    }
	}

      if (synonym)
	{
	  dtype = debug_name_type (dhandle, name, dtype);
	  if (dtype == DEBUG_TYPE_NULL)
	    return FALSE;

	  if (slot != NULL)
	    *slot = dtype;
	}

      break;

    case 'V':
      /* Static symbol of local scope */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      /* FIXME: gdb checks os9k_stabs here.  */
      if (! stab_record_variable (dhandle, info, name, dtype,
				  DEBUG_LOCAL_STATIC, value))
	return FALSE;
      break;

    case 'v':
      /* Reference parameter.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_parameter (dhandle, name, dtype, DEBUG_PARM_REFERENCE,
				    value))
	return FALSE;
      break;

    case 'a':
      /* Reference parameter which is in a register.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! debug_record_parameter (dhandle, name, dtype, DEBUG_PARM_REF_REG,
				    value))
	return FALSE;
      break;

    case 'X':
      /* This is used by Sun FORTRAN for "function result value".
	 Sun claims ("dbx and dbxtool interfaces", 2nd ed)
	 that Pascal uses it too, but when I tried it Pascal used
	 "x:3" (local symbol) instead.  */
      dtype = parse_stab_type (dhandle, info, (const char *) NULL, &p,
			       (debug_type **) NULL);
      if (dtype == DEBUG_TYPE_NULL)
	return FALSE;
      if (! stab_record_variable (dhandle, info, name, dtype, DEBUG_LOCAL,
				  value))
	return FALSE;
      break;

    default:
      bad_stab (string);
      return FALSE;
    }

  /* FIXME: gdb converts structure values to structure pointers in a
     couple of cases, depending upon the target.  */

  return TRUE;
}