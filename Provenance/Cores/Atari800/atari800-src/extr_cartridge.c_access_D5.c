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
struct TYPE_6__ {int state; int type; } ;
typedef  TYPE_1__ CARTRIDGE_image_t ;

/* Variables and functions */
#define  CARTRIDGE_ATMAX_1024 150 
#define  CARTRIDGE_ATMAX_128 149 
#define  CARTRIDGE_ATRAX_SDX_128 148 
#define  CARTRIDGE_ATRAX_SDX_64 147 
#define  CARTRIDGE_BLIZZARD_16 146 
#define  CARTRIDGE_BLIZZARD_32 145 
#define  CARTRIDGE_BLIZZARD_4 144 
#define  CARTRIDGE_DB_32 143 
#define  CARTRIDGE_DIAMOND_64 142 
#define  CARTRIDGE_EXP_64 141 
#define  CARTRIDGE_MEGAMAX_2048 140 
#define  CARTRIDGE_OSS_034M_16 139 
#define  CARTRIDGE_OSS_043M_16 138 
#define  CARTRIDGE_OSS_8 137 
#define  CARTRIDGE_OSS_M091_16 136 
#define  CARTRIDGE_PHOENIX_8 135 
#define  CARTRIDGE_SDX_128 134 
#define  CARTRIDGE_SDX_64 133 
#define  CARTRIDGE_TURBOSOFT_128 132 
#define  CARTRIDGE_TURBOSOFT_64 131 
#define  CARTRIDGE_ULTRACART_32 130 
#define  CARTRIDGE_WILL_32 129 
#define  CARTRIDGE_WILL_64 128 
 TYPE_1__ CARTRIDGE_main ; 
 TYPE_1__ CARTRIDGE_piggyback ; 
 int FALSE ; 
 int /*<<< orphan*/  MapActiveCart () ; 
 int TRUE ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static int access_D5(CARTRIDGE_image_t *cart, UWORD addr, int *state)
{
	int old_state = cart->state;
	int new_state;

	switch (cart->type) {
	case CARTRIDGE_OSS_034M_16:
		/* Reference: http://www.retrobits.net/atari/osscarts.shtml
		   Deprecated by CARTRIDGE_OSS_043M_16 - 034M is an incorrect
		   bank order (a real cartridge consists of two 8KB chips,
		   one containing banks 0 and 4, the other 3 and M). Kept here
		   for backward compatibility. */
		   
		if (addr & 0x08)
			new_state = -1;
		else
			switch (addr & 0x07) {
			case 0x00:
				/* B Lo/A Hi */
				new_state = 0;
				break;
			case 0x01:
				/* A Lo+B Lo/A Hi */
				/* TODO should be binary AND of both banks. For now only fills with 0xFFs. */
				new_state = 0xff;
				break;
			case 0x03:
			case 0x07:
				/* A Lo/A Hi */
				new_state = 1;
				break;
			case 0x04:
				/* B Hi/A Hi */
				new_state = 2;
				break;
			case 0x05:
				/* A Lo+B Hi/A Hi */
				/* TODO should be binary AND of both banks. For now only fills with 0xFFs. */
				new_state = 0xff;
				break;
			default: /* 0x02, 0x06 */
				/* Fill cart area with 0xFFs. */
				new_state = 0xff;
				break;
			}
		break;
	case CARTRIDGE_OSS_043M_16:
		/* Reference: http://www.retrobits.net/atari/osscarts.shtml
		   Using the nomenclature of the above article: the emulator
		   accepts 16KB images composed of two 8KB EPROM dumps joined
		   together in the following order: ROM B, ROM A. Currently
		   only three cartridges with this scheme are known:
		   Action! 3.5, BASIC XL 1.02 and MAC/65 1.0. */
		   
		if (addr & 0x08)
			new_state = -1;
		else
			switch (addr & 0x07) {
			case 0x00:
				/* B Lo/A Hi */
				new_state = 0;
				break;
			case 0x01:
				/* A Lo+B Lo/A Hi */
				/* TODO should be binary AND of both banks. For now only fills with 0xFFs. */
				new_state = 0xff;
				break;
			case 0x03:
			case 0x07:
				/* A Lo/A Hi */
				new_state = 2;
				break;
			case 0x04:
				/* B Hi/A Hi */
				new_state = 1;
				break;
			case 0x05:
				/* A Lo+B Hi/A Hi */
				/* TODO should be binary AND of both banks. For now only fills with 0xFFs. */
				new_state = 0xff;
				break;
			default: /* 0x02, 0x06 */
				/* Fill cart area with 0xFFs. */
				new_state = 0xff;
				break;
			}
		break;
	case CARTRIDGE_DB_32:
		new_state = addr & 0x03;
		break;
	case CARTRIDGE_WILL_64:
		new_state = addr & 0x0f;
		break;
	case CARTRIDGE_WILL_32:
		new_state = addr & 0x0b;
		break;
	case CARTRIDGE_EXP_64:
		/* Only react to access to $D57x. */
		if ((addr & 0xf0) != 0x70)
			return FALSE;
		new_state = ((addr ^ 7) & 0x0f);
		break;
	case CARTRIDGE_DIAMOND_64:
		/* Only react to access to $D5Dx. */
		if ((addr & 0xf0) != 0xd0)
			return FALSE;
		new_state = ((addr ^ 7) & 0x0f);
		break;
	case CARTRIDGE_SDX_64:
	case CARTRIDGE_ATRAX_SDX_64:
		/* Only react to access to $D5Ex. */
		if ((addr & 0xf0) != 0xe0)
			return FALSE;
		if (addr & 0x08)
			new_state = addr & 0x0c;
		else
			/* Negate bits that encode bank number. */
			new_state = ((addr ^ 0x07) & 0x0f);
		if (cart == &CARTRIDGE_main) {
			/* It's the 1st cartridge, process switching the piggyback on/off. */
			if ((old_state & 0x0c) == 0x08) { /* Piggyback cartridge was enabled */
				if ((new_state & 0x0c) != 0x08)  { /* Going to disable it */
					active_cart = &CARTRIDGE_main;
					MapActiveCart();
				}
			}
			else if ((new_state & 0x0c) == 0x08) { /* Going to enable piggyback */
				active_cart = &CARTRIDGE_piggyback;
				MapActiveCart();
			}
		}
		break;
	case CARTRIDGE_SDX_128:
	case CARTRIDGE_ATRAX_SDX_128:
		/* Only react to access to $D5Ex/$D5Fx. */
		if ((addr & 0xe0) != 0xe0)
			return FALSE;
		if (addr & 0x08)
			new_state = addr & 0x0c;
		else
			/* Negate bits that encode bank number. */
			new_state = ((addr ^ 0x17) & 0x1f);
		if (cart == &CARTRIDGE_main) {
			/* It's the 1st cartridge, process switching the piggyback on/off. */
			if ((old_state & 0x0c) == 0x08) { /* Piggyback cartridge was enabled */
				if ((new_state & 0x0c) != 0x08)  { /* Going to disable it */
					active_cart = &CARTRIDGE_main;
					MapActiveCart();
				}
			}
			else if ((new_state & 0x0c) == 0x08) { /* Going to enable piggyback */
				active_cart = &CARTRIDGE_piggyback;
				MapActiveCart();
			}
		}
		break;
	case CARTRIDGE_OSS_M091_16:
		switch (addr & 0x09) {
		case 0x00:
			new_state = 1;
			break;
		case 0x01:
			new_state = 3;
			break;
		case 0x08:
			new_state = -1;
			break;
		default: /* 0x09 */
			new_state = 2;
			break;
		}
		break;
	case CARTRIDGE_BLIZZARD_4:
	case CARTRIDGE_PHOENIX_8:
	case CARTRIDGE_BLIZZARD_16:
		/* Disable the cart. */
		new_state = 1;
		break;
	case CARTRIDGE_ATMAX_128:
		/* Only react to access to $D50x/$D51x. */
		if ((addr & 0xe0) != 0)
			return FALSE;
		/* fall through */
	case CARTRIDGE_TURBOSOFT_128:
		new_state = addr & 0x1f;
		break;
	case CARTRIDGE_TURBOSOFT_64:
		new_state = addr & 0x17;
		break;
	case CARTRIDGE_ATMAX_1024:
	case CARTRIDGE_MEGAMAX_2048:
		new_state = addr;
		break;
	case CARTRIDGE_OSS_8:
		switch (addr & 0x09) {
		case 0x00:
		case 0x01:
			new_state = 1;
			break;
		case 0x08:
			new_state = -1;
			break;
		default: /* 0x09 */
			new_state = 0;
			break;
		}
		break;
	case CARTRIDGE_ULTRACART_32:
		new_state = (old_state + 1) % 5;
		break;
	case CARTRIDGE_BLIZZARD_32:
		if (old_state < 4)
			new_state = old_state + 1;
		break;
	default:
		/* Other cartridge types don't support enabling/disabling/banking through page D5. */
		return FALSE;
	}
	*state = new_state;
	return TRUE;
}