#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct pcc_acpi {TYPE_2__* input_dev; int /*<<< orphan*/ * keymap; } ;
struct TYPE_6__ {int vendor; int product; int version; int /*<<< orphan*/  bustype; } ;
struct TYPE_7__ {int /*<<< orphan*/  keybit; int /*<<< orphan*/  setkeycode; int /*<<< orphan*/  getkeycode; TYPE_1__ id; int /*<<< orphan*/  phys; int /*<<< orphan*/  name; int /*<<< orphan*/ * evbit; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACPI_DB_ERROR ; 
 int /*<<< orphan*/  ACPI_DEBUG_PRINT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ACPI_PCC_DRIVER_NAME ; 
 int /*<<< orphan*/  ACPI_PCC_INPUT_PHYS ; 
 int ARRAY_SIZE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BIT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BUS_HOST ; 
 int ENOMEM ; 
 int /*<<< orphan*/  EV_KEY ; 
 int /*<<< orphan*/  KEY_RESERVED ; 
 int /*<<< orphan*/  __clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  initial_keymap ; 
 TYPE_2__* input_allocate_device () ; 
 int /*<<< orphan*/  input_free_device (TYPE_2__*) ; 
 int input_register_device (TYPE_2__*) ; 
 int /*<<< orphan*/  input_set_drvdata (TYPE_2__*,struct pcc_acpi*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  pcc_getkeycode ; 
 int /*<<< orphan*/  pcc_setkeycode ; 

__attribute__((used)) static int acpi_pcc_init_input(struct pcc_acpi *pcc)
{
	int i, rc;

	pcc->input_dev = input_allocate_device();
	if (!pcc->input_dev) {
		ACPI_DEBUG_PRINT((ACPI_DB_ERROR,
				  "Couldn't allocate input device for hotkey"));
		return -ENOMEM;
	}

	pcc->input_dev->evbit[0] = BIT(EV_KEY);

	pcc->input_dev->name = ACPI_PCC_DRIVER_NAME;
	pcc->input_dev->phys = ACPI_PCC_INPUT_PHYS;
	pcc->input_dev->id.bustype = BUS_HOST;
	pcc->input_dev->id.vendor = 0x0001;
	pcc->input_dev->id.product = 0x0001;
	pcc->input_dev->id.version = 0x0100;
	pcc->input_dev->getkeycode = pcc_getkeycode;
	pcc->input_dev->setkeycode = pcc_setkeycode;

	/* load initial keymap */
	memcpy(pcc->keymap, initial_keymap, sizeof(pcc->keymap));

	for (i = 0; i < ARRAY_SIZE(pcc->keymap); i++)
		__set_bit(pcc->keymap[i], pcc->input_dev->keybit);
	__clear_bit(KEY_RESERVED, pcc->input_dev->keybit);

	input_set_drvdata(pcc->input_dev, pcc);

	rc = input_register_device(pcc->input_dev);
	if (rc < 0)
		input_free_device(pcc->input_dev);

	return rc;
}