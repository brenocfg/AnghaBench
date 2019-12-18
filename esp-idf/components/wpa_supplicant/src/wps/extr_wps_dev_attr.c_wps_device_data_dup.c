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
struct wps_device_data {int /*<<< orphan*/  rf_bands; int /*<<< orphan*/  os_version; int /*<<< orphan*/  pri_dev_type; void* serial_number; void* model_number; void* model_name; void* manufacturer; void* device_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  WPS_DEV_TYPE_LEN ; 
 int /*<<< orphan*/  os_memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* os_strdup (void*) ; 

void wps_device_data_dup(struct wps_device_data *dst,
			 const struct wps_device_data *src)
{
	if (src->device_name)
		dst->device_name = os_strdup(src->device_name);
	if (src->manufacturer)
		dst->manufacturer = os_strdup(src->manufacturer);
	if (src->model_name)
		dst->model_name = os_strdup(src->model_name);
	if (src->model_number)
		dst->model_number = os_strdup(src->model_number);
	if (src->serial_number)
		dst->serial_number = os_strdup(src->serial_number);
	os_memcpy(dst->pri_dev_type, src->pri_dev_type, WPS_DEV_TYPE_LEN);
	dst->os_version = src->os_version;
	dst->rf_bands = src->rf_bands;
}