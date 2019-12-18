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
typedef  unsigned int u8 ;
struct hid_report_enum {struct hid_report** report_id_hash; scalar_t__ numbered; } ;
struct hid_report {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_hid (char*,unsigned int) ; 

__attribute__((used)) static struct hid_report *hid_get_report(struct hid_report_enum *report_enum,
		const u8 *data)
{
	struct hid_report *report;
	unsigned int n = 0;	/* Normally report number is 0 */

	/* Device uses numbered reports, data[0] is report number */
	if (report_enum->numbered)
		n = *data;

	report = report_enum->report_id_hash[n];
	if (report == NULL)
		dbg_hid("undefined report_id %u received\n", n);

	return report;
}