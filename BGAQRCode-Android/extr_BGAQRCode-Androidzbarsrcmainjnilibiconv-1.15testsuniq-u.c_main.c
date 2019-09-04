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
 int /*<<< orphan*/  check_file (char const*,char const*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 char* program_name ; 
 int /*<<< orphan*/  stderr ; 

int
main (int argc, char **argv)
{
  const char *infile = "-";
  const char *outfile = "-";
  int optind = 1;

  program_name = argv[0];

  if (optind < argc)
    infile = argv[optind++];

  if (optind < argc)
    outfile = argv[optind++];

  if (optind < argc)
    {
      fprintf (stderr, "%s: too many arguments\n", program_name);
      exit (1);
    }

  check_file (infile, outfile);

  exit (0);
}