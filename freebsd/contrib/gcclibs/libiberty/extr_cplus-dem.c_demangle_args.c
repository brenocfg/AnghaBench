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
struct work_stuff {scalar_t__ nrepeats; int ntypes; char** typevec; } ;
typedef  int /*<<< orphan*/  string ;

/* Variables and functions */
 scalar_t__ ARM_DEMANGLING ; 
 scalar_t__ EDG_DEMANGLING ; 
 scalar_t__ HP_DEMANGLING ; 
 scalar_t__ LUCID_DEMANGLING ; 
 scalar_t__ PRINT_ARG_TYPES ; 
 int consume_count (char const**) ; 
 int /*<<< orphan*/  do_arg (struct work_stuff*,char const**,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_count (char const**,int*) ; 
 int /*<<< orphan*/  string_append (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  string_appends (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  string_delete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
demangle_args (struct work_stuff *work, const char **mangled,
               string *declp)
{
  string arg;
  int need_comma = 0;
  int r;
  int t;
  const char *tem;
  char temptype;

  if (PRINT_ARG_TYPES)
    {
      string_append (declp, "(");
      if (**mangled == '\0')
	{
	  string_append (declp, "void");
	}
    }

  while ((**mangled != '_' && **mangled != '\0' && **mangled != 'e')
	 || work->nrepeats > 0)
    {
      if ((**mangled == 'N') || (**mangled == 'T'))
	{
	  temptype = *(*mangled)++;

	  if (temptype == 'N')
	    {
	      if (!get_count (mangled, &r))
		{
		  return (0);
		}
	    }
	  else
	    {
	      r = 1;
	    }
          if ((HP_DEMANGLING || ARM_DEMANGLING || EDG_DEMANGLING) && work -> ntypes >= 10)
            {
              /* If we have 10 or more types we might have more than a 1 digit
                 index so we'll have to consume the whole count here. This
                 will lose if the next thing is a type name preceded by a
                 count but it's impossible to demangle that case properly
                 anyway. Eg if we already have 12 types is T12Pc "(..., type1,
                 Pc, ...)"  or "(..., type12, char *, ...)" */
              if ((t = consume_count(mangled)) <= 0)
                {
                  return (0);
                }
            }
          else
	    {
	      if (!get_count (mangled, &t))
	    	{
	          return (0);
	    	}
	    }
	  if (LUCID_DEMANGLING || ARM_DEMANGLING || HP_DEMANGLING || EDG_DEMANGLING)
	    {
	      t--;
	    }
	  /* Validate the type index.  Protect against illegal indices from
	     malformed type strings.  */
	  if ((t < 0) || (t >= work -> ntypes))
	    {
	      return (0);
	    }
	  while (work->nrepeats > 0 || --r >= 0)
	    {
	      tem = work -> typevec[t];
	      if (need_comma && PRINT_ARG_TYPES)
		{
		  string_append (declp, ", ");
		}
	      if (!do_arg (work, &tem, &arg))
		{
		  return (0);
		}
	      if (PRINT_ARG_TYPES)
		{
		  string_appends (declp, &arg);
		}
	      string_delete (&arg);
	      need_comma = 1;
	    }
	}
      else
	{
	  if (need_comma && PRINT_ARG_TYPES)
	    string_append (declp, ", ");
	  if (!do_arg (work, mangled, &arg))
	    return (0);
	  if (PRINT_ARG_TYPES)
	    string_appends (declp, &arg);
	  string_delete (&arg);
	  need_comma = 1;
	}
    }

  if (**mangled == 'e')
    {
      (*mangled)++;
      if (PRINT_ARG_TYPES)
	{
	  if (need_comma)
	    {
	      string_append (declp, ",");
	    }
	  string_append (declp, "...");
	}
    }

  if (PRINT_ARG_TYPES)
    {
      string_append (declp, ")");
    }
  return (1);
}