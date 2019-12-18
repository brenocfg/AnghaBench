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
 int /*<<< orphan*/  freeargv (char**) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 int strlen (char*) ; 

char **
dupargv (char **argv)
{
  int argc;
  char **copy;
  
  if (argv == NULL)
    return NULL;
  
  /* the vector */
  for (argc = 0; argv[argc] != NULL; argc++);
  copy = (char **) malloc ((argc + 1) * sizeof (char *));
  if (copy == NULL)
    return NULL;
  
  /* the strings */
  for (argc = 0; argv[argc] != NULL; argc++)
    {
      int len = strlen (argv[argc]);
      copy[argc] = (char *) malloc (len + 1);
      if (copy[argc] == NULL)
	{
	  freeargv (copy);
	  return NULL;
	}
      strcpy (copy[argc], argv[argc]);
    }
  copy[argc] = NULL;
  return copy;
}