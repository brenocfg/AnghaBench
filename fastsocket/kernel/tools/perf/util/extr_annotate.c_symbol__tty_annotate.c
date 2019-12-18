#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct symbol {int dummy; } ;
struct rb_root {int dummy; } ;
struct map {struct dso* dso; } ;
struct dso {char* long_name; } ;
struct TYPE_4__ {TYPE_1__* src; } ;
struct TYPE_3__ {int /*<<< orphan*/  source; } ;

/* Variables and functions */
 struct rb_root RB_ROOT ; 
 int /*<<< orphan*/  disasm__purge (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  print_summary (struct rb_root*,char const*) ; 
 scalar_t__ symbol__annotate (struct symbol*,struct map*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__annotate_printf (struct symbol*,struct map*,int,int,int,int,int /*<<< orphan*/ ) ; 
 TYPE_2__* symbol__annotation (struct symbol*) ; 
 int /*<<< orphan*/  symbol__free_source_line (struct symbol*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  symbol__get_source_line (struct symbol*,struct map*,int,struct rb_root*,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  symbol__size (struct symbol*) ; 

int symbol__tty_annotate(struct symbol *sym, struct map *map, int evidx,
			 bool print_lines, bool full_paths, int min_pcnt,
			 int max_lines)
{
	struct dso *dso = map->dso;
	const char *filename = dso->long_name;
	struct rb_root source_line = RB_ROOT;
	u64 len;

	if (symbol__annotate(sym, map, 0) < 0)
		return -1;

	len = symbol__size(sym);

	if (print_lines) {
		symbol__get_source_line(sym, map, evidx, &source_line,
					len, filename);
		print_summary(&source_line, filename);
	}

	symbol__annotate_printf(sym, map, evidx, full_paths,
				min_pcnt, max_lines, 0);
	if (print_lines)
		symbol__free_source_line(sym, len);

	disasm__purge(&symbol__annotation(sym)->src->source);

	return 0;
}