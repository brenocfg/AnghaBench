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
struct hid_device {int dummy; } ;
typedef  int __u8 ;

/* Variables and functions */
 unsigned long CP_RDESC_SWAPPED_MIN_MAX ; 
 scalar_t__ hid_get_drvdata (struct hid_device*) ; 

__attribute__((used)) static void cp_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int rsize)
{
	unsigned long quirks = (unsigned long)hid_get_drvdata(hdev);
	unsigned int i;

	if (!(quirks & CP_RDESC_SWAPPED_MIN_MAX))
		return;

	for (i = 0; i < rsize - 4; i++)
		if (rdesc[i] == 0x29 && rdesc[i + 2] == 0x19) {
			__u8 tmp;

			rdesc[i] = 0x19;
			rdesc[i + 2] = 0x29;
			tmp = rdesc[i + 3];
			rdesc[i + 3] = rdesc[i + 1];
			rdesc[i + 1] = tmp;
		}
}