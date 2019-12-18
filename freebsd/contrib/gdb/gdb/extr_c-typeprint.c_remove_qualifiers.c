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
 scalar_t__ alloca (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char*) ; 

__attribute__((used)) static char *
remove_qualifiers (char *qid)
{
  int quoted = 0;		/* zero if we're not in quotes;
				   '"' if we're in a double-quoted string;
				   '\'' if we're in a single-quoted string.  */
  int depth = 0;		/* number of unclosed parens we've seen */
  char *parenstack = (char *) alloca (strlen (qid));
  char *scan;
  char *last = 0;		/* The character after the rightmost
				   `::' token we've seen so far.  */

  for (scan = qid; *scan; scan++)
    {
      if (quoted)
	{
	  if (*scan == quoted)
	    quoted = 0;
	  else if (*scan == '\\' && *(scan + 1))
	    scan++;
	}
      else if (scan[0] == ':' && scan[1] == ':')
	{
	  /* If we're inside parenthesis (i.e., an argument list) or
	     angle brackets (i.e., a list of template arguments), then
	     we don't record the position of this :: token, since it's
	     not relevant to the top-level structure we're trying
	     to operate on.  */
	  if (depth == 0)
	    {
	      last = scan + 2;
	      scan++;
	    }
	}
      else if (*scan == '"' || *scan == '\'')
	quoted = *scan;
      else if (*scan == '(')
	parenstack[depth++] = ')';
      else if (*scan == '[')
	parenstack[depth++] = ']';
      /* We're going to treat <> as a pair of matching characters,
	 since we're more likely to see those in template id's than
	 real less-than characters.  What a crock.  */
      else if (*scan == '<')
	parenstack[depth++] = '>';
      else if (*scan == ')' || *scan == ']' || *scan == '>')
	{
	  if (depth > 0 && parenstack[depth - 1] == *scan)
	    depth--;
	  else
	    {
	      /* We're going to do a little error recovery here.  If we
		 don't find a match for *scan on the paren stack, but
		 there is something lower on the stack that does match, we
		 pop the stack to that point.  */
	      int i;

	      for (i = depth - 1; i >= 0; i--)
		if (parenstack[i] == *scan)
		  {
		    depth = i;
		    break;
		  }
	    }
	}
    }

  if (last)
    return last;
  else
    /* We didn't find any :: tokens at the top level, so declare the
       whole thing an unqualified identifier.  */
    return qid;
}