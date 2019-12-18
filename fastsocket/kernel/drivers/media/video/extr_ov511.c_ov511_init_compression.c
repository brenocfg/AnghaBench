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
struct usb_ov511 {int compress_inited; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  err (char*) ; 
 scalar_t__ ov511_upload_quan_tables (struct usb_ov511*) ; 
 int /*<<< orphan*/  phuv ; 
 int /*<<< orphan*/  phy ; 
 int /*<<< orphan*/  pvuv ; 
 int /*<<< orphan*/  pvy ; 
 int /*<<< orphan*/  qhuv ; 
 int /*<<< orphan*/  qhy ; 
 int /*<<< orphan*/  qvuv ; 
 int /*<<< orphan*/  qvy ; 
 int /*<<< orphan*/  reg_w (struct usb_ov511*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
ov511_init_compression(struct usb_ov511 *ov)
{
	int rc = 0;

	if (!ov->compress_inited) {
		reg_w(ov, 0x70, phy);
		reg_w(ov, 0x71, phuv);
		reg_w(ov, 0x72, pvy);
		reg_w(ov, 0x73, pvuv);
		reg_w(ov, 0x74, qhy);
		reg_w(ov, 0x75, qhuv);
		reg_w(ov, 0x76, qvy);
		reg_w(ov, 0x77, qvuv);

		if (ov511_upload_quan_tables(ov) < 0) {
			err("Error uploading quantization tables");
			rc = -EIO;
			goto out;
		}
	}

	ov->compress_inited = 1;
out:
	return rc;
}