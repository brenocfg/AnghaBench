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
struct __addr_die_search_param {int /*<<< orphan*/ * die_mem; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  Dwarf_Die ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int /*<<< orphan*/  __die_search_func_cb ; 
 int /*<<< orphan*/  dwarf_getfuncs (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct __addr_die_search_param*,int /*<<< orphan*/ ) ; 

Dwarf_Die *die_find_realfunc(Dwarf_Die *cu_die, Dwarf_Addr addr,
				    Dwarf_Die *die_mem)
{
	struct __addr_die_search_param ad;
	ad.addr = addr;
	ad.die_mem = die_mem;
	/* dwarf_getscopes can't find subprogram. */
	if (!dwarf_getfuncs(cu_die, __die_search_func_cb, &ad, 0))
		return NULL;
	else
		return die_mem;
}