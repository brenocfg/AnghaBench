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
 int /*<<< orphan*/  strcat (char*,char const*) ; 
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 int strlen (char const*) ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char**) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

char **
complete_on_enum (const char *enumlist[],
		  char *text,
		  char *word)
{
  char **matchlist;
  int sizeof_matchlist;
  int matches;
  int textlen = strlen (text);
  int i;
  const char *name;

  sizeof_matchlist = 10;
  matchlist = (char **) xmalloc (sizeof_matchlist * sizeof (char *));
  matches = 0;

  for (i = 0; (name = enumlist[i]) != NULL; i++)
    if (strncmp (name, text, textlen) == 0)
      {
	if (matches == sizeof_matchlist)
	  {
	    sizeof_matchlist *= 2;
	    matchlist = (char **) xrealloc ((char *) matchlist,
					    (sizeof_matchlist
					     * sizeof (char *)));
	  }

	matchlist[matches] = (char *)
	  xmalloc (strlen (word) + strlen (name) + 1);
	if (word == text)
	  strcpy (matchlist[matches], name);
	else if (word > text)
	  {
	    /* Return some portion of name.  */
	    strcpy (matchlist[matches], name + (word - text));
	  }
	else
	  {
	    /* Return some of text plus name.  */
	    strncpy (matchlist[matches], word, text - word);
	    matchlist[matches][text - word] = '\0';
	    strcat (matchlist[matches], name);
	  }
	++matches;
      }

  if (matches == 0)
    {
      xfree (matchlist);
      matchlist = 0;
    }
  else
    {
      matchlist = (char **) xrealloc ((char *) matchlist, ((matches + 1)
							* sizeof (char *)));
      matchlist[matches] = (char *) 0;
    }

  return matchlist;
}