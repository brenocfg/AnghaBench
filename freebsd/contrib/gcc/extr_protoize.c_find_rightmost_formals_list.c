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
 scalar_t__ ISALPHA (unsigned char) ; 
 scalar_t__ ISSPACE (unsigned char const) ; 
 int /*<<< orphan*/  check_source (int,char const*) ; 
 char const* clean_read_ptr ; 
 char* forward_to_next_token_char (char const*) ; 

__attribute__((used)) static const char *
find_rightmost_formals_list (const char *clean_text_p)
{
  const char *end_formals;

  /* We are editing a function definition.  The line number we did a seek
     to contains the first token which immediately follows the entire set of
     formals lists which are part of this particular function definition
     header.

     Our job now is to scan leftwards in the clean text looking for the
     right-paren which is at the end of the function header's rightmost
     formals list.

     If we ignore whitespace, this right paren should be the first one we
     see which is (ignoring whitespace) immediately followed either by the
     open curly-brace beginning the function body or by an alphabetic
     character (in the case where the function definition is in old (K&R)
     style and there are some declarations of formal parameters).  */

   /* It is possible that the right paren we are looking for is on the
      current line (together with its following token).  Just in case that
      might be true, we start out here by skipping down to the right end of
      the current line before starting our scan.  */

  for (end_formals = clean_text_p; *end_formals != '\n'; end_formals++)
    continue;
  end_formals--;

#ifdef UNPROTOIZE

  /* Now scan backwards while looking for the right end of the rightmost
     formals list associated with this function definition.  */

  {
    char ch;
    const char *l_brace_p;

    /* Look leftward and try to find a right-paren.  */

    while (*end_formals != ')')
      {
	if (ISSPACE ((unsigned char)*end_formals))
	  while (ISSPACE ((unsigned char)*end_formals))
	    check_source (--end_formals > clean_read_ptr, 0);
	else
	  check_source (--end_formals > clean_read_ptr, 0);
      }

    ch = *(l_brace_p = forward_to_next_token_char (end_formals));
    /* Since we are unprotoizing an ANSI-style (prototyped) function
       definition, there had better not be anything (except whitespace)
       between the end of the ANSI formals list and the beginning of the
       function body (i.e. the '{').  */

    check_source (ch == '{', l_brace_p);
  }

#else /* !defined (UNPROTOIZE) */

  /* Now scan backwards while looking for the right end of the rightmost
     formals list associated with this function definition.  */

  while (1)
    {
      char ch;
      const char *l_brace_p;

      /* Look leftward and try to find a right-paren.  */

      while (*end_formals != ')')
	{
	  if (ISSPACE ((const unsigned char)*end_formals))
	    while (ISSPACE ((const unsigned char)*end_formals))
	      check_source (--end_formals > clean_read_ptr, 0);
	  else
	    check_source (--end_formals > clean_read_ptr, 0);
	}

      ch = *(l_brace_p = forward_to_next_token_char (end_formals));

      /* Since it is possible that we found a right paren before the starting
	 '{' of the body which IS NOT the one at the end of the real K&R
	 formals list (say for instance, we found one embedded inside one of
	 the old K&R formal parameter declarations) we have to check to be
	 sure that this is in fact the right paren that we were looking for.

	 The one we were looking for *must* be followed by either a '{' or
	 by an alphabetic character, while others *cannot* validly be followed
	 by such characters.  */

      if ((ch == '{') || ISALPHA ((unsigned char) ch))
	break;

      /* At this point, we have found a right paren, but we know that it is
	 not the one we were looking for, so backup one character and keep
	 looking.  */

      check_source (--end_formals > clean_read_ptr, 0);
    }

#endif /* !defined (UNPROTOIZE) */

  return end_formals;
}