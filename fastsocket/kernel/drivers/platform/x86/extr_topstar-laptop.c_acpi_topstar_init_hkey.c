#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tps_key_entry {int /*<<< orphan*/  keycode; scalar_t__ code; } ;
struct topstar_hkey {TYPE_2__* inputdev; } ;
struct TYPE_5__ {int /*<<< orphan*/  bustype; } ;
struct TYPE_6__ {char* name; char* phys; int /*<<< orphan*/  keybit; int /*<<< orphan*/  evbit; int /*<<< orphan*/  setkeycode; int /*<<< orphan*/  getkeycode; TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUS_HOST ; 
 int ENODEV ; 
 int /*<<< orphan*/  EV_KEY ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 scalar_t__ input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  topstar_getkeycode ; 
 struct tps_key_entry* topstar_keymap ; 
 int /*<<< orphan*/  topstar_setkeycode ; 

__attribute__((used)) static int acpi_topstar_init_hkey(struct topstar_hkey *hkey)
{
	struct tps_key_entry *key;

	hkey->inputdev = input_allocate_device();
	if (!hkey->inputdev) {
		pr_err("Unable to allocate input device\n");
		return -ENODEV;
	}
	hkey->inputdev->name = "Topstar Laptop extra buttons";
	hkey->inputdev->phys = "topstar/input0";
	hkey->inputdev->id.bustype = BUS_HOST;
	hkey->inputdev->getkeycode = topstar_getkeycode;
	hkey->inputdev->setkeycode = topstar_setkeycode;
	for (key = topstar_keymap; key->code; key++) {
		set_bit(EV_KEY, hkey->inputdev->evbit);
		set_bit(key->keycode, hkey->inputdev->keybit);
	}
	if (input_register_device(hkey->inputdev)) {
		pr_err("Unable to register input device\n");
		input_free_device(hkey->inputdev);
		return -ENODEV;
	}

	return 0;
}