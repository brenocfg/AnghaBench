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
struct TYPE_3__ {uintptr_t addr; } ;
typedef  TYPE_1__ syment_t ;

/* Variables and functions */
 int nsyms ; 
 TYPE_1__* symbol_table ; 

__attribute__((used)) static void
remove_symbol(uintptr_t addr)
{
	int i;
	syment_t *sep = symbol_table;

	for (i = 0; i < nsyms; i++, sep++)
		if (sep->addr == addr)
			sep->addr = 0;
}