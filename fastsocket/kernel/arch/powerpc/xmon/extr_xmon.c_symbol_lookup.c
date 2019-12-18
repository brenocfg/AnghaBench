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

/* Variables and functions */
 int /*<<< orphan*/  bus_error_jmp ; 
 int catch_memory_errors ; 
 int /*<<< orphan*/  getstring (char*,int) ; 
 int inchar () ; 
 unsigned long kallsyms_lookup_name (char*) ; 
 int /*<<< orphan*/  printf (char*,char*,...) ; 
 int /*<<< orphan*/  scanhex (unsigned long*) ; 
 int /*<<< orphan*/  setjmp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sync () ; 
 int /*<<< orphan*/  termch ; 
 int /*<<< orphan*/  xmon_print_symbol (unsigned long,char*,char*) ; 

__attribute__((used)) static void
symbol_lookup(void)
{
	int type = inchar();
	unsigned long addr;
	static char tmp[64];

	switch (type) {
	case 'a':
		if (scanhex(&addr))
			xmon_print_symbol(addr, ": ", "\n");
		termch = 0;
		break;
	case 's':
		getstring(tmp, 64);
		if (setjmp(bus_error_jmp) == 0) {
			catch_memory_errors = 1;
			sync();
			addr = kallsyms_lookup_name(tmp);
			if (addr)
				printf("%s: %lx\n", tmp, addr);
			else
				printf("Symbol '%s' not found.\n", tmp);
			sync();
		}
		catch_memory_errors = 0;
		termch = 0;
		break;
	}
}