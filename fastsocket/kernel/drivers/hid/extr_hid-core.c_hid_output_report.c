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
struct hid_report {scalar_t__ id; unsigned int maxfield; int /*<<< orphan*/ * field; } ;
typedef  int /*<<< orphan*/  __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  hid_output_field (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void hid_output_report(struct hid_report *report, __u8 *data)
{
	unsigned n;

	if (report->id > 0)
		*data++ = report->id;

	for (n = 0; n < report->maxfield; n++)
		hid_output_field(report->field[n], data);
}