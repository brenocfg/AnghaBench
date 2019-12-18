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
struct symbol {int end; int start; } ;
struct sym_hist {double sum; scalar_t__* addr; } ;
struct source_line {scalar_t__ percent; } ;
struct disasm_line {int offset; } ;
struct annotation {TYPE_1__* src; } ;
typedef  size_t s64 ;
struct TYPE_2__ {int /*<<< orphan*/  source; struct source_line* lines; } ;

/* Variables and functions */
 struct sym_hist* annotation__histogram (struct annotation*,int) ; 
 struct disasm_line* disasm__get_next_ip_line (int /*<<< orphan*/ *,struct disasm_line*) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static double disasm_line__calc_percent(struct disasm_line *dl, struct symbol *sym, int evidx)
{
	double percent = 0.0;

	if (dl->offset != -1) {
		int len = sym->end - sym->start;
		unsigned int hits = 0;
		struct annotation *notes = symbol__annotation(sym);
		struct source_line *src_line = notes->src->lines;
		struct sym_hist *h = annotation__histogram(notes, evidx);
		s64 offset = dl->offset;
		struct disasm_line *next;

		next = disasm__get_next_ip_line(&notes->src->source, dl);
		while (offset < (s64)len &&
		       (next == NULL || offset < next->offset)) {
			if (src_line) {
				percent += src_line[offset].percent;
			} else
				hits += h->addr[offset];

			++offset;
		}
		/*
 		 * If the percentage wasn't already calculated in
 		 * symbol__get_source_line, do it now:
 		 */
		if (src_line == NULL && h->sum)
			percent = 100.0 * hits / h->sum;
	}

	return percent;
}