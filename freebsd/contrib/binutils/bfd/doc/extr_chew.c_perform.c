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
typedef  int /*<<< orphan*/  dict_type ;

/* Variables and functions */
 int /*<<< orphan*/  addr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ at (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  idx ; 
 scalar_t__ iscommand (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * lookup_word (char*) ; 
 int /*<<< orphan*/  nextword (int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  ptr ; 
 int /*<<< orphan*/  skip_past_newline () ; 
 int /*<<< orphan*/  stack ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  tos ; 
 scalar_t__ warning ; 

__attribute__((used)) static void
perform ()
{
  tos = stack;

  while (at (ptr, idx))
    {
      /* It's worth looking through the command list.  */
      if (iscommand (ptr, idx))
	{
	  char *next;
	  dict_type *word;

	  (void) nextword (addr (ptr, idx), &next);

	  word = lookup_word (next);

	  if (word)
	    {
	      exec (word);
	    }
	  else
	    {
	      if (warning)
		fprintf (stderr, "warning, %s is not recognised\n", next);
	      skip_past_newline ();
	    }

	}
      else
	skip_past_newline ();
    }
}