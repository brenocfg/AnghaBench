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
typedef  int UBYTE ;
struct TYPE_2__ {int pos; int* url; } ;

/* Variables and functions */
 int /*<<< orphan*/  CPU_ClrN ; 
 int /*<<< orphan*/  CPU_SetN ; 
 int CPU_regA ; 
 int CPU_regY ; 
 int /*<<< orphan*/  Log_print (char*,int,int,int) ; 
 TYPE_1__ dev_b_status ; 
 scalar_t__ devbug ; 

__attribute__((used)) static void Devices_B_Write(void)
{
	UBYTE byte;

	byte = CPU_regA;

	if (devbug)
		Log_print("B: WRITE ([%d] %02X, '%c')", dev_b_status.pos, byte, byte);

	if (byte == 0x9b)
		byte = '\0';

	if (dev_b_status.pos >= sizeof(dev_b_status.url) - 1) {
		CPU_regY = 135; /* attempted to write to a read-only device */
		CPU_SetN;
		return;
	}
	dev_b_status.url[dev_b_status.pos++] = byte;

	CPU_regY = 1;
	CPU_ClrN;
}