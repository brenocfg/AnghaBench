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
typedef  int /*<<< orphan*/  in_dev_t ;

/* Variables and functions */
 int IN_MAX_DEVS ; 
 int /*<<< orphan*/ * in_devices ; 

__attribute__((used)) static in_dev_t *get_dev(int dev_id)
{
	if (dev_id < 0 || dev_id >= IN_MAX_DEVS)
		return NULL;

	return &in_devices[dev_id];
}