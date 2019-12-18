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
struct switchstr {char* part1; scalar_t__ ordering; scalar_t__ validated; int /*<<< orphan*/  live_cond; scalar_t__ args; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWITCH_OK ; 
 char** argbuf ; 
 int argbuf_index ; 
 int /*<<< orphan*/  do_spec_1 (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_spec_2 (char const*) ; 
 int /*<<< orphan*/  fatal (char*,char*) ; 
 int n_switches ; 
 struct switchstr* switches ; 
 struct switchstr* xrealloc (struct switchstr*,int) ; 

__attribute__((used)) static void
do_self_spec (const char *spec)
{
  do_spec_2 (spec);
  do_spec_1 (" ", 0, NULL);

  if (argbuf_index > 0)
    {
      int i, first;

      first = n_switches;
      n_switches += argbuf_index;
      switches = xrealloc (switches,
			   sizeof (struct switchstr) * (n_switches + 1));

      switches[n_switches] = switches[first];
      for (i = 0; i < argbuf_index; i++)
	{
	  struct switchstr *sw;

	  /* Each switch should start with '-'.  */
	  if (argbuf[i][0] != '-')
	    fatal ("switch '%s' does not start with '-'", argbuf[i]);

	  sw = &switches[i + first];
	  sw->part1 = &argbuf[i][1];
	  sw->args = 0;
	  sw->live_cond = SWITCH_OK;
	  sw->validated = 0;
	  sw->ordering = 0;
	}
    }
}