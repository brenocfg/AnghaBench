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
struct cmd_list_element {char* name; scalar_t__ prefixlist; scalar_t__ func; int /*<<< orphan*/  abbrev_flag; struct cmd_list_element* next; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char**) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

char **
complete_on_cmdlist (struct cmd_list_element *list, char *text, char *word)
{
  struct cmd_list_element *ptr;
  char **matchlist;
  int sizeof_matchlist;
  int matches;
  int textlen = strlen (text);

  sizeof_matchlist = 10;
  matchlist = (char **) xmalloc (sizeof_matchlist * sizeof (char *));
  matches = 0;

  for (ptr = list; ptr; ptr = ptr->next)
    if (!strncmp (ptr->name, text, textlen)
	&& !ptr->abbrev_flag
	&& (ptr->func
	    || ptr->prefixlist))
      {
	if (matches == sizeof_matchlist)
	  {
	    sizeof_matchlist *= 2;
	    matchlist = (char **) xrealloc ((char *) matchlist,
					    (sizeof_matchlist
					     * sizeof (char *)));
	  }

	matchlist[matches] = (char *)
	  xmalloc (strlen (word) + strlen (ptr->name) + 1);
	if (word == text)
	  strcpy (matchlist[matches], ptr->name);
	else if (word > text)
	  {
	    /* Return some portion of ptr->name.  */
	    strcpy (matchlist[matches], ptr->name + (word - text));
	  }
	else
	  {
	    /* Return some of text plus ptr->name.  */
	    strncpy (matchlist[matches], word, text - word);
	    matchlist[matches][text - word] = '\0';
	    strcat (matchlist[matches], ptr->name);
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