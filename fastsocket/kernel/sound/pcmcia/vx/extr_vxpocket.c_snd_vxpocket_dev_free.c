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
struct vx_core {int dummy; } ;
struct snd_device {struct vx_core* device_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (struct vx_core*) ; 
 int /*<<< orphan*/  snd_vx_free_firmware (struct vx_core*) ; 

__attribute__((used)) static int snd_vxpocket_dev_free(struct snd_device *device)
{
	struct vx_core *chip = device->device_data;

	snd_vx_free_firmware(chip);
	kfree(chip);
	return 0;
}