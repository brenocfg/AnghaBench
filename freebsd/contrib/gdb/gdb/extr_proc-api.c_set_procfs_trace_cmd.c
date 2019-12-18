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
struct cmd_list_element {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  fflush (scalar_t__) ; 
 scalar_t__ procfs_file ; 

__attribute__((used)) static void
set_procfs_trace_cmd (char *args, int from_tty, struct cmd_list_element *c)
{
#if 0	/* not sure what I might actually need to do here, if anything */
  if (procfs_file)
    fflush (procfs_file);
#endif
}