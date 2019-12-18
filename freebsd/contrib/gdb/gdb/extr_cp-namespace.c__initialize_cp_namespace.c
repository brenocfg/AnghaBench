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
 int /*<<< orphan*/  add_cmd (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  class_maintenance ; 
 int /*<<< orphan*/  maint_cplus_cmd_list ; 
 int /*<<< orphan*/  maintenance_cplus_namespace ; 

void
_initialize_cp_namespace (void)
{
  add_cmd ("namespace", class_maintenance, maintenance_cplus_namespace,
	   "Print the list of possible C++ namespaces.",
	   &maint_cplus_cmd_list);
}