#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int UWORD ;
typedef  int UBYTE ;
struct TYPE_6__ {int state; int type; int* image; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
#define  CARTRIDGE_AST_32 135 
#define  CARTRIDGE_MEGA_4096 134 
 int CARTRIDGE_NONE ; 
#define  CARTRIDGE_SIC_128 133 
#define  CARTRIDGE_SIC_256 132 
#define  CARTRIDGE_SIC_512 131 
#define  CARTRIDGE_THECART_128M 130 
#define  CARTRIDGE_THECART_32M 129 
#define  CARTRIDGE_THECART_64M 128 
 TYPE_1__ CARTRIDGE_piggyback ; 
 int /*<<< orphan*/  Log_print (char*,int,int) ; 
 int /*<<< orphan*/  SwitchBank (int) ; 
 scalar_t__ access_D5 (TYPE_1__*,int,int*) ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static UBYTE GetByte(CARTRIDGE_image_t *cart, UWORD addr, int no_side_effects)
{
	int old_state = cart->state;
	int new_state = old_state;

#if DEBUG
	if (cart->type > CARTRIDGE_NONE)
		Log_print("Cart %i read: %04x", cart == &CARTRIDGE_piggyback, addr);
#endif
	/* Set the cartridge's new state. */
	/* Check types switchable by access to page D5. */
	if (!no_side_effects && access_D5(cart, addr, &new_state)) {
		/* Cartridge supports bankswitching and reacted to the given
		   ADDR. If the state changed, we need to do the bankswitch. */
		if (new_state != old_state) {
			cart->state = new_state;
			if (cart == active_cart)
				SwitchBank(old_state);
		}
	}

	/* Determine returned byte value. */
	switch (cart->type) {
	case CARTRIDGE_AST_32:
		/* cart->state contains address of current bank, therefore it
		   divides by 0x100. */
		return cart->image[(cart->state & 0xff00) | (addr & 0xff)];
	case CARTRIDGE_SIC_512:
	case CARTRIDGE_SIC_256:
	case CARTRIDGE_SIC_128:
	case CARTRIDGE_MEGA_4096:
		/* Only react to access to $D50x/$D51x. */
		if ((addr & 0xe0) == 0x00)
			return cart->state;
		break;
	case CARTRIDGE_THECART_128M:
	case CARTRIDGE_THECART_32M:
	case CARTRIDGE_THECART_64M:
		switch (addr) {
		case 0xd5a0:
			return cart->state & 0x00ff;
		case 0xd5a1:
			return (cart->state & 0x3f00) >> 8;
		case 0xd5a2:
			return (~cart->state & 0x4000) >> 14;
		}
		break;
	}
	return 0xff;
}