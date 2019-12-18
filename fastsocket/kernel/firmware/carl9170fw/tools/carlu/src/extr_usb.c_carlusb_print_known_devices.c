#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  idProduct; int /*<<< orphan*/  idVendor; int /*<<< orphan*/  product_name; int /*<<< orphan*/  vendor_name; } ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (TYPE_1__*) ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  debug_level ; 
 TYPE_1__* dev_list ; 
 int /*<<< orphan*/  info (char*,...) ; 

int carlusb_print_known_devices(void)
{
	unsigned int i;

	debug_level = INFO;

	info("==> dumping known device list <==\n");
	for (i = 0; i < ARRAY_SIZE(dev_list); i++) {
		info("Vendor:\"%-9s\" Product:\"%-26s\" => USBID:[0x%04x:0x%04x]\n",
		     dev_list[i].vendor_name, dev_list[i].product_name,
		     dev_list[i].idVendor, dev_list[i].idProduct);
	}
	info("==> end of device list <==\n");

	return EXIT_SUCCESS;
}