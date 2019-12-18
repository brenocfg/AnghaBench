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
typedef  int UBYTE ;

/* Variables and functions */
 int /*<<< orphan*/  Log_print (char*,int,int) ; 
 int* MEMORY_mem ; 
 int axlon_curbank ; 
 int axlon_current_bankmask ; 
 int* axlon_ram ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 

__attribute__((used)) static void AxlonPutByte(UWORD addr, UBYTE byte)
{
	int newbank;
	/*Write-through to RAM if it is the page 0x0f shadow*/
	if ((addr&0xff00) == 0x0f00) MEMORY_mem[addr] = byte;
	if ((addr&0xff) < 0xc0) return; /*0xffc0-0xffff and 0x0fc0-0x0fff only*/
#ifdef DEBUG
	Log_print("AxlonPutByte:%4X:%2X", addr, byte);
#endif
	newbank = (byte&axlon_current_bankmask);
	if (newbank == axlon_curbank) return;
	memcpy(axlon_ram + axlon_curbank*0x4000, MEMORY_mem + 0x4000, 0x4000);
	memcpy(MEMORY_mem + 0x4000, axlon_ram + newbank*0x4000, 0x4000);
	axlon_curbank = newbank;
}