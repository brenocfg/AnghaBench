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
typedef  int /*<<< orphan*/  u8 ;
struct wps_registrar_device {int /*<<< orphan*/  uuid; int /*<<< orphan*/  dev; struct wps_registrar_device* next; } ;
struct wps_registrar {struct wps_registrar_device* devices; } ;
struct wps_device_data {int /*<<< orphan*/  mac_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_UUID_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 
 scalar_t__ os_zalloc (int) ; 
 int /*<<< orphan*/  wps_device_clone_data (int /*<<< orphan*/ *,struct wps_device_data*) ; 
 struct wps_registrar_device* wps_device_get (struct wps_registrar*,int /*<<< orphan*/ ) ; 

int wps_device_store(struct wps_registrar *reg,
		     struct wps_device_data *dev, const u8 *uuid)
{
	struct wps_registrar_device *d;

	d = wps_device_get(reg, dev->mac_addr);
	if (d == NULL) {
		d = (struct wps_registrar_device *)os_zalloc(sizeof(*d));
		if (d == NULL)
			return -1;
		d->next = reg->devices;
		reg->devices = d;
	}

	wps_device_clone_data(&d->dev, dev);
	os_memcpy(d->uuid, uuid, WPS_UUID_LEN);

	return 0;
}