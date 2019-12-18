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
struct TYPE_2__ {int /*<<< orphan*/  parent; } ;
struct parisc_device {int /*<<< orphan*/  hw_path; TYPE_1__ dev; } ;
struct hardware_path {int /*<<< orphan*/  mod; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_node_path (int /*<<< orphan*/ ,struct hardware_path*) ; 
 char* print_hwpath (struct hardware_path*,char*) ; 

char *print_pa_hwpath(struct parisc_device *dev, char *output)
{
	struct hardware_path path;

	get_node_path(dev->dev.parent, &path);
	path.mod = dev->hw_path;
	return print_hwpath(&path, output);
}