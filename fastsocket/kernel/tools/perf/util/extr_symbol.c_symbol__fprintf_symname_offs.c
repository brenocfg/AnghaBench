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
struct symbol {char* name; unsigned long start; } ;
struct addr_location {unsigned long addr; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t fprintf (int /*<<< orphan*/ *,char*,...) ; 

size_t symbol__fprintf_symname_offs(const struct symbol *sym,
				    const struct addr_location *al, FILE *fp)
{
	unsigned long offset;
	size_t length;

	if (sym && sym->name) {
		length = fprintf(fp, "%s", sym->name);
		if (al) {
			offset = al->addr - sym->start;
			length += fprintf(fp, "+0x%lx", offset);
		}
		return length;
	} else
		return fprintf(fp, "[unknown]");
}