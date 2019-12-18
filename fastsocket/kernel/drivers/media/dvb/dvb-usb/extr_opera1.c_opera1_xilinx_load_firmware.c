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
typedef  int u8 ;
struct usb_device {int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/  data; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  OPERA_READ_MSG ; 
 int OPERA_WRITE_FX2 ; 
 int /*<<< orphan*/  OPERA_WRITE_MSG ; 
 int /*<<< orphan*/  err (char*,...) ; 
 int /*<<< orphan*/  info (char*,char const*) ; 
 int /*<<< orphan*/  kfree (int*) ; 
 int* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int opera1_xilinx_rw (struct usb_device*,int,int,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int opera1_xilinx_load_firmware(struct usb_device *dev,
				       const char *filename)
{
	const struct firmware *fw = NULL;
	u8 *b, *p;
	int ret = 0, i,fpgasize=40;
	u8 testval;
	info("start downloading fpga firmware %s",filename);

	if ((ret = request_firmware(&fw, filename, &dev->dev)) != 0) {
		err("did not find the firmware file. (%s) "
			"Please see linux/Documentation/dvb/ for more details on firmware-problems.",
			filename);
		return ret;
	} else {
		p = kmalloc(fw->size, GFP_KERNEL);
		opera1_xilinx_rw(dev, 0xbc, 0x00, &testval, 1, OPERA_READ_MSG);
		if (p != NULL && testval != 0x67) {

			u8 reset = 0, fpga_command = 0;
			memcpy(p, fw->data, fw->size);
			/* clear fpga ? */
			opera1_xilinx_rw(dev, 0xbc, 0xaa, &fpga_command, 1,
					 OPERA_WRITE_MSG);
			for (i = 0; i < fw->size;) {
				if ( (fw->size - i) <fpgasize){
				    fpgasize=fw->size-i;
				}
				b = (u8 *) p + i;
				if (opera1_xilinx_rw
					(dev, OPERA_WRITE_FX2, 0x0, b , fpgasize,
						OPERA_WRITE_MSG) != fpgasize
					) {
					err("error while transferring firmware");
					ret = -EINVAL;
					break;
				}
				i = i + fpgasize;
			}
			/* restart the CPU */
			if (ret || opera1_xilinx_rw
					(dev, 0xa0, 0xe600, &reset, 1,
					OPERA_WRITE_MSG) != 1) {
				err("could not restart the USB controller CPU.");
				ret = -EINVAL;
			}
		}
	}
	kfree(p);
	release_firmware(fw);
	return ret;
}