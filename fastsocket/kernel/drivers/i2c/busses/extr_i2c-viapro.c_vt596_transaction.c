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
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EIO ; 
 int ENXIO ; 
 int ETIMEDOUT ; 
 int MAX_TIMEOUT ; 
 int /*<<< orphan*/  SMBHSTADD ; 
 int /*<<< orphan*/  SMBHSTCNT ; 
 int /*<<< orphan*/  SMBHSTSTS ; 
 int VT596_BYTE ; 
 int VT596_QUICK ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,...) ; 
 int inb_p (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  outb_p (int,int /*<<< orphan*/ ) ; 
 TYPE_1__ vt596_adapter ; 
 int /*<<< orphan*/  vt596_dump_regs (char*,int) ; 

__attribute__((used)) static int vt596_transaction(u8 size)
{
	int temp;
	int result = 0;
	int timeout = 0;

	vt596_dump_regs("Transaction (pre)", size);

	/* Make sure the SMBus host is ready to start transmitting */
	if ((temp = inb_p(SMBHSTSTS)) & 0x1F) {
		dev_dbg(&vt596_adapter.dev, "SMBus busy (0x%02x). "
			"Resetting...\n", temp);

		outb_p(temp, SMBHSTSTS);
		if ((temp = inb_p(SMBHSTSTS)) & 0x1F) {
			dev_err(&vt596_adapter.dev, "SMBus reset failed! "
				"(0x%02x)\n", temp);
			return -EBUSY;
		}
	}

	/* Start the transaction by setting bit 6 */
	outb_p(0x40 | size, SMBHSTCNT);

	/* We will always wait for a fraction of a second */
	do {
		msleep(1);
		temp = inb_p(SMBHSTSTS);
	} while ((temp & 0x01) && (timeout++ < MAX_TIMEOUT));

	/* If the SMBus is still busy, we give up */
	if (timeout >= MAX_TIMEOUT) {
		result = -ETIMEDOUT;
		dev_err(&vt596_adapter.dev, "SMBus timeout!\n");
	}

	if (temp & 0x10) {
		result = -EIO;
		dev_err(&vt596_adapter.dev, "Transaction failed (0x%02x)\n",
			size);
	}

	if (temp & 0x08) {
		result = -EIO;
		dev_err(&vt596_adapter.dev, "SMBus collision!\n");
	}

	if (temp & 0x04) {
		int read = inb_p(SMBHSTADD) & 0x01;
		result = -ENXIO;
		/* The quick and receive byte commands are used to probe
		   for chips, so errors are expected, and we don't want
		   to frighten the user. */
		if (!((size == VT596_QUICK && !read) ||
		      (size == VT596_BYTE && read)))
			dev_err(&vt596_adapter.dev, "Transaction error!\n");
	}

	/* Resetting status register */
	if (temp & 0x1F)
		outb_p(temp, SMBHSTSTS);

	vt596_dump_regs("Transaction (post)", size);

	return result;
}