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
typedef  int u8 ;
struct hid_report_enum {scalar_t__ numbered; } ;
struct hid_report {int id; } ;
struct hid_driver {int (* raw_event ) (struct hid_device*,struct hid_report*,int*,int) ;} ;
struct hid_device {struct hid_driver* driver; struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  GFP_ATOMIC ; 
 int HID_DEBUG_BUFSIZE ; 
 int /*<<< orphan*/  dbg_hid (char*) ; 
 int /*<<< orphan*/  hid_debug_event (struct hid_device*,char*) ; 
 struct hid_report* hid_get_report (struct hid_report_enum*,int*) ; 
 scalar_t__ hid_match_report (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  hid_report_raw_event (struct hid_device*,int,int*,int,int) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,...) ; 
 int stub1 (struct hid_device*,struct hid_report*,int*,int) ; 

int hid_input_report(struct hid_device *hid, int type, u8 *data, int size, int interrupt)
{
	struct hid_report_enum *report_enum;
	struct hid_driver *hdrv;
	struct hid_report *report;
	char *buf;
	unsigned int i;
	int ret;

	if (!hid || !hid->driver)
		return -ENODEV;
	report_enum = hid->report_enum + type;
	hdrv = hid->driver;

	if (!size) {
		dbg_hid("empty report\n");
		return -1;
	}

	buf = kmalloc(sizeof(char) * HID_DEBUG_BUFSIZE, GFP_ATOMIC);

	if (!buf) {
		report = hid_get_report(report_enum, data);
		goto nomem;
	}

	snprintf(buf, HID_DEBUG_BUFSIZE - 1,
			"\nreport (size %u) (%snumbered)\n", size, report_enum->numbered ? "" : "un");
	hid_debug_event(hid, buf);

	report = hid_get_report(report_enum, data);
	if (!report) {
		kfree(buf);
		return -1;
	}

	/* dump the report */
	snprintf(buf, HID_DEBUG_BUFSIZE - 1,
			"report %d (size %u) = ", report->id, size);
	hid_debug_event(hid, buf);
	for (i = 0; i < size; i++) {
		snprintf(buf, HID_DEBUG_BUFSIZE - 1,
				" %02x", data[i]);
		hid_debug_event(hid, buf);
	}
	hid_debug_event(hid, "\n");

	kfree(buf);

nomem:
	if (hdrv && hdrv->raw_event && hid_match_report(hid, report)) {
		ret = hdrv->raw_event(hid, report, data, size);
		if (ret != 0)
			return ret < 0 ? ret : 0;
	}

	hid_report_raw_event(hid, type, data, size, interrupt);

	return 0;
}