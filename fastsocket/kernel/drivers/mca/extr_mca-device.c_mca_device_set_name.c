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
struct mca_device {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char const*,int) ; 

void mca_device_set_name(struct mca_device *mca_dev, const char *name)
{
	if(!mca_dev)
		return;

	strlcpy(mca_dev->name, name, sizeof(mca_dev->name));
}