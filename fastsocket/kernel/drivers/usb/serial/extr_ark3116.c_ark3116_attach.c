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
struct usb_serial {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARK3116_RCV (struct usb_serial*,int,int,int,int,int,int,char*) ; 
 int /*<<< orphan*/  ARK3116_SND (struct usb_serial*,int,int,int,int,int) ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dbg (char*) ; 
 scalar_t__ is_irda (struct usb_serial*) ; 
 int /*<<< orphan*/  kfree (char*) ; 
 char* kmalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ark3116_attach(struct usb_serial *serial)
{
	char *buf;

	buf = kmalloc(1, GFP_KERNEL);
	if (!buf) {
		dbg("error kmalloc -> out of mem?");
		return -ENOMEM;
	}

	if (is_irda(serial))
		dbg("IrDA mode");

	/* 3 */
	ARK3116_SND(serial, 3, 0xFE, 0x40, 0x0008, 0x0002);
	ARK3116_SND(serial, 4, 0xFE, 0x40, 0x0008, 0x0001);
	ARK3116_SND(serial, 5, 0xFE, 0x40, 0x0000, 0x0008);
	ARK3116_SND(serial, 6, 0xFE, 0x40, is_irda(serial) ? 0x0001 : 0x0000,
		    0x000B);

	if (is_irda(serial)) {
		ARK3116_SND(serial, 1001, 0xFE, 0x40, 0x0000, 0x000C);
		ARK3116_SND(serial, 1002, 0xFE, 0x40, 0x0041, 0x000D);
		ARK3116_SND(serial, 1003, 0xFE, 0x40, 0x0001, 0x000A);
	}

	/* <-- seq7 */
	ARK3116_RCV(serial,  7, 0xFE, 0xC0, 0x0000, 0x0003, 0x00, buf);
	ARK3116_SND(serial,  8, 0xFE, 0x40, 0x0080, 0x0003);
	ARK3116_SND(serial,  9, 0xFE, 0x40, 0x001A, 0x0000);
	ARK3116_SND(serial, 10, 0xFE, 0x40, 0x0000, 0x0001);
	ARK3116_SND(serial, 11, 0xFE, 0x40, 0x0000, 0x0003);

	/* <-- seq12 */
	ARK3116_RCV(serial, 12, 0xFE, 0xC0, 0x0000, 0x0004, 0x00, buf);
	ARK3116_SND(serial, 13, 0xFE, 0x40, 0x0000, 0x0004);

	/* 14 */
	ARK3116_RCV(serial, 14, 0xFE, 0xC0, 0x0000, 0x0004, 0x00, buf);
	ARK3116_SND(serial, 15, 0xFE, 0x40, 0x0000, 0x0004);

	/* 16 */
	ARK3116_RCV(serial, 16, 0xFE, 0xC0, 0x0000, 0x0004, 0x00, buf);
	/* --> seq17 */
	ARK3116_SND(serial, 17, 0xFE, 0x40, 0x0001, 0x0004);

	/* <-- seq18 */
	ARK3116_RCV(serial, 18, 0xFE, 0xC0, 0x0000, 0x0004, 0x01, buf);

	/* --> seq19 */
	ARK3116_SND(serial, 19, 0xFE, 0x40, 0x0003, 0x0004);

	/* <-- seq20 */
	/* seems like serial port status info (RTS, CTS, ...) */
	/* returns modem control line status?! */
	ARK3116_RCV(serial, 20, 0xFE, 0xC0, 0x0000, 0x0006, 0xFF, buf);

	/* set 9600 baud & do some init?! */
	ARK3116_SND(serial, 147, 0xFE, 0x40, 0x0083, 0x0003);
	ARK3116_SND(serial, 148, 0xFE, 0x40, 0x0038, 0x0000);
	ARK3116_SND(serial, 149, 0xFE, 0x40, 0x0001, 0x0001);
	if (is_irda(serial))
		ARK3116_SND(serial, 1004, 0xFE, 0x40, 0x0000, 0x0009);
	ARK3116_SND(serial, 150, 0xFE, 0x40, 0x0003, 0x0003);
	ARK3116_RCV(serial, 151, 0xFE, 0xC0, 0x0000, 0x0004, 0x03, buf);
	ARK3116_SND(serial, 152, 0xFE, 0x40, 0x0000, 0x0003);
	ARK3116_RCV(serial, 153, 0xFE, 0xC0, 0x0000, 0x0003, 0x00, buf);
	ARK3116_SND(serial, 154, 0xFE, 0x40, 0x0003, 0x0003);

	kfree(buf);
	return 0;
}