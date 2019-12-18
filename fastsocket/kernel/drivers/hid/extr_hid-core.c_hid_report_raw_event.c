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
struct hid_report_enum {scalar_t__ numbered; } ;
struct hid_report {int size; unsigned int maxfield; int /*<<< orphan*/ * field; int /*<<< orphan*/  id; } ;
struct hid_device {int claimed; int /*<<< orphan*/  (* hiddev_report_event ) (struct hid_device*,struct hid_report*) ;struct hid_report_enum* report_enum; } ;

/* Variables and functions */
 int HID_CLAIMED_HIDDEV ; 
 int HID_CLAIMED_HIDRAW ; 
 int HID_CLAIMED_INPUT ; 
 int /*<<< orphan*/  dbg_hid (char*,int /*<<< orphan*/ ,int,int) ; 
 struct hid_report* hid_get_report (struct hid_report_enum*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hid_input_field (struct hid_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  hidinput_report_event (struct hid_device*,struct hid_report*) ; 
 int /*<<< orphan*/  hidraw_report_event (struct hid_device*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  stub1 (struct hid_device*,struct hid_report*) ; 

void hid_report_raw_event(struct hid_device *hid, int type, u8 *data, int size,
		int interrupt)
{
	struct hid_report_enum *report_enum = hid->report_enum + type;
	struct hid_report *report;
	unsigned int a;
	int rsize, csize = size;
	u8 *cdata = data;

	report = hid_get_report(report_enum, data);
	if (!report)
		return;

	if (report_enum->numbered) {
		cdata++;
		csize--;
	}

	rsize = ((report->size - 1) >> 3) + 1;

	if (csize < rsize) {
		dbg_hid("report %d is too short, (%d < %d)\n", report->id,
				csize, rsize);
		memset(cdata + csize, 0, rsize - csize);
	}

	if ((hid->claimed & HID_CLAIMED_HIDDEV) && hid->hiddev_report_event)
		hid->hiddev_report_event(hid, report);
	if (hid->claimed & HID_CLAIMED_HIDRAW) {
		/* numbered reports need to be passed with the report num */
		if (report_enum->numbered)
			hidraw_report_event(hid, data - 1, size + 1);
		else
			hidraw_report_event(hid, data, size);
	}

	for (a = 0; a < report->maxfield; a++)
		hid_input_field(hid, report->field[a], cdata, interrupt);

	if (hid->claimed & HID_CLAIMED_INPUT)
		hidinput_report_event(hid, report);
}