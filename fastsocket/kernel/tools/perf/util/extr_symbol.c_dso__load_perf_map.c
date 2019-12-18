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
typedef  int /*<<< orphan*/  u64 ;
typedef  scalar_t__ (* symbol_filter_t ) (struct map*,struct symbol*) ;
struct symbol {int dummy; } ;
struct map {size_t type; } ;
struct dso {int /*<<< orphan*/ * symbols; int /*<<< orphan*/  long_name; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  STB_GLOBAL ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  feof (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int getline (char**,size_t*,int /*<<< orphan*/ *) ; 
 int hex2u64 (char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  symbol__delete (struct symbol*) ; 
 struct symbol* symbol__new (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  symbols__insert (int /*<<< orphan*/ *,struct symbol*) ; 

__attribute__((used)) static int dso__load_perf_map(struct dso *dso, struct map *map,
			      symbol_filter_t filter)
{
	char *line = NULL;
	size_t n;
	FILE *file;
	int nr_syms = 0;

	file = fopen(dso->long_name, "r");
	if (file == NULL)
		goto out_failure;

	while (!feof(file)) {
		u64 start, size;
		struct symbol *sym;
		int line_len, len;

		line_len = getline(&line, &n, file);
		if (line_len < 0)
			break;

		if (!line)
			goto out_failure;

		line[--line_len] = '\0'; /* \n */

		len = hex2u64(line, &start);

		len++;
		if (len + 2 >= line_len)
			continue;

		len += hex2u64(line + len, &size);

		len++;
		if (len + 2 >= line_len)
			continue;

		sym = symbol__new(start, size, STB_GLOBAL, line + len);

		if (sym == NULL)
			goto out_delete_line;

		if (filter && filter(map, sym))
			symbol__delete(sym);
		else {
			symbols__insert(&dso->symbols[map->type], sym);
			nr_syms++;
		}
	}

	free(line);
	fclose(file);

	return nr_syms;

out_delete_line:
	free(line);
out_failure:
	return -1;
}