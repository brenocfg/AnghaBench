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
typedef  int /*<<< orphan*/  hda_nid_t ;

/* Variables and functions */

__attribute__((used)) static void reorder_outputs(unsigned int nums, hda_nid_t *pins)
{
	hda_nid_t nid;

	switch (nums) {
	case 3:
	case 4:
		nid = pins[1];
		pins[1] = pins[2];
		pins[2] = nid;
		break;
	}
}