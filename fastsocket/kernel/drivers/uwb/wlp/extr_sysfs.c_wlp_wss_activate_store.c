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
struct wlp_wss {int dummy; } ;
struct wlp_uuid {int /*<<< orphan*/ * data; } ;
struct uwb_dev_addr {int /*<<< orphan*/ * data; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int sscanf (char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned int*,unsigned int*,...) ; 
 int strlen (char*) ; 
 int wlp_wss_create_activate (struct wlp_wss*,struct wlp_uuid*,char*,unsigned int,unsigned int) ; 
 int wlp_wss_enroll_activate (struct wlp_wss*,struct wlp_uuid*,struct uwb_dev_addr*) ; 

ssize_t wlp_wss_activate_store(struct wlp_wss *wss,
			       const char *buf, size_t size)
{
	ssize_t result = -EINVAL;
	struct wlp_uuid wssid;
	struct uwb_dev_addr dev;
	struct uwb_dev_addr bcast = {.data = {0xff, 0xff} };
	char name[65];
	unsigned sec_status, accept;
	memset(name, 0, sizeof(name));
	result = sscanf(buf, "%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx %02hhx %02hhx %02hhx "
			"%02hhx:%02hhx",
			&wssid.data[0] , &wssid.data[1],
			&wssid.data[2] , &wssid.data[3],
			&wssid.data[4] , &wssid.data[5],
			&wssid.data[6] , &wssid.data[7],
			&wssid.data[8] , &wssid.data[9],
			&wssid.data[10], &wssid.data[11],
			&wssid.data[12], &wssid.data[13],
			&wssid.data[14], &wssid.data[15],
			&dev.data[1], &dev.data[0]);
	if (result == 16 || result == 17) {
		result = sscanf(buf, "%02hhx %02hhx %02hhx %02hhx "
				"%02hhx %02hhx %02hhx %02hhx "
				"%02hhx %02hhx %02hhx %02hhx "
				"%02hhx %02hhx %02hhx %02hhx "
				"%u %u %64c",
				&wssid.data[0] , &wssid.data[1],
				&wssid.data[2] , &wssid.data[3],
				&wssid.data[4] , &wssid.data[5],
				&wssid.data[6] , &wssid.data[7],
				&wssid.data[8] , &wssid.data[9],
				&wssid.data[10], &wssid.data[11],
				&wssid.data[12], &wssid.data[13],
				&wssid.data[14], &wssid.data[15],
				&sec_status, &accept, name);
		if (result == 16)
			result = wlp_wss_enroll_activate(wss, &wssid, &bcast);
		else if (result == 19) {
			sec_status = sec_status == 0 ? 0 : 1;
			accept = accept == 0 ? 0 : 1;
			/* We read name using %c, so the newline needs to be
			 * removed */
			if (strlen(name) != sizeof(name) - 1)
				name[strlen(name) - 1] = '\0';
			result = wlp_wss_create_activate(wss, &wssid, name,
							 sec_status, accept);
		} else
			result = -EINVAL;
	} else if (result == 18)
		result = wlp_wss_enroll_activate(wss, &wssid, &dev);
	else
		result = -EINVAL;
	return result < 0 ? result : size;
}