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
struct target_ops {int dummy; } ;

/* Variables and functions */
 scalar_t__ attach_flag ; 
 int /*<<< orphan*/  inferior_ptid ; 
 int /*<<< orphan*/  nto_procfs_path ; 
 int /*<<< orphan*/  printf_unfiltered (char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  target_pid_to_str (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
procfs_files_info (struct target_ops *ignore)
{
  printf_unfiltered ("\tUsing the running image of %s %s via %s.\n",
		     attach_flag ? "attached" : "child",
		     target_pid_to_str (inferior_ptid), nto_procfs_path);
}