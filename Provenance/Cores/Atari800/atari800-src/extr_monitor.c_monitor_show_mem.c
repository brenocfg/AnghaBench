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
 int MEMORY_SafeGetByte (int) ; 
 int /*<<< orphan*/  get_hex (int*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  putchar (char) ; 

__attribute__((used)) static void monitor_show_mem(UWORD *addr)
{
	int count = 16;
	get_hex(addr);
	do {
		int i;
		printf("%04X: ", *addr);
		for (i = 0; i < 16; i++)
			printf("%02X ", MEMORY_SafeGetByte((UWORD) (*addr + i)));
		putchar(' ');
		for (i = 0; i < 16; i++) {
			UBYTE c;
			c = MEMORY_SafeGetByte(*addr);
			(*addr)++;
			putchar((c >= ' ' && c <= 'z' && c != '\x60') ? c : '.');
		}
		putchar('\n');
	} while (--count > 0);
}