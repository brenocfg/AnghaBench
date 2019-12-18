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
typedef  int UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  ANTIC_PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Atari800_MACHINE_5200 ; 
 int /*<<< orphan*/  Atari800_machine_type ; 
 int /*<<< orphan*/  AxlonPutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CARTRIDGE_BountyBob1 (int) ; 
 int /*<<< orphan*/  CARTRIDGE_BountyBob2 (int) ; 
 int /*<<< orphan*/  CARTRIDGE_PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GTIA_PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MosaicPutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBI_D1PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBI_D6PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PBI_D7PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PIA_PutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  POKEY_PutByte (int,int /*<<< orphan*/ ) ; 

void MEMORY_HwPutByte(UWORD addr, UBYTE byte)
{
	switch (addr & 0xff00) {
	case 0x4f00:
	case 0x8f00:
		CARTRIDGE_BountyBob1(addr);
		break;
	case 0x5f00:
	case 0x9f00:
		CARTRIDGE_BountyBob2(addr);
		break;
	case 0xd000:				/* GTIA */
	case 0xc000:				/* GTIA - 5200 */
	case 0xc100:				/* GTIA - 5200 */
	case 0xc200:				/* GTIA - 5200 */
	case 0xc300:				/* GTIA - 5200 */
	case 0xc400:				/* GTIA - 5200 */
	case 0xc500:				/* GTIA - 5200 */
	case 0xc600:				/* GTIA - 5200 */
	case 0xc700:				/* GTIA - 5200 */
	case 0xc800:				/* GTIA - 5200 */
	case 0xc900:				/* GTIA - 5200 */
	case 0xca00:				/* GTIA - 5200 */
	case 0xcb00:				/* GTIA - 5200 */
	case 0xcc00:				/* GTIA - 5200 */
	case 0xcd00:				/* GTIA - 5200 */
	case 0xce00:				/* GTIA - 5200 */
		GTIA_PutByte(addr, byte);
		break;
	case 0xd200:				/* POKEY */
	case 0xe800:				/* POKEY - 5200 */
	case 0xe900:				/* POKEY - 5200 */
	case 0xea00:				/* POKEY - 5200 */
	case 0xeb00:				/* POKEY - 5200 */
	case 0xec00:				/* POKEY - 5200 */
	case 0xed00:				/* POKEY - 5200 */
	case 0xee00:				/* POKEY - 5200 */
	case 0xef00:				/* POKEY - 5200 */
		POKEY_PutByte(addr, byte);
		break;
	case 0xd300:				/* PIA */
		PIA_PutByte(addr, byte);
		break;
	case 0xd400:				/* ANTIC */
		ANTIC_PutByte(addr, byte);
		break;
	case 0xd500:				/* bank-switching cartridges, RTIME-8 */
		CARTRIDGE_PutByte(addr, byte);
		break;
	case 0xff00:				/* Mosaic memory expansion for 400/800 */
		MosaicPutByte(addr,byte);
		break;
	case 0xcf00:				/* Axlon memory expansion for 800 */
	case 0x0f00:				/* Axlon shadow */
		if (Atari800_machine_type == Atari800_MACHINE_5200) {
			GTIA_PutByte(addr, byte); /* GTIA-5200 cfxx */
		}
		else {
			AxlonPutByte(addr,byte);
		}
		break;
	case 0xd100:				/* PBI page D1 */
		PBI_D1PutByte(addr, byte);
		break;
	case 0xd600:				/* PBI page D6 */
		PBI_D6PutByte(addr, byte);
		break;
	case 0xd700:				/* PBI page D7 */
		PBI_D7PutByte(addr, byte);
		break;
	default:
		break;
	}
}