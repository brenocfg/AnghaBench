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
 int /*<<< orphan*/  exec_ops ; 
 int /*<<< orphan*/  printf_unfiltered (char*) ; 
 int /*<<< orphan*/  unpush_target (int /*<<< orphan*/ *) ; 

void
exec_file_clear (int from_tty)
{
  /* Remove exec file.  */
  unpush_target (&exec_ops);

  if (from_tty)
    printf_unfiltered ("No executable file now.\n");
}