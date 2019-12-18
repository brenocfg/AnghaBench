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
 int /*<<< orphan*/  AF80_D5PutByte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ AF80_enabled ; 
 int /*<<< orphan*/  CARTRIDGE_main ; 
 int /*<<< orphan*/  CARTRIDGE_piggyback ; 
 int /*<<< orphan*/  IDE_PutByte (int,int /*<<< orphan*/ ) ; 
 scalar_t__ IDE_enabled ; 
 int /*<<< orphan*/  PutByte (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  RTIME_PutByte (int /*<<< orphan*/ ) ; 
 scalar_t__ RTIME_enabled ; 

void CARTRIDGE_PutByte(UWORD addr, UBYTE byte)
{
#ifdef AF80
	if (AF80_enabled) {
		AF80_D5PutByte(addr,byte);
		/* Return, because AF_80_enabled means there's an AF80
		   cartridge in the left slot and no other cartridges are
		   there. */
		return;
	}
#endif
	if (RTIME_enabled && (addr == 0xd5b8 || addr == 0xd5b9)) {
		RTIME_PutByte(byte);
	}
#ifdef IDE
	if (IDE_enabled && (addr <= 0xd50f)) {
		IDE_PutByte(addr,byte);
	}
#endif
	PutByte(&CARTRIDGE_main, addr, byte);
	PutByte(&CARTRIDGE_piggyback, addr, byte);
}