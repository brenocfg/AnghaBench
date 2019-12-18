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
struct text_range {unsigned long long start; unsigned long long end; int /*<<< orphan*/  etext; int /*<<< orphan*/  stext; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (struct text_range*) ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 struct text_range* text_ranges ; 

__attribute__((used)) static int read_symbol_tr(const char *sym, unsigned long long addr)
{
	size_t i;
	struct text_range *tr;

	for (i = 0; i < ARRAY_SIZE(text_ranges); ++i) {
		tr = &text_ranges[i];

		if (strcmp(sym, tr->stext) == 0) {
			tr->start = addr;
			return 0;
		} else if (strcmp(sym, tr->etext) == 0) {
			tr->end = addr;
			return 0;
		}
	}

	return 1;
}