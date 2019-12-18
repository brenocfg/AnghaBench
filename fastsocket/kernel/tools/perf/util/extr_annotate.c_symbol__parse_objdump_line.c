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
typedef  int u64 ;
struct symbol {int /*<<< orphan*/  end; int /*<<< orphan*/  start; } ;
struct map {int dummy; } ;
struct disasm_line {int dummy; } ;
struct annotation {TYPE_1__* src; } ;
typedef  int s64 ;
struct TYPE_2__ {int /*<<< orphan*/  source; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  disasm__add (int /*<<< orphan*/ *,struct disasm_line*) ; 
 struct disasm_line* disasm_line__new (int,char*,size_t) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 scalar_t__ isspace (char) ; 
 int map__rip_2objdump (struct map*,int /*<<< orphan*/ ) ; 
 char* strchr (char*,char) ; 
 int strtoull (char*,char**,int) ; 
 struct annotation* symbol__annotation (struct symbol*) ; 

__attribute__((used)) static int symbol__parse_objdump_line(struct symbol *sym, struct map *map,
				      FILE *file, size_t privsize)
{
	struct annotation *notes = symbol__annotation(sym);
	struct disasm_line *dl;
	char *line = NULL, *parsed_line, *tmp, *tmp2, *c;
	size_t line_len;
	s64 line_ip, offset = -1;

	if (getline(&line, &line_len, file) < 0)
		return -1;

	if (!line)
		return -1;

	while (line_len != 0 && isspace(line[line_len - 1]))
		line[--line_len] = '\0';

	c = strchr(line, '\n');
	if (c)
		*c = 0;

	line_ip = -1;
	parsed_line = line;

	/*
	 * Strip leading spaces:
	 */
	tmp = line;
	while (*tmp) {
		if (*tmp != ' ')
			break;
		tmp++;
	}

	if (*tmp) {
		/*
		 * Parse hexa addresses followed by ':'
		 */
		line_ip = strtoull(tmp, &tmp2, 16);
		if (*tmp2 != ':' || tmp == tmp2 || tmp2[1] == '\0')
			line_ip = -1;
	}

	if (line_ip != -1) {
		u64 start = map__rip_2objdump(map, sym->start),
		    end = map__rip_2objdump(map, sym->end);

		offset = line_ip - start;
		if (offset < 0 || (u64)line_ip > end)
			offset = -1;
		else
			parsed_line = tmp2 + 1;
	}

	dl = disasm_line__new(offset, parsed_line, privsize);
	free(line);

	if (dl == NULL)
		return -1;

	disasm__add(&notes->src->source, dl);

	return 0;
}