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
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int in_dev_count ; 
 TYPE_1__* in_devices ; 
 int /*<<< orphan*/  lprintf (char*,char const*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 

int in_name_to_id(const char *dev_name)
{
	int i;

	for (i = 0; i < in_dev_count; i++)
		if (strcmp(dev_name, in_devices[i].name) == 0)
			break;

	if (i >= in_dev_count) {
		lprintf("input: in_name_to_id: no such device: %s\n", dev_name);
		return -1;
	}

	return i;
}