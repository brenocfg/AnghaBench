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
typedef  int /*<<< orphan*/ * mt_device_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 size_t minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * mt_devices ; 

__attribute__((used)) static mt_device_t
mt_get_device(dev_t devnum)
{
	return &mt_devices[minor(devnum)];
}