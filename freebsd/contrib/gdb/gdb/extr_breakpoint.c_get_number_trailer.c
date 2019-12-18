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
struct value {int dummy; } ;

/* Variables and functions */
 scalar_t__ TYPE_CODE (int /*<<< orphan*/ ) ; 
 scalar_t__ TYPE_CODE_INT ; 
 int /*<<< orphan*/  VALUE_TYPE (struct value*) ; 
 scalar_t__ alloca (int) ; 
 int atoi (char*) ; 
 int breakpoint_count ; 
 scalar_t__ isalnum (char) ; 
 scalar_t__ isspace (char) ; 
 int /*<<< orphan*/  lookup_internalvar (char*) ; 
 int /*<<< orphan*/  printf_filtered (char*) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 scalar_t__ value_as_long (struct value*) ; 
 struct value* value_of_internalvar (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
get_number_trailer (char **pp, int trailer)
{
  int retval = 0;	/* default */
  char *p = *pp;

  if (p == NULL)
    /* Empty line means refer to the last breakpoint.  */
    return breakpoint_count;
  else if (*p == '$')
    {
      /* Make a copy of the name, so we can null-terminate it
         to pass to lookup_internalvar().  */
      char *varname;
      char *start = ++p;
      struct value *val;

      while (isalnum (*p) || *p == '_')
	p++;
      varname = (char *) alloca (p - start + 1);
      strncpy (varname, start, p - start);
      varname[p - start] = '\0';
      val = value_of_internalvar (lookup_internalvar (varname));
      if (TYPE_CODE (VALUE_TYPE (val)) == TYPE_CODE_INT)
	retval = (int) value_as_long (val);
      else
	{
	  printf_filtered ("Convenience variable must have integer value.\n");
	  retval = 0;
	}
    }
  else
    {
      if (*p == '-')
	++p;
      while (*p >= '0' && *p <= '9')
	++p;
      if (p == *pp)
	/* There is no number here.  (e.g. "cond a == b").  */
	{
	  /* Skip non-numeric token */
	  while (*p && !isspace((int) *p))
	    ++p;
	  /* Return zero, which caller must interpret as error. */
	  retval = 0;
	}
      else
	retval = atoi (*pp);
    }
  if (!(isspace (*p) || *p == '\0' || *p == trailer))
    {
      /* Trailing junk: return 0 and let caller print error msg. */
      while (!(isspace (*p) || *p == '\0' || *p == trailer))
	++p;
      retval = 0;
    }
  while (isspace (*p))
    p++;
  *pp = p;
  return retval;
}