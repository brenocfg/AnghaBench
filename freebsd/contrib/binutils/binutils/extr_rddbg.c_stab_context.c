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
struct saved_stab {char* string; int type; int desc; int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int SAVE_STABS_COUNT ; 
 char* _ (char*) ; 
 char* bfd_get_stab_name (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  fprintf_vma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct saved_stab* saved_stabs ; 
 int saved_stabs_index ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void
stab_context (void)
{
  int i;

  fprintf (stderr, _("Last stabs entries before error:\n"));
  fprintf (stderr, "n_type n_desc n_value  string\n");

  i = saved_stabs_index;
  do
    {
      struct saved_stab *stabp;

      stabp = saved_stabs + i;
      if (stabp->string != NULL)
	{
	  const char *s;

	  s = bfd_get_stab_name (stabp->type);
	  if (s != NULL)
	    fprintf (stderr, "%-6s", s);
	  else if (stabp->type == 0)
	    fprintf (stderr, "HdrSym");
	  else
	    fprintf (stderr, "%-6d", stabp->type);
	  fprintf (stderr, " %-6d ", stabp->desc);
	  fprintf_vma (stderr, stabp->value);
	  if (stabp->type != 0)
	    fprintf (stderr, " %s", stabp->string);
	  fprintf (stderr, "\n");
	}
      i = (i + 1) % SAVE_STABS_COUNT;
    }
  while (i != saved_stabs_index);
}