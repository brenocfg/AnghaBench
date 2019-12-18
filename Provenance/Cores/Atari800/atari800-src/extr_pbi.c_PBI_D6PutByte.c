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
typedef  size_t UWORD ;
typedef  int /*<<< orphan*/  UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  AF80_D6PutByte (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ AF80_enabled ; 
 int /*<<< orphan*/ * MEMORY_mem ; 
 int /*<<< orphan*/  PBI_BB_D6PutByte (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ PBI_BB_enabled ; 
 scalar_t__ PBI_D6D7ram ; 
 int /*<<< orphan*/  PBI_MIO_D6PutByte (size_t,int /*<<< orphan*/ ) ; 
 scalar_t__ PBI_MIO_enabled ; 

void PBI_D6PutByte(UWORD addr, UBYTE byte)
{
#ifdef AF80
	if (AF80_enabled) {
		AF80_D6PutByte(addr,byte);
		return;
	}
#endif
#ifdef PBI_MIO
	if (PBI_MIO_enabled) {
		PBI_MIO_D6PutByte(addr,byte);
		return;
	}
#endif
#ifdef PBI_BB
	if(PBI_BB_enabled) {
		PBI_BB_D6PutByte(addr,byte);
		return;
	}
#endif
	/* XLD/1090 has ram here */
	if (PBI_D6D7ram) MEMORY_mem[addr]=byte;
}