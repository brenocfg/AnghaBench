#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {char* name; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  dialog_clear () ; 
 int /*<<< orphan*/  dialog_input_result ; 
 int dialog_inputbox (char*,char*,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  extract_packages (int /*<<< orphan*/ ) ; 
 scalar_t__ my_system (char*,char const*,...) ; 
 int /*<<< orphan*/  null ; 
 TYPE_1__* partitions ; 
 int select_source_partition () ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
install_harddisk(void)
{
    const char *name;
    int part, ret;

    if ((part = select_source_partition()) <= -1)
	return;
    name = partitions[part].name;

    if (my_system("mount -t ext2 %s /source %s", name, null))
	return;
    ret = dialog_inputbox("Path in partition",
			  "Please enter the directory in which the "
			  "source files are.", 13, 50, "", FALSE);
    dialog_clear();
    if (ret != 0)
	return;
    /* XXX strdup */
    extract_packages(strdup(dialog_input_result));
    if (my_system("umount /source %s", null))
	return;
}