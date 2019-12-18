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
struct smscore_device_t {int /*<<< orphan*/  device; int /*<<< orphan*/  devpath; } ;

/* Variables and functions */
 int /*<<< orphan*/  g_smscore_deviceslock ; 
 int /*<<< orphan*/  kmutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sms_info (char*,...) ; 
 int /*<<< orphan*/  smscore_init_ir (struct smscore_device_t*) ; 
 int smscore_notify_callbacks (struct smscore_device_t*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  smscore_registry_getmode (int /*<<< orphan*/ ) ; 
 int smscore_set_device_mode (struct smscore_device_t*,int /*<<< orphan*/ ) ; 

int smscore_start_device(struct smscore_device_t *coredev)
{
	int rc = smscore_set_device_mode(
			coredev, smscore_registry_getmode(coredev->devpath));
	if (rc < 0) {
		sms_info("set device mode faile , rc %d", rc);
		return rc;
	}

	kmutex_lock(&g_smscore_deviceslock);

	rc = smscore_notify_callbacks(coredev, coredev->device, 1);
	smscore_init_ir(coredev);

	sms_info("device %p started, rc %d", coredev, rc);

	kmutex_unlock(&g_smscore_deviceslock);

	return rc;
}