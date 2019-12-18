#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u32 ;
struct sisusb_usb_data {TYPE_1__* sisusb_dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int GETIREG (int /*<<< orphan*/ ,int,int*) ; 
 int GETREG (int /*<<< orphan*/ ,int*) ; 
 int SETIREG (int /*<<< orphan*/ ,int,char const) ; 
 int SETIREGAND (int /*<<< orphan*/ ,int,int) ; 
 int SETIREGOR (int /*<<< orphan*/ ,int,int) ; 
 int SETREG (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SISCAP ; 
 int /*<<< orphan*/  SISCR ; 
 int /*<<< orphan*/  SISMISCR ; 
 int /*<<< orphan*/  SISMISCW ; 
 int /*<<< orphan*/  SISPART1 ; 
 int /*<<< orphan*/  SISSR ; 
 int /*<<< orphan*/  SISVGAEN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*) ; 
 int sisusb_get_sdram_size (struct sisusb_usb_data*,int*,int,int) ; 
 int sisusb_getbuswidth (struct sisusb_usb_data*,int*,int*) ; 
 int sisusb_read_pci_config (struct sisusb_usb_data*,int,int*) ; 
 int sisusb_set_default_mode (struct sisusb_usb_data*,int /*<<< orphan*/ ) ; 
 int sisusb_triggersr16 (struct sisusb_usb_data*,int) ; 
 int sisusb_verify_mclk (struct sisusb_usb_data*) ; 

__attribute__((used)) static int
sisusb_init_gfxcore(struct sisusb_usb_data *sisusb)
{
	int ret = 0, i, j, bw, chab, iret, retry = 3;
	u8 tmp8, ramtype;
	u32 tmp32;
	static const char mclktable[] = {
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	};
	static const char eclktable[] = {
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143,
		0x3b, 0x22, 0x01, 143
	};
	static const char ramtypetable1[] = {
		0x00, 0x04, 0x60, 0x60,
		0x0f, 0x0f, 0x1f, 0x1f,
		0xba, 0xba, 0xba, 0xba,
		0xa9, 0xa9, 0xac, 0xac,
		0xa0, 0xa0, 0xa0, 0xa8,
		0x00, 0x00, 0x02, 0x02,
		0x30, 0x30, 0x40, 0x40
	};
	static const char ramtypetable2[] = {
		0x77, 0x77, 0x44, 0x44,
		0x77, 0x77, 0x44, 0x44,
		0x00, 0x00, 0x00, 0x00,
		0x5b, 0x5b, 0xab, 0xab,
		0x00, 0x00, 0xf0, 0xf8
	};

	while (retry--) {

		/* Enable VGA */
		ret = GETREG(SISVGAEN, &tmp8);
		ret |= SETREG(SISVGAEN, (tmp8 | 0x01));

		/* Enable GPU access to VRAM */
		ret |= GETREG(SISMISCR, &tmp8);
		ret |= SETREG(SISMISCW, (tmp8 | 0x01));

		if (ret) continue;

		/* Reset registers */
		ret |= SETIREGAND(SISCR, 0x5b, 0xdf);
		ret |= SETIREG(SISSR, 0x05, 0x86);
		ret |= SETIREGOR(SISSR, 0x20, 0x01);

		ret |= SETREG(SISMISCW, 0x67);

		for (i = 0x06; i <= 0x1f; i++) {
			ret |= SETIREG(SISSR, i, 0x00);
		}
		for (i = 0x21; i <= 0x27; i++) {
			ret |= SETIREG(SISSR, i, 0x00);
		}
		for (i = 0x31; i <= 0x3d; i++) {
			ret |= SETIREG(SISSR, i, 0x00);
		}
		for (i = 0x12; i <= 0x1b; i++) {
			ret |= SETIREG(SISSR, i, 0x00);
		}
		for (i = 0x79; i <= 0x7c; i++) {
			ret |= SETIREG(SISCR, i, 0x00);
		}

		if (ret) continue;

		ret |= SETIREG(SISCR, 0x63, 0x80);

		ret |= GETIREG(SISSR, 0x3a, &ramtype);
		ramtype &= 0x03;

		ret |= SETIREG(SISSR, 0x28, mclktable[ramtype * 4]);
		ret |= SETIREG(SISSR, 0x29, mclktable[(ramtype * 4) + 1]);
		ret |= SETIREG(SISSR, 0x2a, mclktable[(ramtype * 4) + 2]);

		ret |= SETIREG(SISSR, 0x2e, eclktable[ramtype * 4]);
		ret |= SETIREG(SISSR, 0x2f, eclktable[(ramtype * 4) + 1]);
		ret |= SETIREG(SISSR, 0x30, eclktable[(ramtype * 4) + 2]);

		ret |= SETIREG(SISSR, 0x07, 0x18);
		ret |= SETIREG(SISSR, 0x11, 0x0f);

		if (ret) continue;

		for (i = 0x15, j = 0; i <= 0x1b; i++, j++) {
			ret |= SETIREG(SISSR, i, ramtypetable1[(j*4) + ramtype]);
		}
		for (i = 0x40, j = 0; i <= 0x44; i++, j++) {
			ret |= SETIREG(SISCR, i, ramtypetable2[(j*4) + ramtype]);
		}

		ret |= SETIREG(SISCR, 0x49, 0xaa);

		ret |= SETIREG(SISSR, 0x1f, 0x00);
		ret |= SETIREG(SISSR, 0x20, 0xa0);
		ret |= SETIREG(SISSR, 0x23, 0xf6);
		ret |= SETIREG(SISSR, 0x24, 0x0d);
		ret |= SETIREG(SISSR, 0x25, 0x33);

		ret |= SETIREG(SISSR, 0x11, 0x0f);

		ret |= SETIREGOR(SISPART1, 0x2f, 0x01);

		ret |= SETIREGAND(SISCAP, 0x3f, 0xef);

		if (ret) continue;

		ret |= SETIREG(SISPART1, 0x00, 0x00);

		ret |= GETIREG(SISSR, 0x13, &tmp8);
		tmp8 >>= 4;

		ret |= SETIREG(SISPART1, 0x02, 0x00);
		ret |= SETIREG(SISPART1, 0x2e, 0x08);

		ret |= sisusb_read_pci_config(sisusb, 0x50, &tmp32);
		tmp32 &= 0x00f00000;
		tmp8 = (tmp32 == 0x100000) ? 0x33 : 0x03;
		ret |= SETIREG(SISSR, 0x25, tmp8);
		tmp8 = (tmp32 == 0x100000) ? 0xaa : 0x88;
		ret |= SETIREG(SISCR, 0x49, tmp8);

		ret |= SETIREG(SISSR, 0x27, 0x1f);
		ret |= SETIREG(SISSR, 0x31, 0x00);
		ret |= SETIREG(SISSR, 0x32, 0x11);
		ret |= SETIREG(SISSR, 0x33, 0x00);

		if (ret) continue;

		ret |= SETIREG(SISCR, 0x83, 0x00);

		ret |= sisusb_set_default_mode(sisusb, 0);

		ret |= SETIREGAND(SISSR, 0x21, 0xdf);
		ret |= SETIREGOR(SISSR, 0x01, 0x20);
		ret |= SETIREGOR(SISSR, 0x16, 0x0f);

		ret |= sisusb_triggersr16(sisusb, ramtype);

		/* Disable refresh */
		ret |= SETIREGAND(SISSR, 0x17, 0xf8);
		ret |= SETIREGOR(SISSR, 0x19, 0x03);

		ret |= sisusb_getbuswidth(sisusb, &bw, &chab);
		ret |= sisusb_verify_mclk(sisusb);

		if (ramtype <= 1) {
			ret |= sisusb_get_sdram_size(sisusb, &iret, bw, chab);
			if (iret) {
				dev_err(&sisusb->sisusb_dev->dev,"RAM size detection failed, assuming 8MB video RAM\n");
				ret |= SETIREG(SISSR,0x14,0x31);
				/* TODO */
			}
		} else {
			dev_err(&sisusb->sisusb_dev->dev, "DDR RAM device found, assuming 8MB video RAM\n");
			ret |= SETIREG(SISSR,0x14,0x31);
			/* *** TODO *** */
		}

		/* Enable refresh */
		ret |= SETIREG(SISSR, 0x16, ramtypetable1[4 + ramtype]);
		ret |= SETIREG(SISSR, 0x17, ramtypetable1[8 + ramtype]);
		ret |= SETIREG(SISSR, 0x19, ramtypetable1[16 + ramtype]);

		ret |= SETIREGOR(SISSR, 0x21, 0x20);

		ret |= SETIREG(SISSR, 0x22, 0xfb);
		ret |= SETIREG(SISSR, 0x21, 0xa5);

		if (ret == 0)
			break;
	}

	return ret;
}