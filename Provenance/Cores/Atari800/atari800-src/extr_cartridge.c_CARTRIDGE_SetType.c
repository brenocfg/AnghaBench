#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int type; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
 int CARTRIDGE_NONE ; 
 int /*<<< orphan*/  InitCartridge (TYPE_1__*) ; 
 int /*<<< orphan*/  RemoveCart (TYPE_1__*) ; 

void CARTRIDGE_SetType(CARTRIDGE_image_t *cart, int type)
{
	cart->type = type;
	if (type == CARTRIDGE_NONE)
		/* User cancelled setting the cartridge's type - the cartridge
		   can be unloaded. */
		RemoveCart(cart);
	InitCartridge(cart);
}