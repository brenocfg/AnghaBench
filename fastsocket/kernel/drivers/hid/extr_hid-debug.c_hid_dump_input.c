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
struct hid_usage {int /*<<< orphan*/  hid; } ;
struct hid_device {int /*<<< orphan*/  debug_wait; } ;
typedef  int __s32 ;

/* Variables and functions */
 int HID_DEBUG_BUFSIZE ; 
 int /*<<< orphan*/  hid_debug_event (struct hid_device*,char*) ; 
 char* hid_resolv_usage (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 
 int strlen (char*) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void hid_dump_input(struct hid_device *hdev, struct hid_usage *usage, __s32 value)
{
	char *buf;
	int len;

	buf = hid_resolv_usage(usage->hid, NULL);
	if (!buf)
		return;
	len = strlen(buf);
	snprintf(buf + len, HID_DEBUG_BUFSIZE - len - 1, " = %d\n", value);

	hid_debug_event(hdev, buf);

	kfree(buf);
        wake_up_interruptible(&hdev->debug_wait);

}