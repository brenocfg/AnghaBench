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
struct pcc_acpi {int* keymap; } ;

/* Variables and functions */
 int ARRAY_SIZE (int*) ; 

__attribute__((used)) static int keymap_get_by_keycode(struct pcc_acpi *pcc, int keycode)
{
	int i;

	for (i = 0; i < ARRAY_SIZE(pcc->keymap); i++) {
		if (pcc->keymap[i] == keycode)
			return i+1;
	}

	return 0;
}