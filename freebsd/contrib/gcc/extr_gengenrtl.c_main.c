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
 int FATAL_EXIT_CODE ; 
 int SUCCESS_EXIT_CODE ; 
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 scalar_t__ ferror (int /*<<< orphan*/ ) ; 
 scalar_t__ fflush (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_formats () ; 
 int /*<<< orphan*/  gencode () ; 
 int /*<<< orphan*/  genheader () ; 
 int /*<<< orphan*/  genlegend () ; 
 int /*<<< orphan*/  stdout ; 

int
main (int argc, char **argv)
{
  find_formats ();
  genlegend ();

  if (argc == 2 && argv[1][0] == '-' && argv[1][1] == 'h')
    genheader ();
  else
    gencode ();

  if (ferror (stdout) || fflush (stdout) || fclose (stdout))
    return FATAL_EXIT_CODE;

  return SUCCESS_EXIT_CODE;
}