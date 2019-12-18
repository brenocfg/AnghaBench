#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/ * part1; } ;

/* Variables and functions */
 scalar_t__ check_live_switch (int,unsigned int) ; 
 scalar_t__ do_spec_1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fatal (char*,char const*) ; 
 int /*<<< orphan*/  give_switch (int,int) ; 
 int n_switches ; 
 char* save_string (char const*,int) ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char const*,unsigned int) ; 
 int /*<<< orphan*/ * suffix_subst ; 
 TYPE_1__* switches ; 

__attribute__((used)) static const char *
process_brace_body (const char *p, const char *atom, const char *end_atom,
		    int starred, int matched)
{
  const char *body, *end_body;
  unsigned int nesting_level;
  bool have_subst     = false;

  /* Locate the closing } or ;, honoring nested braces.
     Trim trailing whitespace.  */
  body = p;
  nesting_level = 1;
  for (;;)
    {
      if (*p == '{')
	nesting_level++;
      else if (*p == '}')
	{
	  if (!--nesting_level)
	    break;
	}
      else if (*p == ';' && nesting_level == 1)
	break;
      else if (*p == '%' && p[1] == '*' && nesting_level == 1)
	have_subst = true;
      else if (*p == '\0')
	goto invalid;
      p++;
    }

  end_body = p;
  while (end_body[-1] == ' ' || end_body[-1] == '\t')
    end_body--;

  if (have_subst && !starred)
    goto invalid;

  if (matched)
    {
      /* Copy the substitution body to permanent storage and execute it.
	 If have_subst is false, this is a simple matter of running the
	 body through do_spec_1...  */
      char *string = save_string (body, end_body - body);
      if (!have_subst)
	{
	  if (do_spec_1 (string, 0, NULL) < 0)
	    return 0;
	}
      else
	{
	  /* ... but if have_subst is true, we have to process the
	     body once for each matching switch, with %* set to the
	     variant part of the switch.  */
	  unsigned int hard_match_len = end_atom - atom;
	  int i;

	  for (i = 0; i < n_switches; i++)
	    if (!strncmp (switches[i].part1, atom, hard_match_len)
		&& check_live_switch (i, hard_match_len))
	      {
		if (do_spec_1 (string, 0,
			       &switches[i].part1[hard_match_len]) < 0)
		  return 0;
		/* Pass any arguments this switch has.  */
		give_switch (i, 1);
		suffix_subst = NULL;
	      }
	}
    }

  return p;

 invalid:
  fatal ("braced spec body '%s' is invalid", body);
}