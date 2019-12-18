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
 int /*<<< orphan*/  fprintf_unfiltered (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  gdb_stdout ; 
 int /*<<< orphan*/  pop_output_files () ; 
 int /*<<< orphan*/ * saved_filename ; 
 int /*<<< orphan*/  xfree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void 
set_logging_off (char *args, int from_tty)
{
  if (saved_filename == NULL)
    return;

  pop_output_files ();
  if (from_tty)
    fprintf_unfiltered (gdb_stdout, "Done logging to %s.\n", saved_filename);
  xfree (saved_filename);
  saved_filename = NULL;
}