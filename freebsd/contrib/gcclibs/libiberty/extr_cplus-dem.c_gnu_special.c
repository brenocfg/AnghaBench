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
struct work_stuff {int destructor; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 int /*<<< orphan*/  ISDIGIT (unsigned char) ; 
 char const* SCOPE_STRING (struct work_stuff*) ; 
 int consume_count (char const**) ; 
 char* cplus_markers ; 
 int demangle_qualified (struct work_stuff*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int demangle_template (struct work_stuff*,char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int do_type (struct work_stuff*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* internal_cplus_demangle (struct work_stuff*,char const*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,int) ; 
 int /*<<< orphan*/ * strchr (char*,char const) ; 
 int strcspn (char const*,char*) ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  string_appendn (int /*<<< orphan*/ *,char const*,int) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strpbrk (char const*,char*) ; 

__attribute__((used)) static int
gnu_special (struct work_stuff *work, const char **mangled, string *declp)
{
  int n;
  int success = 1;
  const char *p;

  if ((*mangled)[0] == '_'
      && strchr (cplus_markers, (*mangled)[1]) != NULL
      && (*mangled)[2] == '_')
    {
      /* Found a GNU style destructor, get past "_<CPLUS_MARKER>_" */
      (*mangled) += 3;
      work -> destructor += 1;
    }
  else if ((*mangled)[0] == '_'
	   && (((*mangled)[1] == '_'
		&& (*mangled)[2] == 'v'
		&& (*mangled)[3] == 't'
		&& (*mangled)[4] == '_')
	       || ((*mangled)[1] == 'v'
		   && (*mangled)[2] == 't'
		   && strchr (cplus_markers, (*mangled)[3]) != NULL)))
    {
      /* Found a GNU style virtual table, get past "_vt<CPLUS_MARKER>"
         and create the decl.  Note that we consume the entire mangled
	 input string, which means that demangle_signature has no work
	 to do.  */
      if ((*mangled)[2] == 'v')
	(*mangled) += 5; /* New style, with thunks: "__vt_" */
      else
	(*mangled) += 4; /* Old style, no thunks: "_vt<CPLUS_MARKER>" */
      while (**mangled != '\0')
	{
	  switch (**mangled)
	    {
	    case 'Q':
	    case 'K':
	      success = demangle_qualified (work, mangled, declp, 0, 1);
	      break;
	    case 't':
	      success = demangle_template (work, mangled, declp, 0, 1,
					   1);
	      break;
	    default:
	      if (ISDIGIT((unsigned char)*mangled[0]))
		{
		  n = consume_count(mangled);
		  /* We may be seeing a too-large size, or else a
		     ".<digits>" indicating a static local symbol.  In
		     any case, declare victory and move on; *don't* try
		     to use n to allocate.  */
		  if (n > (int) strlen (*mangled))
		    {
		      success = 1;
		      break;
		    }
		}
	      else
		{
		  n = strcspn (*mangled, cplus_markers);
		}
	      string_appendn (declp, *mangled, n);
	      (*mangled) += n;
	    }

	  p = strpbrk (*mangled, cplus_markers);
	  if (success && ((p == NULL) || (p == *mangled)))
	    {
	      if (p != NULL)
		{
		  string_append (declp, SCOPE_STRING (work));
		  (*mangled)++;
		}
	    }
	  else
	    {
	      success = 0;
	      break;
	    }
	}
      if (success)
	string_append (declp, " virtual table");
    }
  else if ((*mangled)[0] == '_'
	   && (strchr("0123456789Qt", (*mangled)[1]) != NULL)
	   && (p = strpbrk (*mangled, cplus_markers)) != NULL)
    {
      /* static data member, "_3foo$varname" for example */
      (*mangled)++;
      switch (**mangled)
	{
	case 'Q':
	case 'K':
	  success = demangle_qualified (work, mangled, declp, 0, 1);
	  break;
	case 't':
	  success = demangle_template (work, mangled, declp, 0, 1, 1);
	  break;
	default:
	  n = consume_count (mangled);
	  if (n < 0 || n > (long) strlen (*mangled))
	    {
	      success = 0;
	      break;
	    }

	  if (n > 10 && strncmp (*mangled, "_GLOBAL_", 8) == 0
	      && (*mangled)[9] == 'N'
	      && (*mangled)[8] == (*mangled)[10]
	      && strchr (cplus_markers, (*mangled)[8]))
	    {
	      /* A member of the anonymous namespace.  There's information
		 about what identifier or filename it was keyed to, but
		 it's just there to make the mangled name unique; we just
		 step over it.  */
	      string_append (declp, "{anonymous}");
	      (*mangled) += n;

	      /* Now p points to the marker before the N, so we need to
		 update it to the first marker after what we consumed.  */
	      p = strpbrk (*mangled, cplus_markers);
	      break;
	    }

	  string_appendn (declp, *mangled, n);
	  (*mangled) += n;
	}
      if (success && (p == *mangled))
	{
	  /* Consumed everything up to the cplus_marker, append the
	     variable name.  */
	  (*mangled)++;
	  string_append (declp, SCOPE_STRING (work));
	  n = strlen (*mangled);
	  string_appendn (declp, *mangled, n);
	  (*mangled) += n;
	}
      else
	{
	  success = 0;
	}
    }
  else if (strncmp (*mangled, "__thunk_", 8) == 0)
    {
      int delta;

      (*mangled) += 8;
      delta = consume_count (mangled);
      if (delta == -1)
	success = 0;
      else
	{
	  char *method = internal_cplus_demangle (work, ++*mangled);

	  if (method)
	    {
	      char buf[50];
	      sprintf (buf, "virtual function thunk (delta:%d) for ", -delta);
	      string_append (declp, buf);
	      string_append (declp, method);
	      free (method);
	      n = strlen (*mangled);
	      (*mangled) += n;
	    }
	  else
	    {
	      success = 0;
	    }
	}
    }
  else if (strncmp (*mangled, "__t", 3) == 0
	   && ((*mangled)[3] == 'i' || (*mangled)[3] == 'f'))
    {
      p = (*mangled)[3] == 'i' ? " type_info node" : " type_info function";
      (*mangled) += 4;
      switch (**mangled)
	{
	case 'Q':
	case 'K':
	  success = demangle_qualified (work, mangled, declp, 0, 1);
	  break;
	case 't':
	  success = demangle_template (work, mangled, declp, 0, 1, 1);
	  break;
	default:
	  success = do_type (work, mangled, declp);
	  break;
	}
      if (success && **mangled != '\0')
	success = 0;
      if (success)
	string_append (declp, p);
    }
  else
    {
      success = 0;
    }
  return (success);
}