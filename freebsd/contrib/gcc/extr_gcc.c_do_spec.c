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
 int /*<<< orphan*/ * argbuf ; 
 int argbuf_index ; 
 int do_spec_2 (char const*) ; 
 int execute () ; 
 int /*<<< orphan*/  set_collect_gcc_options () ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

int
do_spec (const char *spec)
{
  int value;

  value = do_spec_2 (spec);

  /* Force out any unfinished command.
     If -pipe, this forces out the last command if it ended in `|'.  */
  if (value == 0)
    {
      if (argbuf_index > 0 && !strcmp (argbuf[argbuf_index - 1], "|"))
	argbuf_index--;

      set_collect_gcc_options ();

      if (argbuf_index > 0)
	value = execute ();
    }

  return value;
}