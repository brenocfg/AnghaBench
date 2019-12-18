#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int type; int state; int /*<<< orphan*/  image; } ;

/* Variables and functions */
 scalar_t__ Atari800_MACHINE_5200 ; 
 scalar_t__ Atari800_MACHINE_800 ; 
 int /*<<< orphan*/  Atari800_builtin_basic ; 
 int /*<<< orphan*/  Atari800_disable_basic ; 
 scalar_t__ Atari800_machine_type ; 
 int /*<<< orphan*/  BINLOAD_loading_basic ; 
#define  CARTRIDGE_5200_32 194 
#define  CARTRIDGE_5200_4 193 
#define  CARTRIDGE_5200_40 192 
#define  CARTRIDGE_5200_8 191 
#define  CARTRIDGE_5200_EE_16 190 
#define  CARTRIDGE_5200_NS_16 189 
#define  CARTRIDGE_AST_32 188 
#define  CARTRIDGE_ATMAX_1024 187 
#define  CARTRIDGE_ATMAX_128 186 
#define  CARTRIDGE_ATRAX_128 185 
#define  CARTRIDGE_ATRAX_SDX_128 184 
#define  CARTRIDGE_ATRAX_SDX_64 183 
#define  CARTRIDGE_BBSB_40 182 
#define  CARTRIDGE_BLIZZARD_16 181 
#define  CARTRIDGE_BLIZZARD_32 180 
#define  CARTRIDGE_BLIZZARD_4 179 
 int /*<<< orphan*/  CARTRIDGE_BountyBob1GetByte ; 
 int /*<<< orphan*/  CARTRIDGE_BountyBob1PutByte ; 
 int /*<<< orphan*/  CARTRIDGE_BountyBob2GetByte ; 
 int /*<<< orphan*/  CARTRIDGE_BountyBob2PutByte ; 
#define  CARTRIDGE_DB_32 178 
#define  CARTRIDGE_DIAMOND_64 177 
#define  CARTRIDGE_EXP_64 176 
#define  CARTRIDGE_LOW_BANK_8 175 
#define  CARTRIDGE_MEGAMAX_2048 174 
#define  CARTRIDGE_MEGA_1024 173 
#define  CARTRIDGE_MEGA_128 172 
#define  CARTRIDGE_MEGA_16 171 
#define  CARTRIDGE_MEGA_2048 170 
#define  CARTRIDGE_MEGA_256 169 
#define  CARTRIDGE_MEGA_32 168 
#define  CARTRIDGE_MEGA_4096 167 
#define  CARTRIDGE_MEGA_512 166 
#define  CARTRIDGE_MEGA_64 165 
#define  CARTRIDGE_OSS_034M_16 164 
#define  CARTRIDGE_OSS_043M_16 163 
#define  CARTRIDGE_OSS_8 162 
#define  CARTRIDGE_OSS_M091_16 161 
#define  CARTRIDGE_PHOENIX_8 160 
#define  CARTRIDGE_RIGHT_4 159 
#define  CARTRIDGE_RIGHT_8 158 
#define  CARTRIDGE_SDX_128 157 
#define  CARTRIDGE_SDX_64 156 
#define  CARTRIDGE_SIC_128 155 
#define  CARTRIDGE_SIC_256 154 
#define  CARTRIDGE_SIC_512 153 
#define  CARTRIDGE_STD_16 152 
#define  CARTRIDGE_STD_2 151 
#define  CARTRIDGE_STD_4 150 
#define  CARTRIDGE_STD_8 149 
#define  CARTRIDGE_SWXEGS_1024 148 
#define  CARTRIDGE_SWXEGS_128 147 
#define  CARTRIDGE_SWXEGS_256 146 
#define  CARTRIDGE_SWXEGS_32 145 
#define  CARTRIDGE_SWXEGS_512 144 
#define  CARTRIDGE_SWXEGS_64 143 
#define  CARTRIDGE_THECART_128M 142 
#define  CARTRIDGE_THECART_32M 141 
#define  CARTRIDGE_THECART_64M 140 
#define  CARTRIDGE_TURBOSOFT_128 139 
#define  CARTRIDGE_TURBOSOFT_64 138 
#define  CARTRIDGE_ULTRACART_32 137 
#define  CARTRIDGE_WILL_32 136 
#define  CARTRIDGE_WILL_64 135 
#define  CARTRIDGE_XEGS_07_64 134 
#define  CARTRIDGE_XEGS_1024 133 
#define  CARTRIDGE_XEGS_128 132 
#define  CARTRIDGE_XEGS_256 131 
#define  CARTRIDGE_XEGS_32 130 
#define  CARTRIDGE_XEGS_512 129 
#define  CARTRIDGE_XEGS_8F_64 128 
 int /*<<< orphan*/  MEMORY_Cart809fDisable () ; 
 int /*<<< orphan*/  MEMORY_Cart809fEnable () ; 
 int /*<<< orphan*/  MEMORY_CartA0bfDisable () ; 
 int /*<<< orphan*/  MEMORY_CartA0bfEnable () ; 
 int /*<<< orphan*/  MEMORY_CopyROM (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_SetHARDWARE (int,int) ; 
 int /*<<< orphan*/  MEMORY_SetROM (int,int) ; 
 int /*<<< orphan*/  MEMORY_basic ; 
 int /*<<< orphan*/  MEMORY_dFillMem (int,int,int) ; 
 int /*<<< orphan*/  MEMORY_have_basic ; 
 int /*<<< orphan*/ * MEMORY_readmap ; 
 int /*<<< orphan*/ * MEMORY_writemap ; 
 int /*<<< orphan*/  SwitchBank (int) ; 
 TYPE_1__* active_cart ; 

__attribute__((used)) static void MapActiveCart(void)
{
	if (Atari800_machine_type == Atari800_MACHINE_5200) {
		MEMORY_SetROM(0x4ff6, 0x4ff9);		/* disable Bounty Bob bank switching */
		MEMORY_SetROM(0x5ff6, 0x5ff9);
		switch (active_cart->type) {
		case CARTRIDGE_5200_32:
			MEMORY_CopyROM(0x4000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_5200_EE_16:
			MEMORY_CopyROM(0x4000, 0x5fff, active_cart->image);
			MEMORY_CopyROM(0x6000, 0x9fff, active_cart->image);
			MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x2000);
			break;
		case CARTRIDGE_5200_40:
			MEMORY_CopyROM(0x4000, 0x4fff, active_cart->image + (active_cart->state & 0x03) * 0x1000);
			MEMORY_CopyROM(0x5000, 0x5fff, active_cart->image + 0x4000 + ((active_cart->state & 0x0c) >> 2) * 0x1000);
			MEMORY_CopyROM(0x8000, 0x9fff, active_cart->image + 0x8000);
			MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x8000);
#ifndef PAGED_ATTRIB
			MEMORY_SetHARDWARE(0x4ff6, 0x4ff9);
			MEMORY_SetHARDWARE(0x5ff6, 0x5ff9);
#else
			MEMORY_readmap[0x4f] = CARTRIDGE_BountyBob1GetByte;
			MEMORY_readmap[0x5f] = CARTRIDGE_BountyBob2GetByte;
			MEMORY_writemap[0x4f] = CARTRIDGE_BountyBob1PutByte;
			MEMORY_writemap[0x5f] = CARTRIDGE_BountyBob2PutByte;
#endif
			break;
		case CARTRIDGE_5200_NS_16:
			MEMORY_CopyROM(0x8000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_5200_8:
			MEMORY_CopyROM(0x8000, 0x9fff, active_cart->image);
			MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_5200_4:
			MEMORY_CopyROM(0x8000, 0x8fff, active_cart->image);
			MEMORY_CopyROM(0x9000, 0x9fff, active_cart->image);
			MEMORY_CopyROM(0xa000, 0xafff, active_cart->image);
			MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image);
			break;
		default:
			/* clear cartridge area so the 5200 will crash */
			MEMORY_dFillMem(0x4000, 0, 0x8000);
			break;
		}
	}
	else {
		switch (active_cart->type) {
		case CARTRIDGE_STD_2:
			MEMORY_Cart809fDisable();
			MEMORY_CartA0bfEnable();
			MEMORY_dFillMem(0xa000, 0xff, 0x1800);
			MEMORY_CopyROM(0xb800, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_STD_4:
			MEMORY_Cart809fDisable();
			MEMORY_CartA0bfEnable();
			MEMORY_dFillMem(0xa000, 0xff, 0x1000);
			MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_BLIZZARD_4:
			MEMORY_Cart809fDisable();
			MEMORY_CartA0bfEnable();
			MEMORY_CopyROM(0xa000, 0xafff, active_cart->image);
			MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_STD_8:
		case CARTRIDGE_PHOENIX_8:
			MEMORY_Cart809fDisable();
			MEMORY_CartA0bfEnable();
			MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_LOW_BANK_8:
			MEMORY_Cart809fEnable();
			MEMORY_CartA0bfDisable();
			MEMORY_CopyROM(0x8000, 0x9fff, active_cart->image);
			break;
		case CARTRIDGE_STD_16:
		case CARTRIDGE_BLIZZARD_16:
			MEMORY_Cart809fEnable();
			MEMORY_CartA0bfEnable();
			MEMORY_CopyROM(0x8000, 0xbfff, active_cart->image);
			break;
		case CARTRIDGE_OSS_034M_16:
		case CARTRIDGE_OSS_043M_16:
			MEMORY_Cart809fDisable();
			if (active_cart->state >= 0) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image + 0x3000);
			}
			break;
		case CARTRIDGE_OSS_M091_16:
		case CARTRIDGE_OSS_8:
			MEMORY_Cart809fDisable();
			if (active_cart->state >= 0) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xb000, 0xbfff, active_cart->image);
			}
			break;
		case CARTRIDGE_WILL_64:
		case CARTRIDGE_EXP_64:
		case CARTRIDGE_DIAMOND_64:
		case CARTRIDGE_SDX_64:
		case CARTRIDGE_ATRAX_128:
		case CARTRIDGE_WILL_32:
		case CARTRIDGE_ATMAX_128:
		case CARTRIDGE_ATMAX_1024:
		case CARTRIDGE_SDX_128:
		case CARTRIDGE_ATRAX_SDX_64:
		case CARTRIDGE_ATRAX_SDX_128:
		case CARTRIDGE_TURBOSOFT_64:
		case CARTRIDGE_TURBOSOFT_128:
		case CARTRIDGE_ULTRACART_32:
		case CARTRIDGE_BLIZZARD_32:
		case CARTRIDGE_THECART_128M:
		case CARTRIDGE_THECART_32M:
		case CARTRIDGE_THECART_64M:
			MEMORY_Cart809fDisable();
			break;
		case CARTRIDGE_DB_32:
		case CARTRIDGE_XEGS_32:
		case CARTRIDGE_SWXEGS_32:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x6000);
			}
			break;
		case CARTRIDGE_XEGS_07_64:
		case CARTRIDGE_SWXEGS_64:
		case CARTRIDGE_XEGS_8F_64:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0xe000);
			}
			break;
		case CARTRIDGE_XEGS_128:
		case CARTRIDGE_SWXEGS_128:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x1e000);
			}
			break;
		case CARTRIDGE_XEGS_256:
		case CARTRIDGE_SWXEGS_256:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x3e000);
			}
			break;
		case CARTRIDGE_XEGS_512:
		case CARTRIDGE_SWXEGS_512:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x7e000);
			}
			break;
		case CARTRIDGE_XEGS_1024:
		case CARTRIDGE_SWXEGS_1024:
			if (!(active_cart->state & 0x80)) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0xfe000);
			}
			break;
		case CARTRIDGE_BBSB_40:
			MEMORY_Cart809fEnable();
			MEMORY_CartA0bfEnable();
			MEMORY_CopyROM(0x8000, 0x8fff, active_cart->image + (active_cart->state & 0x03) * 0x1000);
			MEMORY_CopyROM(0x9000, 0x9fff, active_cart->image + 0x4000 + ((active_cart->state & 0x0c) >> 2) * 0x1000);
			MEMORY_CopyROM(0xa000, 0xbfff, active_cart->image + 0x8000);
#ifndef PAGED_ATTRIB
			MEMORY_SetHARDWARE(0x8ff6, 0x8ff9);
			MEMORY_SetHARDWARE(0x9ff6, 0x9ff9);
#else
			MEMORY_readmap[0x8f] = CARTRIDGE_BountyBob1GetByte;
			MEMORY_readmap[0x9f] = CARTRIDGE_BountyBob2GetByte;
			MEMORY_writemap[0x8f] = CARTRIDGE_BountyBob1PutByte;
			MEMORY_writemap[0x9f] = CARTRIDGE_BountyBob2PutByte;
#endif
			/* No need to call SwitchBank(), return. */
			return;
		case CARTRIDGE_RIGHT_4:
			if (Atari800_machine_type == Atari800_MACHINE_800) {
				MEMORY_Cart809fEnable();
				MEMORY_dFillMem(0x8000, 0xff, 0x1000);
				MEMORY_CopyROM(0x9000, 0x9fff, active_cart->image);
				if ((!Atari800_disable_basic || BINLOAD_loading_basic) && MEMORY_have_basic) {
					MEMORY_CartA0bfEnable();
					MEMORY_CopyROM(0xa000, 0xbfff, MEMORY_basic);
				}
				else
					MEMORY_CartA0bfDisable();
			} else {
				/* there's no right slot in XL/XE */
				MEMORY_Cart809fDisable();
				MEMORY_CartA0bfDisable();
			}
			/* No need to call SwitchBank(), return. */
			return;
		case CARTRIDGE_RIGHT_8:
			if (Atari800_machine_type == Atari800_MACHINE_800) {
				MEMORY_Cart809fEnable();
				MEMORY_CopyROM(0x8000, 0x9fff, active_cart->image);
				if (!Atari800_builtin_basic
				    && (!Atari800_disable_basic || BINLOAD_loading_basic) && MEMORY_have_basic) {
					MEMORY_CartA0bfEnable();
					MEMORY_CopyROM(0xa000, 0xbfff, MEMORY_basic);
				}
				else
					MEMORY_CartA0bfDisable();
			} else {
				/* there's no right slot in XL/XE */
				MEMORY_Cart809fDisable();
				MEMORY_CartA0bfDisable();
			}
			/* No need to call SwitchBank(), return. */
			return;
		case CARTRIDGE_AST_32:
			{
				int i;
				MEMORY_Cart809fDisable();
				MEMORY_CartA0bfEnable();
				/* Copy the chosen bank 32 times over 0xa000-0xbfff. */
				for (i = 0xa000; i < 0xc000; i += 0x100)
					MEMORY_CopyROM(i, i + 0xff, active_cart->image + (active_cart->state & 0xffff));
			}
			break;
		case CARTRIDGE_MEGA_16:
		case CARTRIDGE_MEGA_32:
		case CARTRIDGE_MEGA_64:
		case CARTRIDGE_MEGA_128:
		case CARTRIDGE_MEGA_256:
		case CARTRIDGE_MEGA_512:
		case CARTRIDGE_MEGA_1024:
		case CARTRIDGE_MEGA_2048:
		case CARTRIDGE_MEGA_4096:
		case CARTRIDGE_SIC_128:
		case CARTRIDGE_SIC_256:
		case CARTRIDGE_SIC_512:
		case CARTRIDGE_MEGAMAX_2048:
			break;
		default:
			MEMORY_Cart809fDisable();
			if (!Atari800_builtin_basic
			&& (!Atari800_disable_basic || BINLOAD_loading_basic) && MEMORY_have_basic) {
				MEMORY_CartA0bfEnable();
				MEMORY_CopyROM(0xa000, 0xbfff, MEMORY_basic);
			}
			else
				MEMORY_CartA0bfDisable();
			/* No need to call SwitchBank(), return. */
			return;
		}
		SwitchBank(active_cart->state);
	}
}