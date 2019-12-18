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
 int /*<<< orphan*/  abort () ; 
 int n_infiles ; 
 scalar_t__* outfiles ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char const*) ; 
 scalar_t__ xstrdup (char const*) ; 

__attribute__((used)) static const char *
replace_outfile_spec_function (int argc, const char **argv)
{
  int i;
  /* Must have exactly two arguments.  */
  if (argc != 2)
    abort ();

  for (i = 0; i < n_infiles; i++)
    {
      if (outfiles[i] && !strcmp (outfiles[i], argv[0]))
	outfiles[i] = xstrdup (argv[1]);
    }
  return NULL;
}