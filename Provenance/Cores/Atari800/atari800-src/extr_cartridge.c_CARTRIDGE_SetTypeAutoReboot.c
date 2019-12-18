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
typedef  int /*<<< orphan*/  CARTRIDGE_image_t ;

/* Variables and functions */
 int /*<<< orphan*/  AutoReboot () ; 
 int /*<<< orphan*/  CARTRIDGE_SetType (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  CARTRIDGE_piggyback ; 

void CARTRIDGE_SetTypeAutoReboot(CARTRIDGE_image_t *cart, int type)
{
	CARTRIDGE_SetType(cart, type);
	/* We don't want to autoreboot on inserting the piggyback cartridge. */
	if (cart != &CARTRIDGE_piggyback)
		AutoReboot();
}