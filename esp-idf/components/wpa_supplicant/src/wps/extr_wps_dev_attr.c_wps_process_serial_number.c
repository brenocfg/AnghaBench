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
struct wps_device_data {char* serial_number; } ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_DEBUG ; 
 int /*<<< orphan*/  os_free (char*) ; 
 scalar_t__ os_malloc (size_t) ; 
 int /*<<< orphan*/  os_memcpy (char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_hexdump_ascii (int /*<<< orphan*/ ,char*,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  wpa_printf (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int wps_process_serial_number(struct wps_device_data *dev,
				     const u8 *str, size_t str_len)
{
	if (str == NULL) {
		wpa_printf(MSG_DEBUG,  "WPS: No Serial Number received");
		return -1;
	}

	wpa_hexdump_ascii(MSG_DEBUG, "WPS: Serial Number", str, str_len);

	os_free(dev->serial_number);
	dev->serial_number = (char *)os_malloc(str_len + 1);
	if (dev->serial_number == NULL)
		return -1;
	os_memcpy(dev->serial_number, str, str_len);
	dev->serial_number[str_len] = '\0';

	return 0;
}