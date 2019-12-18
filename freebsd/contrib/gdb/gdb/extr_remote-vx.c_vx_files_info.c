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
 int /*<<< orphan*/  printf_unfiltered (char*,...) ; 
 scalar_t__ target_has_fp ; 
 int /*<<< orphan*/  vx_host ; 

__attribute__((used)) static void
vx_files_info (void)
{
  printf_unfiltered ("\tAttached to host `%s'", vx_host);
  printf_unfiltered (", which has %sfloating point", target_has_fp ? "" : "no ");
  printf_unfiltered (".\n");
}