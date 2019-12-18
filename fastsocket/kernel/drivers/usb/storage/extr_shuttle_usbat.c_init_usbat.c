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
struct usbat_info {int dummy; } ;
struct us_data {unsigned char* iobuf; scalar_t__ extra; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOIO ; 
 unsigned char USBAT_ATA_LBA_HI ; 
 unsigned char USBAT_ATA_LBA_ME ; 
 scalar_t__ USBAT_DEV_FLASH ; 
 int USBAT_FEAT_ET1 ; 
 int USBAT_FEAT_ET2 ; 
 int USBAT_FEAT_ETEN ; 
 int USBAT_UIO_1 ; 
 int USBAT_UIO_EPAD ; 
 int USBAT_UIO_OE0 ; 
 int USBAT_UIO_OE1 ; 
 int USB_STOR_TRANSPORT_ERROR ; 
 int USB_STOR_TRANSPORT_GOOD ; 
 int USB_STOR_XFER_GOOD ; 
 int /*<<< orphan*/  US_DEBUGP (char*) ; 
 scalar_t__ kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int usbat_device_enable_cdt (struct us_data*) ; 
 scalar_t__ usbat_get_device_type (struct us_data*) ; 
 int usbat_read_user_io (struct us_data*,unsigned char*) ; 
 int usbat_select_and_test_registers (struct us_data*) ; 
 int usbat_set_shuttle_features (struct us_data*,int,int,int,int,unsigned char,unsigned char) ; 
 scalar_t__ usbat_set_transport (struct us_data*,struct usbat_info*,int) ; 
 int usbat_write_user_io (struct us_data*,int,int) ; 

__attribute__((used)) static int init_usbat(struct us_data *us, int devicetype)
{
	int rc;
	struct usbat_info *info;
	unsigned char subcountH = USBAT_ATA_LBA_HI;
	unsigned char subcountL = USBAT_ATA_LBA_ME;
	unsigned char *status = us->iobuf;

	us->extra = kzalloc(sizeof(struct usbat_info), GFP_NOIO);
	if (!us->extra) {
		US_DEBUGP("init_usbat: Gah! Can't allocate storage for usbat info struct!\n");
		return 1;
	}
	info = (struct usbat_info *) (us->extra);

	/* Enable peripheral control signals */
	rc = usbat_write_user_io(us,
				 USBAT_UIO_OE1 | USBAT_UIO_OE0,
				 USBAT_UIO_EPAD | USBAT_UIO_1);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 1\n");

	msleep(2000);

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_TRANSPORT_GOOD)
		return rc;

	US_DEBUGP("INIT 2\n");

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 3\n");

	rc = usbat_select_and_test_registers(us);
	if (rc != USB_STOR_TRANSPORT_GOOD)
		return rc;

	US_DEBUGP("INIT 4\n");

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 5\n");

	/* Enable peripheral control signals and card detect */
	rc = usbat_device_enable_cdt(us);
	if (rc != USB_STOR_TRANSPORT_GOOD)
		return rc;

	US_DEBUGP("INIT 6\n");

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 7\n");

	msleep(1400);

	rc = usbat_read_user_io(us, status);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 8\n");

	rc = usbat_select_and_test_registers(us);
	if (rc != USB_STOR_TRANSPORT_GOOD)
		return rc;

	US_DEBUGP("INIT 9\n");

	/* At this point, we need to detect which device we are using */
	if (usbat_set_transport(us, info, devicetype))
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 10\n");

	if (usbat_get_device_type(us) == USBAT_DEV_FLASH) { 
		subcountH = 0x02;
		subcountL = 0x00;
	}
	rc = usbat_set_shuttle_features(us, (USBAT_FEAT_ETEN | USBAT_FEAT_ET2 | USBAT_FEAT_ET1),
									0x00, 0x88, 0x08, subcountH, subcountL);
	if (rc != USB_STOR_XFER_GOOD)
		return USB_STOR_TRANSPORT_ERROR;

	US_DEBUGP("INIT 11\n");

	return USB_STOR_TRANSPORT_GOOD;
}