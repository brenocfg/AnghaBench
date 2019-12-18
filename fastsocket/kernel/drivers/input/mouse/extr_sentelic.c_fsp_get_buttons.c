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
struct psmouse {int dummy; } ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  FSP_REG_TMOD_STATUS1 ; 
 int fsp_reg_read (struct psmouse*,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int fsp_get_buttons(struct psmouse *psmouse, int *btn)
{
	static const int buttons[] = {
		0x16, /* Left/Middle/Right/Forward/Backward & Scroll Up/Down */
		0x06, /* Left/Middle/Right & Scroll Up/Down/Right/Left */
		0x04, /* Left/Middle/Right & Scroll Up/Down */
		0x02, /* Left/Middle/Right */
	};
	int val;

	if (fsp_reg_read(psmouse, FSP_REG_TMOD_STATUS1, &val) == -1)
		return -EIO;

	*btn = buttons[(val & 0x30) >> 4];
	return 0;
}