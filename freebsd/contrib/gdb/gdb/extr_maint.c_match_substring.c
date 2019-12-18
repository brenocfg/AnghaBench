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
 int strlen (char const*) ; 
 char* strstr (char const*,char const*) ; 

__attribute__((used)) static int
match_substring (const char *string, const char *substr)
{
  int substr_len = strlen(substr);
  const char *tok;

  while ((tok = strstr (string, substr)) != NULL)
    {
      /* Got a partial match.  Is it a whole word? */
      if (tok == string
	  || tok[-1] == ' '
	  || tok[-1] == '\t')
      {
	/* Token is delimited at the front... */
	if (tok[substr_len] == ' '
	    || tok[substr_len] == '\t'
	    || tok[substr_len] == '\0')
	{
	  /* Token is delimited at the rear.  Got a whole-word match.  */
	  return 1;
	}
      }
      /* Token didn't match as a whole word.  Advance and try again.  */
      string = tok + 1;
    }
  return 0;
}