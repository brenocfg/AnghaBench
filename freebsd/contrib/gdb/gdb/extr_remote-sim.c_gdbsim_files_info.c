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
 char* bfd_get_filename (scalar_t__) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  gdbsim_desc ; 
 int /*<<< orphan*/  printf_filtered (char*,char*,...) ; 
 int /*<<< orphan*/  sim_info (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sr_get_debug () ; 
 int /*<<< orphan*/  target_shortname ; 

__attribute__((used)) static void
gdbsim_files_info (struct target_ops *target)
{
  char *file = "nothing";

  if (exec_bfd)
    file = bfd_get_filename (exec_bfd);

  if (sr_get_debug ())
    printf_filtered ("gdbsim_files_info: file \"%s\"\n", file);

  if (exec_bfd)
    {
      printf_filtered ("\tAttached to %s running program %s\n",
		       target_shortname, file);
      sim_info (gdbsim_desc, 0);
    }
}