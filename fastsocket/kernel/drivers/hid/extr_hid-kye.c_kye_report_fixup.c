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
struct hid_device {int /*<<< orphan*/  dev; } ;
typedef  int __u8 ;

/* Variables and functions */
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void kye_report_fixup(struct hid_device *hdev, __u8 *rdesc,
		unsigned int rsize)
{
	if (rsize >= 74 &&
		rdesc[61] == 0x05 && rdesc[62] == 0x08 &&
		rdesc[63] == 0x19 && rdesc[64] == 0x08 &&
		rdesc[65] == 0x29 && rdesc[66] == 0x0f &&
		rdesc[71] == 0x75 && rdesc[72] == 0x08 &&
		rdesc[73] == 0x95 && rdesc[74] == 0x01) {
		dev_info(&hdev->dev, "fixing up Kye/Genius Ergo Mouse report "
				"descriptor\n");
		rdesc[62] = 0x09;
		rdesc[64] = 0x04;
		rdesc[66] = 0x07;
		rdesc[72] = 0x01;
		rdesc[74] = 0x08;
	}
}