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
struct parisc_device {TYPE_1__ dev; scalar_t__ hw_path; } ;
struct hardware_path {int* bc; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_set_name (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  get_node_path (int /*<<< orphan*/ ,struct hardware_path*) ; 
 int /*<<< orphan*/  sprintf (char*,char*,unsigned char) ; 

__attribute__((used)) static void setup_bus_id(struct parisc_device *padev)
{
	struct hardware_path path;
	char name[20];
	char *output = name;
	int i;

	get_node_path(padev->dev.parent, &path);

	for (i = 0; i < 6; i++) {
		if (path.bc[i] == -1)
			continue;
		output += sprintf(output, "%u:", (unsigned char) path.bc[i]);
	}
	sprintf(output, "%u", (unsigned char) padev->hw_path);
	dev_set_name(&padev->dev, name);
}