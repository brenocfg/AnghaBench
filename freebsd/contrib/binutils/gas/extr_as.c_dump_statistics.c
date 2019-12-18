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
 char* _ (char*) ; 
 int /*<<< orphan*/  environ ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,long,...) ; 
 long get_run_time () ; 
 char* myname ; 
 int /*<<< orphan*/  obj_print_statistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  read_print_statistics (int /*<<< orphan*/ ) ; 
 scalar_t__ sbrk (int /*<<< orphan*/ ) ; 
 long start_time ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  subsegs_print_statistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol_print_statistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_print_statistics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_print_statistics (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dump_statistics (void)
{
#ifdef HAVE_SBRK
  char *lim = (char *) sbrk (0);
#endif
  long run_time = get_run_time () - start_time;

  fprintf (stderr, _("%s: total time in assembly: %ld.%06ld\n"),
	   myname, run_time / 1000000, run_time % 1000000);
#ifdef HAVE_SBRK
  fprintf (stderr, _("%s: data size %ld\n"),
	   myname, (long) (lim - (char *) &environ));
#endif

  subsegs_print_statistics (stderr);
  write_print_statistics (stderr);
  symbol_print_statistics (stderr);
  read_print_statistics (stderr);

#ifdef tc_print_statistics
  tc_print_statistics (stderr);
#endif

#ifdef obj_print_statistics
  obj_print_statistics (stderr);
#endif
}