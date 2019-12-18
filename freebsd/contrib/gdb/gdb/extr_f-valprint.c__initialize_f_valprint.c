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
 int /*<<< orphan*/  add_com (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  add_info (char*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  class_info ; 
 int /*<<< orphan*/  info_common_command ; 
 scalar_t__ xdb_commands ; 

void
_initialize_f_valprint (void)
{
  add_info ("common", info_common_command,
	    "Print out the values contained in a Fortran COMMON block.");
  if (xdb_commands)
    add_com ("lc", class_info, info_common_command,
	     "Print out the values contained in a Fortran COMMON block.");
}