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
 char** dupargv (char**) ; 
 int /*<<< orphan*/  erase_test (int) ; 
 int /*<<< orphan*/  expandargv (int*,char***) ; 
 int /*<<< orphan*/  freeargv (char**) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  run_replaces (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  writeout_test (int,char const*) ; 

int
run_tests (const char **test_data)
{
  int argc_after, argc_before;
  char ** argv_before, ** argv_after;
  int i, j, k, fails, failed;

  i = j = fails = 0;
  /* Loop over all the tests */
  while (test_data[j])
    {
      /* Write test data */
      writeout_test (i, test_data[j++]);
      /* Copy argv before */
      argv_before = dupargv ((char **) &test_data[j]);

      /* Count argc before/after */
      argc_before = 0;
      argc_after = 0;
      while (test_data[j + argc_before])
        argc_before++;
      j += argc_before + 1; /* Skip null */
      while (test_data[j + argc_after])
        argc_after++;

      /* Copy argv after */
      argv_after = dupargv ((char **) &test_data[j]);

      /* Run all possible replaces */
      for (k = 0; k < argc_before; k++)
        run_replaces (argv_before[k]);
      for (k = 0; k < argc_after; k++)
        run_replaces (argv_after[k]);

      /* Run test: Expand arguments */
      expandargv (&argc_before, &argv_before);

      failed = 0;
      /* Compare size first */
      if (argc_before != argc_after)
        {
          printf ("FAIL: test-expandargv-%d. Number of arguments don't match.\n", i);
	  failed++;
        }
      /* Compare each of the argv's ... */
      else
        for (k = 0; k < argc_after; k++)
          if (strncmp (argv_before[k], argv_after[k], strlen(argv_after[k])) != 0)
            {
              printf ("FAIL: test-expandargv-%d. Arguments don't match.\n", i);
              failed++;
            }

      if (!failed)
        printf ("PASS: test-expandargv-%d.\n", i);
      else
        fails++;

      freeargv (argv_before);
      freeargv (argv_after);
      /* Advance to next test */
      j += argc_after + 1;
      /* Erase test file */
      erase_test (i);
      i++;
    }
  return fails;
}