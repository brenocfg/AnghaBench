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
struct TYPE_2__ {scalar_t__ BasePort1; } ;
struct pcmcia_device {TYPE_1__ io; int /*<<< orphan*/  dev; } ;
struct firmware {int size; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIRMWARE_NAME ; 
 int /*<<< orphan*/  outb (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_firmware (struct firmware const*) ; 
 int request_firmware (struct firmware const**,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static int osi_load_firmware(struct pcmcia_device *link)
{
	const struct firmware *fw;
	int i, err;

	err = request_firmware(&fw, FIRMWARE_NAME, &link->dev);
	if (err) {
		pr_err("Failed to load firmware \"%s\"\n", FIRMWARE_NAME);
		return err;
	}

	/* Download the Seven of Diamonds firmware */
	for (i = 0; i < fw->size; i++) {
	    outb(fw->data[i], link->io.BasePort1 + 2);
	    udelay(50);
	}
	release_firmware(fw);
	return err;
}