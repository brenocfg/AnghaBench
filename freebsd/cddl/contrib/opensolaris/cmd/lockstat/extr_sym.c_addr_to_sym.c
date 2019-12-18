#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {uintptr_t addr; size_t size; char* name; } ;
typedef  TYPE_1__ syment_t ;

/* Variables and functions */
 int nsyms ; 
 TYPE_1__* symbol_table ; 

char *
addr_to_sym(uintptr_t addr, uintptr_t *offset, size_t *sizep)
{
	int lo = 0;
	int hi = nsyms - 1;
	int mid;
	syment_t *sep;

	while (hi - lo > 1) {
		mid = (lo + hi) / 2;
		if (addr >= symbol_table[mid].addr) {
			lo = mid;
		} else {
			hi = mid;
		}
	}
	sep = &symbol_table[lo];
	*offset = addr - sep->addr;
	*sizep = sep->size;
	return (sep->name);
}