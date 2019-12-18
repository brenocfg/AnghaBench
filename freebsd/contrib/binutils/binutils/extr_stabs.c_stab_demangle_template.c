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
struct stab_demangle_info {int dummy; } ;
typedef  int /*<<< orphan*/  debug_type ;
typedef  scalar_t__ bfd_boolean ;

/* Variables and functions */
 int /*<<< orphan*/  DMGL_ANSI ; 
 scalar_t__ FALSE ; 
 scalar_t__ ISDIGIT (char const) ; 
 scalar_t__ TRUE ; 
 int /*<<< orphan*/  abort () ; 
 char* concat (char*,char*,char const*) ; 
 char* cplus_demangle (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* savestring (char const*,int) ; 
 int /*<<< orphan*/  stab_bad_demangle (char const*) ; 
 unsigned int stab_demangle_count (char const**) ; 
 scalar_t__ stab_demangle_get_count (char const**,unsigned int*) ; 
 int /*<<< orphan*/  stab_demangle_type (struct stab_demangle_info*,char const**,int /*<<< orphan*/ *) ; 
 unsigned int strlen (char const*) ; 
 char* strstr (char*,char*) ; 

__attribute__((used)) static bfd_boolean
stab_demangle_template (struct stab_demangle_info *minfo, const char **pp,
			char **pname)
{
  const char *orig;
  unsigned int r, i;

  orig = *pp;

  ++*pp;

  /* Skip the template name.  */
  r = stab_demangle_count (pp);
  if (r == 0 || strlen (*pp) < r)
    {
      stab_bad_demangle (orig);
      return FALSE;
    }
  *pp += r;

  /* Get the size of the parameter list.  */
  if (stab_demangle_get_count (pp, &r) == 0)
    {
      stab_bad_demangle (orig);
      return FALSE;
    }

  for (i = 0; i < r; i++)
    {
      if (**pp == 'Z')
	{
	  /* This is a type parameter.  */
	  ++*pp;
	  if (! stab_demangle_type (minfo, pp, (debug_type *) NULL))
	    return FALSE;
	}
      else
	{
	  const char *old_p;
	  bfd_boolean pointerp, realp, integralp, charp, boolp;
	  bfd_boolean done;

	  old_p = *pp;
	  pointerp = FALSE;
	  realp = FALSE;
	  integralp = FALSE;
	  charp = FALSE;
	  boolp = FALSE;
	  done = FALSE;

	  /* This is a value parameter.  */

	  if (! stab_demangle_type (minfo, pp, (debug_type *) NULL))
	    return FALSE;

	  while (*old_p != '\0' && ! done)
	    {
	      switch (*old_p)
		{
		case 'P':
		case 'p':
		case 'R':
		  pointerp = TRUE;
		  done = TRUE;
		  break;
		case 'C':	/* Const.  */
		case 'S':	/* Signed.  */
		case 'U':	/* Unsigned.  */
		case 'V':	/* Volatile.  */
		case 'F':	/* Function.  */
		case 'M':	/* Member function.  */
		case 'O':	/* ??? */
		  ++old_p;
		  break;
		case 'Q':	/* Qualified name.  */
		  integralp = TRUE;
		  done = TRUE;
		  break;
		case 'T':	/* Remembered type.  */
		  abort ();
		case 'v':	/* Void.  */
		  abort ();
		case 'x':	/* Long long.  */
		case 'l':	/* Long.  */
		case 'i':	/* Int.  */
		case 's':	/* Short.  */
		case 'w':	/* Wchar_t.  */
		  integralp = TRUE;
		  done = TRUE;
		  break;
		case 'b':	/* Bool.  */
		  boolp = TRUE;
		  done = TRUE;
		  break;
		case 'c':	/* Char.  */
		  charp = TRUE;
		  done = TRUE;
		  break;
		case 'r':	/* Long double.  */
		case 'd':	/* Double.  */
		case 'f':	/* Float.  */
		  realp = TRUE;
		  done = TRUE;
		  break;
		default:
		  /* Assume it's a user defined integral type.  */
		  integralp = TRUE;
		  done = TRUE;
		  break;
		}
	    }

	  if (integralp)
	    {
	      if (**pp == 'm')
		++*pp;
	      while (ISDIGIT (**pp))
		++*pp;
	    }
	  else if (charp)
	    {
	      unsigned int val;

	      if (**pp == 'm')
		++*pp;
	      val = stab_demangle_count (pp);
	      if (val == 0)
		{
		  stab_bad_demangle (orig);
		  return FALSE;
		}
	    }
	  else if (boolp)
	    {
	      unsigned int val;

	      val = stab_demangle_count (pp);
	      if (val != 0 && val != 1)
		{
		  stab_bad_demangle (orig);
		  return FALSE;
		}
	    }
	  else if (realp)
	    {
	      if (**pp == 'm')
		++*pp;
	      while (ISDIGIT (**pp))
		++*pp;
	      if (**pp == '.')
		{
		  ++*pp;
		  while (ISDIGIT (**pp))
		    ++*pp;
		}
	      if (**pp == 'e')
		{
		  ++*pp;
		  while (ISDIGIT (**pp))
		    ++*pp;
		}
	    }
	  else if (pointerp)
	    {
	      unsigned int len;

	      len = stab_demangle_count (pp);
	      if (len == 0)
		{
		  stab_bad_demangle (orig);
		  return FALSE;
		}
	      *pp += len;
	    }
	}
    }

  /* We can translate this to a string fairly easily by invoking the
     regular demangling routine.  */
  if (pname != NULL)
    {
      char *s1, *s2, *s3, *s4 = NULL;
      char *from, *to;

      s1 = savestring (orig, *pp - orig);

      s2 = concat ("NoSuchStrinG__", s1, (const char *) NULL);

      free (s1);

      s3 = cplus_demangle (s2, DMGL_ANSI);

      free (s2);

      if (s3 != NULL)
	s4 = strstr (s3, "::NoSuchStrinG");
      if (s3 == NULL || s4 == NULL)
	{
	  stab_bad_demangle (orig);
	  if (s3 != NULL)
	    free (s3);
	  return FALSE;
	}

      /* Eliminating all spaces, except those between > characters,
         makes it more likely that the demangled name will match the
         name which g++ used as the structure name.  */
      for (from = to = s3; from != s4; ++from)
	if (*from != ' '
	    || (from[1] == '>' && from > s3 && from[-1] == '>'))
	  *to++ = *from;

      *pname = savestring (s3, to - s3);

      free (s3);
    }

  return TRUE;
}