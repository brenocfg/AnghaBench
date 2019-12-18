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
struct stab_handle {void* self_crossref; } ;
typedef  enum debug_type_kind { ____Placeholder_debug_type_kind } debug_type_kind ;
typedef  scalar_t__ debug_type ;
typedef  void* bfd_boolean ;

/* Variables and functions */
 int DEBUG_KIND_ENUM ; 
 int DEBUG_KIND_STRUCT ; 
 int DEBUG_KIND_UNION ; 
 int /*<<< orphan*/  DEBUG_KIND_VOID ; 
 scalar_t__ DEBUG_TYPE_NULL ; 
 void* FALSE ; 
 scalar_t__ ISDIGIT (char const) ; 
 void* TRUE ; 
 int /*<<< orphan*/  _ (char*) ; 
 int atoi (char const*) ; 
 int /*<<< orphan*/  bad_stab (char const*) ; 
 int /*<<< orphan*/  debug_get_type_kind (void*,scalar_t__) ; 
 scalar_t__ debug_make_const_type (void*,scalar_t__) ; 
 scalar_t__ debug_make_function_type (void*,scalar_t__,scalar_t__*,void*) ; 
 scalar_t__ debug_make_method_type (void*,scalar_t__,scalar_t__,scalar_t__*,void*) ; 
 scalar_t__ debug_make_offset_type (void*,scalar_t__,scalar_t__) ; 
 scalar_t__ debug_make_pointer_type (void*,scalar_t__) ; 
 scalar_t__ debug_make_reference_type (void*,scalar_t__) ; 
 scalar_t__ debug_make_set_type (void*,scalar_t__,void*) ; 
 scalar_t__ debug_make_void_type (void*) ; 
 scalar_t__ debug_make_volatile_type (void*,scalar_t__) ; 
 int /*<<< orphan*/  debug_record_type_size (void*,scalar_t__,unsigned int) ; 
 scalar_t__ parse_stab_array_type (void*,struct stab_handle*,char const**,void*) ; 
 scalar_t__ parse_stab_enum_type (void*,char const**) ; 
 scalar_t__ parse_stab_range_type (void*,struct stab_handle*,char const*,char const**,int*) ; 
 scalar_t__ parse_stab_struct_type (void*,struct stab_handle*,char const*,char const**,int,int*) ; 
 scalar_t__ parse_stab_sun_builtin_type (void*,char const**) ; 
 scalar_t__ parse_stab_sun_floating_type (void*,char const**) ; 
 int /*<<< orphan*/  parse_stab_type_number (char const**,int*) ; 
 scalar_t__* stab_find_slot (struct stab_handle*,int*) ; 
 scalar_t__ stab_find_tagged_type (void*,struct stab_handle*,char const*,int,int) ; 
 scalar_t__ stab_find_type (void*,struct stab_handle*,int*) ; 
 int /*<<< orphan*/  stab_record_type (void*,struct stab_handle*,int*,scalar_t__) ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strncmp (char const*,char const*,int) ; 
 int /*<<< orphan*/  warn_stab (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ xmalloc (unsigned int) ; 
 scalar_t__ xrealloc (scalar_t__*,unsigned int) ; 

__attribute__((used)) static debug_type
parse_stab_type (void *dhandle, struct stab_handle *info, const char *typename, const char **pp, debug_type **slotp)
{
  const char *orig;
  int typenums[2];
  int size;
  bfd_boolean stringp;
  int descriptor;
  debug_type dtype;

  if (slotp != NULL)
    *slotp = NULL;

  orig = *pp;

  size = -1;
  stringp = FALSE;

  info->self_crossref = FALSE;

  /* Read type number if present.  The type number may be omitted.
     for instance in a two-dimensional array declared with type
     "ar1;1;10;ar1;1;10;4".  */
  if (! ISDIGIT (**pp) && **pp != '(' && **pp != '-')
    {
      /* 'typenums=' not present, type is anonymous.  Read and return
	 the definition, but don't put it in the type vector.  */
      typenums[0] = typenums[1] = -1;
    }
  else
    {
      if (! parse_stab_type_number (pp, typenums))
	return DEBUG_TYPE_NULL;

      if (**pp != '=')
	/* Type is not being defined here.  Either it already
	   exists, or this is a forward reference to it.  */
	return stab_find_type (dhandle, info, typenums);

      /* Only set the slot if the type is being defined.  This means
         that the mapping from type numbers to types will only record
         the name of the typedef which defines a type.  If we don't do
         this, then something like
	     typedef int foo;
	     int i;
	 will record that i is of type foo.  Unfortunately, stabs
	 information is ambiguous about variable types.  For this code,
	     typedef int foo;
	     int i;
	     foo j;
	 the stabs information records both i and j as having the same
	 type.  This could be fixed by patching the compiler.  */
      if (slotp != NULL && typenums[0] >= 0 && typenums[1] >= 0)
	*slotp = stab_find_slot (info, typenums);

      /* Type is being defined here.  */
      /* Skip the '='.  */
      ++*pp;

      while (**pp == '@')
	{
	  const char *p = *pp + 1;
	  const char *attr;

	  if (ISDIGIT (*p) || *p == '(' || *p == '-')
	    /* Member type.  */
	    break;

	  /* Type attributes.  */
	  attr = p;

	  for (; *p != ';'; ++p)
	    {
	      if (*p == '\0')
		{
		  bad_stab (orig);
		  return DEBUG_TYPE_NULL;
		}
	    }
	  *pp = p + 1;

	  switch (*attr)
	    {
	    case 's':
	      size = atoi (attr + 1);
	      size /= 8;  /* Size is in bits.  We store it in bytes.  */
	      if (size <= 0)
		size = -1;
	      break;

	    case 'S':
	      stringp = TRUE;
	      break;

	    default:
	      /* Ignore unrecognized type attributes, so future
		 compilers can invent new ones.  */
	      break;
	    }
	}
    }

  descriptor = **pp;
  ++*pp;

  switch (descriptor)
    {
    case 'x':
      {
	enum debug_type_kind code;
	const char *q1, *q2, *p;

	/* A cross reference to another type.  */
	switch (**pp)
	  {
	  case 's':
	    code = DEBUG_KIND_STRUCT;
	    break;
	  case 'u':
	    code = DEBUG_KIND_UNION;
	    break;
	  case 'e':
	    code = DEBUG_KIND_ENUM;
	    break;
	  default:
	    /* Complain and keep going, so compilers can invent new
	       cross-reference types.  */
	    warn_stab (orig, _("unrecognized cross reference type"));
	    code = DEBUG_KIND_STRUCT;
	    break;
	  }
	++*pp;

	q1 = strchr (*pp, '<');
	p = strchr (*pp, ':');
	if (p == NULL)
	  {
	    bad_stab (orig);
	    return DEBUG_TYPE_NULL;
	  }
	if (q1 != NULL && p > q1 && p[1] == ':')
	  {
	    int nest = 0;

	    for (q2 = q1; *q2 != '\0'; ++q2)
	      {
		if (*q2 == '<')
		  ++nest;
		else if (*q2 == '>')
		  --nest;
		else if (*q2 == ':' && nest == 0)
		  break;
	      }
	    p = q2;
	    if (*p != ':')
	      {
		bad_stab (orig);
		return DEBUG_TYPE_NULL;
	      }
	  }

	/* Some versions of g++ can emit stabs like
	       fleep:T20=xsfleep:
	   which define structures in terms of themselves.  We need to
	   tell the caller to avoid building a circular structure.  */
	if (typename != NULL
	    && strncmp (typename, *pp, p - *pp) == 0
	    && typename[p - *pp] == '\0')
	  info->self_crossref = TRUE;

	dtype = stab_find_tagged_type (dhandle, info, *pp, p - *pp, code);

	*pp = p + 1;
      }
      break;

    case '-':
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
    case '(':
      {
	const char *hold;
	int xtypenums[2];

	/* This type is defined as another type.  */
	(*pp)--;
	hold = *pp;

	/* Peek ahead at the number to detect void.  */
	if (! parse_stab_type_number (pp, xtypenums))
	  return DEBUG_TYPE_NULL;

	if (typenums[0] == xtypenums[0] && typenums[1] == xtypenums[1])
	  {
	    /* This type is being defined as itself, which means that
               it is void.  */
	    dtype = debug_make_void_type (dhandle);
	  }
	else
	  {
	    *pp = hold;

	    /* Go back to the number and have parse_stab_type get it.
	       This means that we can deal with something like
	       t(1,2)=(3,4)=... which the Lucid compiler uses.  */
	    dtype = parse_stab_type (dhandle, info, (const char *) NULL,
				     pp, (debug_type **) NULL);
	    if (dtype == DEBUG_TYPE_NULL)
	      return DEBUG_TYPE_NULL;
	  }

	if (typenums[0] != -1)
	  {
	    if (! stab_record_type (dhandle, info, typenums, dtype))
	      return DEBUG_TYPE_NULL;
	  }

	break;
      }

    case '*':
      dtype = debug_make_pointer_type (dhandle,
				       parse_stab_type (dhandle, info,
							(const char *) NULL,
							pp,
							(debug_type **) NULL));
      break;

    case '&':
      /* Reference to another type.  */
      dtype = (debug_make_reference_type
	       (dhandle,
		parse_stab_type (dhandle, info, (const char *) NULL, pp,
				 (debug_type **) NULL)));
      break;

    case 'f':
      /* Function returning another type.  */
      /* FIXME: gdb checks os9k_stabs here.  */
      dtype = (debug_make_function_type
	       (dhandle,
		parse_stab_type (dhandle, info, (const char *) NULL, pp,
				 (debug_type **) NULL),
		(debug_type *) NULL, FALSE));
      break;

    case 'k':
      /* Const qualifier on some type (Sun).  */
      /* FIXME: gdb accepts 'c' here if os9k_stabs.  */
      dtype = debug_make_const_type (dhandle,
				     parse_stab_type (dhandle, info,
						      (const char *) NULL,
						      pp,
						      (debug_type **) NULL));
      break;

    case 'B':
      /* Volatile qual on some type (Sun).  */
      /* FIXME: gdb accepts 'i' here if os9k_stabs.  */
      dtype = (debug_make_volatile_type
	       (dhandle,
		parse_stab_type (dhandle, info, (const char *) NULL, pp,
				 (debug_type **) NULL)));
      break;

    case '@':
      /* Offset (class & variable) type.  This is used for a pointer
         relative to an object.  */
      {
	debug_type domain;
	debug_type memtype;

	/* Member type.  */

	domain = parse_stab_type (dhandle, info, (const char *) NULL, pp,
				  (debug_type **) NULL);
	if (domain == DEBUG_TYPE_NULL)
	  return DEBUG_TYPE_NULL;

	if (**pp != ',')
	  {
	    bad_stab (orig);
	    return DEBUG_TYPE_NULL;
	  }
	++*pp;

	memtype = parse_stab_type (dhandle, info, (const char *) NULL, pp,
				   (debug_type **) NULL);
	if (memtype == DEBUG_TYPE_NULL)
	  return DEBUG_TYPE_NULL;

	dtype = debug_make_offset_type (dhandle, domain, memtype);
      }
      break;

    case '#':
      /* Method (class & fn) type.  */
      if (**pp == '#')
	{
	  debug_type return_type;

	  ++*pp;
	  return_type = parse_stab_type (dhandle, info, (const char *) NULL,
					 pp, (debug_type **) NULL);
	  if (return_type == DEBUG_TYPE_NULL)
	    return DEBUG_TYPE_NULL;
	  if (**pp != ';')
	    {
	      bad_stab (orig);
	      return DEBUG_TYPE_NULL;
	    }
	  ++*pp;
	  dtype = debug_make_method_type (dhandle, return_type,
					  DEBUG_TYPE_NULL,
					  (debug_type *) NULL, FALSE);
	}
      else
	{
	  debug_type domain;
	  debug_type return_type;
	  debug_type *args;
	  unsigned int n;
	  unsigned int alloc;
	  bfd_boolean varargs;

	  domain = parse_stab_type (dhandle, info, (const char *) NULL,
				    pp, (debug_type **) NULL);
	  if (domain == DEBUG_TYPE_NULL)
	    return DEBUG_TYPE_NULL;

	  if (**pp != ',')
	    {
	      bad_stab (orig);
	      return DEBUG_TYPE_NULL;
	    }
	  ++*pp;

	  return_type = parse_stab_type (dhandle, info, (const char *) NULL,
					 pp, (debug_type **) NULL);
	  if (return_type == DEBUG_TYPE_NULL)
	    return DEBUG_TYPE_NULL;

	  alloc = 10;
	  args = (debug_type *) xmalloc (alloc * sizeof *args);
	  n = 0;
	  while (**pp != ';')
	    {
	      if (**pp != ',')
		{
		  bad_stab (orig);
		  return DEBUG_TYPE_NULL;
		}
	      ++*pp;

	      if (n + 1 >= alloc)
		{
		  alloc += 10;
		  args = ((debug_type *)
			  xrealloc (args, alloc * sizeof *args));
		}

	      args[n] = parse_stab_type (dhandle, info, (const char *) NULL,
					 pp, (debug_type **) NULL);
	      if (args[n] == DEBUG_TYPE_NULL)
		return DEBUG_TYPE_NULL;
	      ++n;
	    }
	  ++*pp;

	  /* If the last type is not void, then this function takes a
	     variable number of arguments.  Otherwise, we must strip
	     the void type.  */
	  if (n == 0
	      || debug_get_type_kind (dhandle, args[n - 1]) != DEBUG_KIND_VOID)
	    varargs = TRUE;
	  else
	    {
	      --n;
	      varargs = FALSE;
	    }

	  args[n] = DEBUG_TYPE_NULL;

	  dtype = debug_make_method_type (dhandle, return_type, domain, args,
					  varargs);
	}
      break;

    case 'r':
      /* Range type.  */
      dtype = parse_stab_range_type (dhandle, info, typename, pp, typenums);
      break;

    case 'b':
      /* FIXME: gdb checks os9k_stabs here.  */
      /* Sun ACC builtin int type.  */
      dtype = parse_stab_sun_builtin_type (dhandle, pp);
      break;

    case 'R':
      /* Sun ACC builtin float type.  */
      dtype = parse_stab_sun_floating_type (dhandle, pp);
      break;

    case 'e':
      /* Enumeration type.  */
      dtype = parse_stab_enum_type (dhandle, pp);
      break;

    case 's':
    case 'u':
      /* Struct or union type.  */
      dtype = parse_stab_struct_type (dhandle, info, typename, pp,
				      descriptor == 's', typenums);
      break;

    case 'a':
      /* Array type.  */
      if (**pp != 'r')
	{
	  bad_stab (orig);
	  return DEBUG_TYPE_NULL;
	}
      ++*pp;

      dtype = parse_stab_array_type (dhandle, info, pp, stringp);
      break;

    case 'S':
      dtype = debug_make_set_type (dhandle,
				   parse_stab_type (dhandle, info,
						    (const char *) NULL,
						    pp,
						    (debug_type **) NULL),
				   stringp);
      break;

    default:
      bad_stab (orig);
      return DEBUG_TYPE_NULL;
    }

  if (dtype == DEBUG_TYPE_NULL)
    return DEBUG_TYPE_NULL;

  if (typenums[0] != -1)
    {
      if (! stab_record_type (dhandle, info, typenums, dtype))
	return DEBUG_TYPE_NULL;
    }

  if (size != -1)
    {
      if (! debug_record_type_size (dhandle, dtype, (unsigned int) size))
	return DEBUG_TYPE_NULL;
    }

  return dtype;
}