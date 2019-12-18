#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ type; int /*<<< orphan*/ * image; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
 scalar_t__ CARTRIDGE_NONE ; 
 int /*<<< orphan*/  MapActiveCart () ; 
 TYPE_1__* active_cart ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void RemoveCart(CARTRIDGE_image_t *cart)
{
	if (cart->image != NULL) {
		free(cart->image);
		cart->image = NULL;
	}
	if (cart->type != CARTRIDGE_NONE) {
		cart->type = CARTRIDGE_NONE;
		if (cart == active_cart)
			MapActiveCart();
	}
}