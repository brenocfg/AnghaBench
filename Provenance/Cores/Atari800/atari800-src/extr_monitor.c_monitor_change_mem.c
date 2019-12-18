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
 scalar_t__ MEMORY_HARDWARE ; 
 int /*<<< orphan*/  MEMORY_HwPutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_ROM_PutByte (int,int /*<<< orphan*/ ) ; 
 scalar_t__* MEMORY_attrib ; 
 int /*<<< orphan*/  MEMORY_dPutByte (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MEMORY_writemap (int,int /*<<< orphan*/ ) ; 
 scalar_t__ get_hex (int*) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void monitor_change_mem(UWORD *addr)
{
	UWORD temp = 0;
	get_hex(addr);
	while (get_hex(&temp)) {
#ifdef PAGED_ATTRIB
		if (MEMORY_writemap[*addr >> 8] != NULL && MEMORY_writemap[*addr >> 8] != MEMORY_ROM_PutByte)
			(*MEMORY_writemap[*addr >> 8])(*addr, (UBYTE) temp);
#else
		if (MEMORY_attrib[*addr] == MEMORY_HARDWARE)
			MEMORY_HwPutByte(*addr, (UBYTE) temp);
#endif
		else /* RAM, ROM */
			MEMORY_dPutByte(*addr, (UBYTE) temp);
		(*addr)++;
		if (temp > 0xff) {
#ifdef PAGED_ATTRIB
			if (MEMORY_writemap[*addr >> 8] != NULL && MEMORY_writemap[*addr >> 8] != MEMORY_ROM_PutByte)
				(*MEMORY_writemap[*addr >> 8])(*addr, (UBYTE) (temp >> 8));
#else
			if (MEMORY_attrib[*addr] == MEMORY_HARDWARE)
				MEMORY_HwPutByte(*addr, (UBYTE) (temp >> 8));
#endif
			else /* RAM, ROM */
				MEMORY_dPutByte(*addr, (UBYTE) (temp >> 8));
			(*addr)++;
		}
	}
}