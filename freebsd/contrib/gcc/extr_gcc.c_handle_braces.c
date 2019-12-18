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

/* Variables and functions */
 scalar_t__ ISIDNUM (char const) ; 
 int /*<<< orphan*/  SKIP_WHITE () ; 
 int /*<<< orphan*/  fatal (char*,char const*,char const) ; 
 int input_suffix_matches (char const*,char const*) ; 
 int /*<<< orphan*/  mark_matching_switches (char const*,char const*,int) ; 
 char* process_brace_body (char const*,char const*,char const*,int,int) ; 
 int /*<<< orphan*/  process_marked_switches () ; 
 int switch_matches (char const*,char const*,int) ; 

__attribute__((used)) static const char *
handle_braces (const char *p)
{
  const char *atom, *end_atom;
  const char *d_atom = NULL, *d_end_atom = NULL;
  const char *orig = p;

  bool a_is_suffix;
  bool a_is_starred;
  bool a_is_negated;
  bool a_matched;

  bool a_must_be_last = false;
  bool ordered_set    = false;
  bool disjunct_set   = false;
  bool disj_matched   = false;
  bool disj_starred   = true;
  bool n_way_choice   = false;
  bool n_way_matched  = false;

#define SKIP_WHITE() do { while (*p == ' ' || *p == '\t') p++; } while (0)

  do
    {
      if (a_must_be_last)
	goto invalid;

      /* Scan one "atom" (S in the description above of %{}, possibly
	 with !, ., or * modifiers).  */
      a_matched = a_is_suffix = a_is_starred = a_is_negated = false;

      SKIP_WHITE();
      if (*p == '!')
	p++, a_is_negated = true;

      SKIP_WHITE();
      if (*p == '.')
	p++, a_is_suffix = true;

      atom = p;
      while (ISIDNUM(*p) || *p == '-' || *p == '+' || *p == '='
	     || *p == ',' || *p == '.' || *p == '@')
	p++;
      end_atom = p;

      if (*p == '*')
	p++, a_is_starred = 1;

      SKIP_WHITE();
      switch (*p)
	{
	case '&': case '}':
	  /* Substitute the switch(es) indicated by the current atom.  */
	  ordered_set = true;
	  if (disjunct_set || n_way_choice || a_is_negated || a_is_suffix
	      || atom == end_atom)
	    goto invalid;

	  mark_matching_switches (atom, end_atom, a_is_starred);

	  if (*p == '}')
	    process_marked_switches ();
	  break;

	case '|': case ':':
	  /* Substitute some text if the current atom appears as a switch
	     or suffix.  */
	  disjunct_set = true;
	  if (ordered_set)
	    goto invalid;

	  if (atom == end_atom)
	    {
	      if (!n_way_choice || disj_matched || *p == '|'
		  || a_is_negated || a_is_suffix || a_is_starred)
		goto invalid;

	      /* An empty term may appear as the last choice of an
		 N-way choice set; it means "otherwise".  */
	      a_must_be_last = true;
	      disj_matched = !n_way_matched;
	      disj_starred = false;
	    }
	  else
	    {
	       if (a_is_suffix && a_is_starred)
		 goto invalid;

	       if (!a_is_starred)
		 disj_starred = false;

	       /* Don't bother testing this atom if we already have a
                  match.  */
	       if (!disj_matched && !n_way_matched)
		 {
		   if (a_is_suffix)
		     a_matched = input_suffix_matches (atom, end_atom);
		   else
		     a_matched = switch_matches (atom, end_atom, a_is_starred);

		   if (a_matched != a_is_negated)
		     {
		       disj_matched = true;
		       d_atom = atom;
		       d_end_atom = end_atom;
		     }
		 }
	    }

	  if (*p == ':')
	    {
	      /* Found the body, that is, the text to substitute if the
		 current disjunction matches.  */
	      p = process_brace_body (p + 1, d_atom, d_end_atom, disj_starred,
				      disj_matched && !n_way_matched);
	      if (p == 0)
		return 0;

	      /* If we have an N-way choice, reset state for the next
		 disjunction.  */
	      if (*p == ';')
		{
		  n_way_choice = true;
		  n_way_matched |= disj_matched;
		  disj_matched = false;
		  disj_starred = true;
		  d_atom = d_end_atom = NULL;
		}
	    }
	  break;

	default:
	  goto invalid;
	}
    }
  while (*p++ != '}');

  return p;

 invalid:
  fatal ("braced spec '%s' is invalid at '%c'", orig, *p);

#undef SKIP_WHITE
}