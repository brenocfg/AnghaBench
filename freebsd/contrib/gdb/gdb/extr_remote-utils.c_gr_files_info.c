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
struct target_ops {int to_shortname; } ;

/* Variables and functions */
 int baud_rate ; 
 int bfd_get_filename (scalar_t__) ; 
 scalar_t__ exec_bfd ; 
 int /*<<< orphan*/  printf_filtered (char*,...) ; 
 int sr_get_device () ; 

void
gr_files_info (struct target_ops *ops)
{
#ifdef __GO32__
  printf_filtered ("\tAttached to DOS asynctsr\n");
#else
  printf_filtered ("\tAttached to %s", sr_get_device ());
  if (baud_rate != -1)
    printf_filtered ("at %d baud", baud_rate);
  printf_filtered ("\n");
#endif

  if (exec_bfd)
    {
      printf_filtered ("\tand running program %s\n",
		       bfd_get_filename (exec_bfd));
    }
  printf_filtered ("\tusing the %s protocol.\n", ops->to_shortname);
}