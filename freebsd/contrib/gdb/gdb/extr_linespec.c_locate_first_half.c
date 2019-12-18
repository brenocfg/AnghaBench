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
 int /*<<< orphan*/  error (char*) ; 
 char* find_template_name_end (char*) ; 
 char* find_toplevel_char (char*,char) ; 
 scalar_t__ is_objc_method_format (char*) ; 
 char* strchr (char*,char) ; 

__attribute__((used)) static char *
locate_first_half (char **argptr, int *is_quote_enclosed)
{
  char *ii;
  char *p, *p1;
  int has_comma;

  /* Maybe we were called with a line range FILENAME:LINENUM,FILENAME:LINENUM
     and we must isolate the first half.  Outer layers will call again later
     for the second half.

     Don't count commas that appear in argument lists of overloaded
     functions, or in quoted strings.  It's stupid to go to this much
     trouble when the rest of the function is such an obvious roach hotel.  */
  ii = find_toplevel_char (*argptr, ',');
  has_comma = (ii != 0);

  /* Temporarily zap out second half to not confuse the code below.
     This is undone below. Do not change ii!!  */
  if (has_comma)
    {
      *ii = '\0';
    }

  /* Maybe arg is FILE : LINENUM or FILE : FUNCTION.  May also be
     CLASS::MEMBER, or NAMESPACE::NAME.  Look for ':', but ignore
     inside of <>.  */

  p = *argptr;
  if (p[0] == '"')
    {
      *is_quote_enclosed = 1;
      (*argptr)++;
      p++;
    }
  else
    *is_quote_enclosed = 0;
  for (; *p; p++)
    {
      if (p[0] == '<')
	{
	  char *temp_end = find_template_name_end (p);
	  if (!temp_end)
	    error ("malformed template specification in command");
	  p = temp_end;
	}
      /* Check for a colon and a plus or minus and a [ (which
         indicates an Objective-C method) */
      if (is_objc_method_format (p))
	{
	  break;
	}
      /* Check for the end of the first half of the linespec.  End of
         line, a tab, a double colon or the last single colon, or a
         space.  But if enclosed in double quotes we do not break on
         enclosed spaces.  */
      if (!*p
	  || p[0] == '\t'
	  || ((p[0] == ':')
	      && ((p[1] == ':') || (strchr (p + 1, ':') == NULL)))
	  || ((p[0] == ' ') && !*is_quote_enclosed))
	break;
      if (p[0] == '.' && strchr (p, ':') == NULL)
	{
	  /* Java qualified method.  Find the *last* '.', since the
	     others are package qualifiers.  */
	  for (p1 = p; *p1; p1++)
	    {
	      if (*p1 == '.')
		p = p1;
	    }
	  break;
	}
    }
  while (p[0] == ' ' || p[0] == '\t')
    p++;

  /* If the closing double quote was left at the end, remove it.  */
  if (*is_quote_enclosed)
    {
      char *closing_quote = strchr (p - 1, '"');
      if (closing_quote && closing_quote[1] == '\0')
	*closing_quote = '\0';
    }

  /* Now that we've safely parsed the first half, put back ',' so
     outer layers can see it.  */
  if (has_comma)
    *ii = ',';

  return p;
}