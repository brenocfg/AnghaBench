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
struct interp {char* name; struct interp* next; } ;

/* Variables and functions */
 struct interp* interp_list ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  strncpy (char*,char*,int) ; 
 int /*<<< orphan*/  xfree (char**) ; 
 scalar_t__ xmalloc (int) ; 
 scalar_t__ xrealloc (char*,int) ; 

__attribute__((used)) static char **
interpreter_completer (char *text, char *word)
{
  int alloced = 0;
  int textlen;
  int num_matches;
  char **matches;
  struct interp *interp;

  /* We expect only a very limited number of interpreters, so just
     allocate room for all of them. */
  for (interp = interp_list; interp != NULL; interp = interp->next)
    ++alloced;
  matches = (char **) xmalloc (alloced * sizeof (char *));

  num_matches = 0;
  textlen = strlen (text);
  for (interp = interp_list; interp != NULL; interp = interp->next)
    {
      if (strncmp (interp->name, text, textlen) == 0)
	{
	  matches[num_matches] =
	    (char *) xmalloc (strlen (word) + strlen (interp->name) + 1);
	  if (word == text)
	    strcpy (matches[num_matches], interp->name);
	  else if (word > text)
	    {
	      /* Return some portion of interp->name */
	      strcpy (matches[num_matches], interp->name + (word - text));
	    }
	  else
	    {
	      /* Return some of text plus interp->name */
	      strncpy (matches[num_matches], word, text - word);
	      matches[num_matches][text - word] = '\0';
	      strcat (matches[num_matches], interp->name);
	    }
	  ++num_matches;
	}
    }

  if (num_matches == 0)
    {
      xfree (matches);
      matches = NULL;
    }
  else if (num_matches < alloced)
    {
      matches = (char **) xrealloc ((char *) matches, ((num_matches + 1)
						       * sizeof (char *)));
      matches[num_matches] = NULL;
    }

  return matches;
}