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
typedef  char UBYTE ;

/* Variables and functions */
 int* CommandFrame ; 
 int /*<<< orphan*/  DataBuffer ; 
 char SIO_MAX_DRIVES ; 
 char SIO_WriteSector (char,int,int /*<<< orphan*/ ) ; 
 char SIO_WriteStatusBlock (char,int /*<<< orphan*/ ) ; 

__attribute__((used)) static UBYTE WriteSectorBack(void)
{
	UWORD sector;
	UBYTE unit;

	sector = CommandFrame[2] + (CommandFrame[3] << 8);
	unit = CommandFrame[0] - '1';
	if (unit >= SIO_MAX_DRIVES)		/* UBYTE range ! */
		return 0;
	switch (CommandFrame[1]) {
	case 0x4f:				/* Write Status Block */
		return SIO_WriteStatusBlock(unit, DataBuffer);
	case 0x50:				/* Write */
	case 0x57:
	case 0xD0:				/* xf551 hispeed */
	case 0xD7:
		return SIO_WriteSector(unit, sector, DataBuffer);
	default:
		return 'E';
	}
}