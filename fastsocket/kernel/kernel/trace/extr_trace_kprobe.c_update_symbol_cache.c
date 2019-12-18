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
struct symbol_cache {unsigned long addr; scalar_t__ offset; int /*<<< orphan*/  symbol; } ;

/* Variables and functions */
 scalar_t__ kallsyms_lookup_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned long update_symbol_cache(struct symbol_cache *sc)
{
	sc->addr = (unsigned long)kallsyms_lookup_name(sc->symbol);
	if (sc->addr)
		sc->addr += sc->offset;
	return sc->addr;
}