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
 int /*<<< orphan*/  gcc_init_libintl () ; 
 int optind ; 
 int /*<<< orphan*/  print_usage (int) ; 
 int process_args (int,char**) ; 
 int /*<<< orphan*/  process_file (char*) ; 
 int /*<<< orphan*/  release_structures () ; 
 int /*<<< orphan*/  unlock_std_streams () ; 

int
main (int argc, char **argv)
{
  int argno;

  /* Unlock the stdio streams.  */
  unlock_std_streams ();

  gcc_init_libintl ();

  argno = process_args (argc, argv);
  if (optind == argc)
    print_usage (true);

  for (; argno != argc; argno++)
    {
      release_structures ();

      process_file (argv[argno]);
    }

  return 0;
}