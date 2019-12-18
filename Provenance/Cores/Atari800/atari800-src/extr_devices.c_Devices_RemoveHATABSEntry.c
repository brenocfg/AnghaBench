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
typedef  scalar_t__ UWORD ;

/* Variables and functions */
 char MEMORY_dGetByte (scalar_t__) ; 
 scalar_t__ MEMORY_dGetWord (scalar_t__) ; 
 int /*<<< orphan*/  MEMORY_dPutByte (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_dPutWord (scalar_t__,int /*<<< orphan*/ ) ; 

void Devices_RemoveHATABSEntry(char device, UWORD entry_address,
							  UWORD table_address)
{
	if (entry_address != 0 && MEMORY_dGetByte(entry_address) == device
		&& MEMORY_dGetWord(entry_address + 1) == table_address) {
		MEMORY_dPutByte(entry_address, 0);
		MEMORY_dPutWord(entry_address + 1, 0);
	}
}