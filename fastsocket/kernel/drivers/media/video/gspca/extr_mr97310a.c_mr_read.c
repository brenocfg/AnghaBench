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
struct gspca_dev {int /*<<< orphan*/ * usb_buf; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  err (char*,int /*<<< orphan*/ ,int) ; 
 int usb_bulk_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  usb_rcvbulkpipe (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int mr_read(struct gspca_dev *gspca_dev, int len)
{
	int rc;

	rc = usb_bulk_msg(gspca_dev->dev,
			  usb_rcvbulkpipe(gspca_dev->dev, 3),
			  gspca_dev->usb_buf, len, NULL, 500);
	if (rc < 0)
		err("reg read [%02x] error %d",
		       gspca_dev->usb_buf[0], rc);
	return rc;
}