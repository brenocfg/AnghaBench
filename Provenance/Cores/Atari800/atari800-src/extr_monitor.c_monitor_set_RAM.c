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

/* Variables and functions */
 int /*<<< orphan*/  MEMORY_SetRAM (int,int) ; 
 scalar_t__ get_attrib_range (int*,int*) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 

__attribute__((used)) static void monitor_set_RAM(void)
{
	UWORD addr1;
	UWORD addr2;
	if (get_attrib_range(&addr1, &addr2)) {
		MEMORY_SetRAM(addr1, addr2);
		printf("Changed memory from %04X to %04X into RAM\n",
			   addr1, addr2);
	}
}