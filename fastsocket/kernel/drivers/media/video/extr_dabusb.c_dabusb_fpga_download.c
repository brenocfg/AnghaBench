#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct firmware {int* data; } ;
typedef  TYPE_2__* pdabusb_t ;
typedef  TYPE_3__* pbulk_transfer_t ;
typedef  int /*<<< orphan*/  bulk_transfer_t ;
struct TYPE_15__ {int pipe; int* data; int size; } ;
struct TYPE_14__ {TYPE_1__* usbdev; } ;
struct TYPE_13__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int dabusb_bulk (TYPE_2__*,TYPE_3__*) ; 
 int dabusb_fpga_clear (TYPE_2__*,TYPE_3__*) ; 
 int dabusb_fpga_init (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  dbg (char*,...) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 TYPE_3__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mdelay (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dabusb_fpga_download (pdabusb_t s, const char *fname)
{
	pbulk_transfer_t b = kmalloc (sizeof (bulk_transfer_t), GFP_KERNEL);
	const struct firmware *fw;
	unsigned int blen, n;
	int ret;

	dbg("Enter dabusb_fpga_download (internal)");

	if (!b) {
		dev_err(&s->usbdev->dev,
			"kmalloc(sizeof(bulk_transfer_t))==NULL\n");
		return -ENOMEM;
	}

	ret = request_firmware(&fw, "dabusb/bitstream.bin", &s->usbdev->dev);
	if (ret) {
		dev_err(&s->usbdev->dev,
			"Failed to load \"dabusb/bitstream.bin\": %d\n", ret);
		kfree(b);
		return ret;
	}

	b->pipe = 1;
	ret = dabusb_fpga_clear (s, b);
	mdelay (10);
	blen = fw->data[73] + (fw->data[72] << 8);

	dbg("Bitstream len: %i", blen);

	b->data[0] = 0x2b;
	b->data[1] = 0;
	b->data[2] = 0;
	b->data[3] = 60;

	for (n = 0; n <= blen + 60; n += 60) {
		// some cclks for startup
		b->size = 64;
		memcpy (b->data + 4, fw->data + 74 + n, 60);
		ret = dabusb_bulk (s, b);
		if (ret < 0) {
			dev_err(&s->usbdev->dev, "dabusb_bulk failed.\n");
			break;
		}
		mdelay (1);
	}

	ret = dabusb_fpga_init (s, b);
	kfree (b);
	release_firmware(fw);

	dbg("exit dabusb_fpga_download");

	return ret;
}