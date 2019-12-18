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
typedef  int /*<<< orphan*/  multisound_dev_t ;

/* Variables and functions */
 int ENOMEM ; 
 int MSND_MAX_DEVS ; 
 int /*<<< orphan*/ ** devs ; 
 int /*<<< orphan*/  num_devs ; 

int msnd_register(multisound_dev_t *dev)
{
	int i;

	for (i = 0; i < MSND_MAX_DEVS; ++i)
		if (devs[i] == NULL)
			break;

	if (i == MSND_MAX_DEVS)
		return -ENOMEM;

	devs[i] = dev;
	++num_devs;
	return 0;
}