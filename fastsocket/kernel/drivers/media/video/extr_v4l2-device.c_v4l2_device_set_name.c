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
struct v4l2_device {int /*<<< orphan*/  name; } ;
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,char const*,int) ; 
 int strlen (char const*) ; 

int v4l2_device_set_name(struct v4l2_device *v4l2_dev, const char *basename,
						atomic_t *instance)
{
	int num = atomic_inc_return(instance) - 1;
	int len = strlen(basename);

	if (basename[len - 1] >= '0' && basename[len - 1] <= '9')
		snprintf(v4l2_dev->name, sizeof(v4l2_dev->name),
				"%s-%d", basename, num);
	else
		snprintf(v4l2_dev->name, sizeof(v4l2_dev->name),
				"%s%d", basename, num);
	return num;
}