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
struct t10_wwn {char* unit_serial; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*,char*) ; 

__attribute__((used)) static ssize_t target_core_dev_wwn_show_attr_vpd_unit_serial(
	struct t10_wwn *t10_wwn,
	char *page)
{
	return sprintf(page, "T10 VPD Unit Serial Number: %s\n",
		&t10_wwn->unit_serial[0]);
}