#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct hid_report {unsigned int maxfield; TYPE_2__** field; } ;
struct hid_device {TYPE_1__* report_enum; } ;
struct TYPE_4__ {unsigned int report_count; } ;
struct TYPE_3__ {struct hid_report** report_id_hash; } ;

/* Variables and functions */
 unsigned int HID_FEATURE_REPORT ; 
 unsigned int HID_MAX_IDS ; 
 int /*<<< orphan*/  hid_err (struct hid_device*,char*,unsigned int,...) ; 
 int /*<<< orphan*/ * hid_report_names ; 

struct hid_report *hid_validate_values(struct hid_device *hid,
				       unsigned int type, unsigned int id,
				       unsigned int field_index,
				       unsigned int report_counts)
{
	struct hid_report *report;

	if (type > HID_FEATURE_REPORT) {
		hid_err(hid, "invalid HID report type %u\n", type);
		return NULL;
	}

	if (id >= HID_MAX_IDS) {
		hid_err(hid, "invalid HID report id %u\n", id);
		return NULL;
	}

	/*
	 * Explicitly not using hid_get_report() here since it depends on
	 * ->numbered being checked, which may not always be the case when
	 * drivers go to access report values.
	 */
	report = hid->report_enum[type].report_id_hash[id];
	if (!report) {
		hid_err(hid, "missing %s %u\n", hid_report_names[type], id);
		return NULL;
	}
	if (report->maxfield <= field_index) {
		hid_err(hid, "not enough fields in %s %u\n",
			hid_report_names[type], id);
		return NULL;
	}
	if (report->field[field_index]->report_count < report_counts) {
		hid_err(hid, "not enough values in %s %u field %u\n",
			hid_report_names[type], id, field_index);
		return NULL;
	}
	return report;
}