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
 int /*<<< orphan*/  PREFIX (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PROMPT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SUFFIX (int /*<<< orphan*/ ) ; 
 scalar_t__ alloca (scalar_t__) ; 
 int annotation_level ; 
 char* async_annotation_suffix ; 
 int /*<<< orphan*/  pop_prompt () ; 
 int /*<<< orphan*/  push_prompt (char*,char*,char*) ; 
 int /*<<< orphan*/  strcat (char*,char*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 scalar_t__ strlen (char*) ; 
 int /*<<< orphan*/  warning (char*) ; 

__attribute__((used)) static void
change_annotation_level (void)
{
  char *prefix, *suffix;

  if (!PREFIX (0) || !PROMPT (0) || !SUFFIX (0))
    {
      /* The prompt stack has not been initialized to "", we are
         using gdb w/o the --async switch */
      warning ("Command has same effect as set annotate");
      return;
    }

  if (annotation_level > 1)
    {
      if (!strcmp (PREFIX (0), "") && !strcmp (SUFFIX (0), ""))
	{
	  /* Push a new prompt if the previous annotation_level was not >1. */
	  prefix = (char *) alloca (strlen (async_annotation_suffix) + 10);
	  strcpy (prefix, "\n\032\032pre-");
	  strcat (prefix, async_annotation_suffix);
	  strcat (prefix, "\n");

	  suffix = (char *) alloca (strlen (async_annotation_suffix) + 6);
	  strcpy (suffix, "\n\032\032");
	  strcat (suffix, async_annotation_suffix);
	  strcat (suffix, "\n");

	  push_prompt (prefix, (char *) 0, suffix);
	}
    }
  else
    {
      if (strcmp (PREFIX (0), "") && strcmp (SUFFIX (0), ""))
	{
	  /* Pop the top of the stack, we are going back to annotation < 1. */
	  pop_prompt ();
	}
    }
}