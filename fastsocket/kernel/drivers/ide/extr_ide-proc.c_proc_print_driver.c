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
struct seq_file {int dummy; } ;
struct ide_driver {int /*<<< orphan*/  version; } ;
struct device_driver {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ide_driver* to_ide_driver (struct device_driver*) ; 

__attribute__((used)) static int proc_print_driver(struct device_driver *drv, void *data)
{
	struct ide_driver *ide_drv = to_ide_driver(drv);
	struct seq_file *s = data;

	seq_printf(s, "%s version %s\n", drv->name, ide_drv->version);

	return 0;
}