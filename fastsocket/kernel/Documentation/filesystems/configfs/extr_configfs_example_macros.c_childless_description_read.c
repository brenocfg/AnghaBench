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
struct childless {int dummy; } ;
typedef  int /*<<< orphan*/  ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  sprintf (char*,char*) ; 

__attribute__((used)) static ssize_t childless_description_read(struct childless *childless,
					  char *page)
{
	return sprintf(page,
"[01-childless]\n"
"\n"
"The childless subsystem is the simplest possible subsystem in\n"
"configfs.  It does not support the creation of child config_items.\n"
"It only has a few attributes.  In fact, it isn't much different\n"
"than a directory in /proc.\n");
}