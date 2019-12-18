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
struct pcc_acpi {int* keymap; int /*<<< orphan*/  device; int /*<<< orphan*/  handle; struct input_dev* input_dev; } ;
struct input_dev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ERROR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_SUCCESS (int) ; 
 int ARRAY_SIZE (int*) ; 
 int FALSE ; 
 int /*<<< orphan*/  HKEY_NOTIFY ; 
 int KEY_RESERVED ; 
 int /*<<< orphan*/  METHOD_HKEY_QUERY ; 
 int TRUE ; 
 int /*<<< orphan*/  acpi_bus_generate_proc_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned long long) ; 
 int acpi_evaluate_integer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,unsigned long long*) ; 
 int /*<<< orphan*/  input_report_key (struct input_dev*,int,int) ; 
 int /*<<< orphan*/  input_sync (struct input_dev*) ; 

__attribute__((used)) static void acpi_pcc_generate_keyinput(struct pcc_acpi *pcc)
{
	struct input_dev *hotk_input_dev = pcc->input_dev;
	int rc;
	int key_code, hkey_num;
	unsigned long long result;

	rc = acpi_evaluate_integer(pcc->handle, METHOD_HKEY_QUERY,
				   NULL, &result);
	if (!ACPI_SUCCESS(rc)) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
				 "error getting hotkey status\n"));
		return;
	}

	acpi_bus_generate_proc_event(pcc->device, HKEY_NOTIFY, result);

	hkey_num = result & 0xf;

	if (hkey_num < 0 || hkey_num >= ARRAY_SIZE(pcc->keymap)) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
				  "hotkey number out of range: %d\n",
				  hkey_num));
		return;
	}

	key_code = pcc->keymap[hkey_num];

	if (key_code != KEY_RESERVED) {
		int pushed = (result & 0x80) ? TRUE : FALSE;

		input_report_key(hotk_input_dev, key_code, pushed);
		input_sync(hotk_input_dev);
	}

	return;
}