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
struct fw_unit {int /*<<< orphan*/ * directory; } ;
struct fw_device {int /*<<< orphan*/ * config_rom; } ;
struct fw_csr_iterator {int dummy; } ;

/* Variables and functions */
#define  CSR_MODEL 131 
#define  CSR_SPECIFIER_ID 130 
#define  CSR_VENDOR 129 
#define  CSR_VERSION 128 
 int /*<<< orphan*/  fw_csr_iterator_init (struct fw_csr_iterator*,int /*<<< orphan*/ *) ; 
 scalar_t__ fw_csr_iterator_next (struct fw_csr_iterator*,int*,int*) ; 
 struct fw_device* fw_parent_device (struct fw_unit*) ; 
 int snprintf (char*,size_t,char*,int,int,int,int) ; 

__attribute__((used)) static int get_modalias(struct fw_unit *unit, char *buffer, size_t buffer_size)
{
	struct fw_device *device = fw_parent_device(unit);
	struct fw_csr_iterator ci;

	int key, value;
	int vendor = 0;
	int model = 0;
	int specifier_id = 0;
	int version = 0;

	fw_csr_iterator_init(&ci, &device->config_rom[5]);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		switch (key) {
		case CSR_VENDOR:
			vendor = value;
			break;
		case CSR_MODEL:
			model = value;
			break;
		}
	}

	fw_csr_iterator_init(&ci, unit->directory);
	while (fw_csr_iterator_next(&ci, &key, &value)) {
		switch (key) {
		case CSR_SPECIFIER_ID:
			specifier_id = value;
			break;
		case CSR_VERSION:
			version = value;
			break;
		}
	}

	return snprintf(buffer, buffer_size,
			"ieee1394:ven%08Xmo%08Xsp%08Xver%08X",
			vendor, model, specifier_id, version);
}