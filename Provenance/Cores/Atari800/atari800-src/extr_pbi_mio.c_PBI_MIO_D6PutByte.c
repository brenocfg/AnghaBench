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
 int /*<<< orphan*/ * MEMORY_mem ; 
 int /*<<< orphan*/  mio_ram_enabled ; 

void PBI_MIO_D6PutByte(UWORD addr, UBYTE byte)
{
	if (!mio_ram_enabled) return;
	MEMORY_mem[addr]=byte;
}