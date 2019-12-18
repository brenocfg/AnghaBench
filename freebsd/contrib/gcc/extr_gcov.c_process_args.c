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
 int flag_all_blocks ; 
 int flag_branches ; 
 int flag_counts ; 
 int flag_function_summary ; 
 int /*<<< orphan*/  flag_gcov_file ; 
 int flag_long_names ; 
 int flag_preserve_paths ; 
 int flag_unconditional ; 
 int getopt_long (int,char**,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  object_directory ; 
 int /*<<< orphan*/  optarg ; 
 int optind ; 
 int /*<<< orphan*/  options ; 
 int /*<<< orphan*/  print_usage (int) ; 
 int /*<<< orphan*/  print_version () ; 

__attribute__((used)) static int
process_args (int argc, char **argv)
{
  int opt;

  while ((opt = getopt_long (argc, argv, "abcfhlno:puv", options, NULL)) != -1)
    {
      switch (opt)
	{
	case 'a':
	  flag_all_blocks = 1;
	  break;
	case 'b':
	  flag_branches = 1;
	  break;
	case 'c':
	  flag_counts = 1;
	  break;
	case 'f':
	  flag_function_summary = 1;
	  break;
	case 'h':
	  print_usage (false);
	  /* print_usage will exit.  */
	case 'l':
	  flag_long_names = 1;
	  break;
	case 'n':
	  flag_gcov_file = 0;
	  break;
	case 'o':
	  object_directory = optarg;
	  break;
	case 'p':
	  flag_preserve_paths = 1;
	  break;
	case 'u':
	  flag_unconditional = 1;
	  break;
	case 'v':
	  print_version ();
	  /* print_version will exit.  */
	default:
	  print_usage (true);
	  /* print_usage will exit.  */
	}
    }

  return optind;
}