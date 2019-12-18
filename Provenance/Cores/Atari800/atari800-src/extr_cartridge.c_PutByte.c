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
struct TYPE_6__ {int state; int type; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
#define  CARTRIDGE_AST_32 157 
#define  CARTRIDGE_ATRAX_128 156 
#define  CARTRIDGE_MEGA_1024 155 
#define  CARTRIDGE_MEGA_128 154 
#define  CARTRIDGE_MEGA_16 153 
#define  CARTRIDGE_MEGA_2048 152 
#define  CARTRIDGE_MEGA_256 151 
#define  CARTRIDGE_MEGA_32 150 
#define  CARTRIDGE_MEGA_4096 149 
#define  CARTRIDGE_MEGA_512 148 
#define  CARTRIDGE_MEGA_64 147 
 int CARTRIDGE_NONE ; 
#define  CARTRIDGE_SIC_128 146 
#define  CARTRIDGE_SIC_256 145 
#define  CARTRIDGE_SIC_512 144 
#define  CARTRIDGE_SWXEGS_1024 143 
#define  CARTRIDGE_SWXEGS_128 142 
#define  CARTRIDGE_SWXEGS_256 141 
#define  CARTRIDGE_SWXEGS_32 140 
#define  CARTRIDGE_SWXEGS_512 139 
#define  CARTRIDGE_SWXEGS_64 138 
#define  CARTRIDGE_THECART_128M 137 
#define  CARTRIDGE_THECART_32M 136 
#define  CARTRIDGE_THECART_64M 135 
#define  CARTRIDGE_XEGS_07_64 134 
#define  CARTRIDGE_XEGS_1024 133 
#define  CARTRIDGE_XEGS_128 132 
#define  CARTRIDGE_XEGS_256 131 
#define  CARTRIDGE_XEGS_32 130 
#define  CARTRIDGE_XEGS_512 129 
#define  CARTRIDGE_XEGS_8F_64 128 
 TYPE_1__ CARTRIDGE_piggyback ; 
 int /*<<< orphan*/  Log_print (char*,int,int,int) ; 
 int /*<<< orphan*/  SwitchBank (int) ; 
 int /*<<< orphan*/  access_D5 (TYPE_1__*,int,int*) ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static void PutByte(CARTRIDGE_image_t *cart, UWORD addr, UBYTE byte)
{
	int old_state = cart->state;
	int new_state = old_state;

#if DEBUG
	if (cart->type > CARTRIDGE_NONE)
		Log_print("Cart %i write: %04x, %02x", cart == &CARTRIDGE_piggyback, addr, byte);
#endif
	/* Set the cartridge's new state. */
	switch (cart->type) {
	case CARTRIDGE_XEGS_32:
		new_state = byte & 0x03;
		break;
	case CARTRIDGE_XEGS_07_64:
		new_state = byte & 0x07;
		break;
	case CARTRIDGE_XEGS_128:
	case CARTRIDGE_XEGS_8F_64:
		new_state = byte & 0x0f;
		break;
	case CARTRIDGE_XEGS_256:
		new_state = byte & 0x1f;
		break;
	case CARTRIDGE_XEGS_512:
		new_state = byte & 0x3f;
		break;
	case CARTRIDGE_XEGS_1024:
		new_state = byte & 0x7f;
		break;
	case CARTRIDGE_MEGA_16:
		new_state = byte & 0x80;
		break;
	case CARTRIDGE_MEGA_32:
		new_state = byte & 0x81;
		break;
	case CARTRIDGE_MEGA_64:
	case CARTRIDGE_SWXEGS_32:
		new_state = byte & 0x83;
		break;
	case CARTRIDGE_MEGA_128:
	case CARTRIDGE_SWXEGS_64:
		new_state = byte & 0x87;
		break;
	case CARTRIDGE_MEGA_256:
	case CARTRIDGE_SWXEGS_128:
	case CARTRIDGE_ATRAX_128:
		new_state = byte & 0x8f;
		break;
	case CARTRIDGE_MEGA_512:
	case CARTRIDGE_SWXEGS_256:
		new_state = byte & 0x9f;
		break;
	case CARTRIDGE_MEGA_1024:
	case CARTRIDGE_SWXEGS_512:
		new_state = byte & 0xbf;
		break;
	case CARTRIDGE_MEGA_2048:
	case CARTRIDGE_SWXEGS_1024:
		new_state = byte;
		break;
	case CARTRIDGE_AST_32:
		/* State contains address of current bank. */
		new_state = (old_state + 0x100) & 0x7fff;
		break;
	case CARTRIDGE_SIC_512:
	case CARTRIDGE_SIC_256:
	case CARTRIDGE_SIC_128:
	case CARTRIDGE_MEGA_4096:
		/* Only react to access to $D50x/$D51x. */
		if ((addr & 0xe0) == 0x00)
			new_state = byte;
		break;
	case CARTRIDGE_THECART_128M:
	case CARTRIDGE_THECART_32M:
	case CARTRIDGE_THECART_64M:
		switch (addr) {
		case 0xd5a0:
			new_state = (old_state & 0x3f00) | byte;
			break;
		case 0xd5a1:
			new_state = (old_state & 0x00ff) | ((byte & 0x3f) << 8);
			break;
		case 0xd5a2:
			new_state = (old_state & 0x3fff) | ((~byte & 0x01) << 14);
			break;
		}
		break;
	default:
		/* Check types switchable by access to page D5. */
		if (!access_D5(cart, addr, &new_state))
			/* Cartridge doesn't support bankswitching, or didn't react to
			   the given ADDR. */
			return;
	}

	/* If the state changed, we need to do the bankswitch. */
	if (new_state != old_state) {
		cart->state = new_state;
		if (cart == active_cart)
			SwitchBank(old_state);
	}
}