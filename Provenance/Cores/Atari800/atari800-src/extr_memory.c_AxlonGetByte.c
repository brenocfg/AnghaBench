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
 int /*<<< orphan*/  Log_print (char*,size_t) ; 
 int /*<<< orphan*/ * MEMORY_mem ; 

__attribute__((used)) static UBYTE AxlonGetByte(UWORD addr, int no_side_effects)
{
#ifdef DEBUG
	Log_print("AxlonGetByte%4X",addr);
#endif
	return MEMORY_mem[addr];
}