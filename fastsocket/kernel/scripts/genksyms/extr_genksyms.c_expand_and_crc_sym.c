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
struct symbol {struct symbol* visited; void* expansion_trail; struct string_list* defn; } ;
struct string_list {int tag; char* string; struct string_list* next; } ;

/* Variables and functions */
#define  SYM_ENUM 132 
#define  SYM_NORMAL 131 
#define  SYM_STRUCT 130 
#define  SYM_TYPEDEF 129 
#define  SYM_UNION 128 
 struct symbol* add_symbol (char*,int,struct string_list*,int /*<<< orphan*/ ) ; 
 struct string_list** alloca (int) ; 
 int /*<<< orphan*/  debugfile ; 
 int /*<<< orphan*/  error_with_pos (char*,char*,char*) ; 
 void* expansion_trail ; 
 struct symbol* find_symbol (char*,int) ; 
 int /*<<< orphan*/  flag_dump_defs ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,...) ; 
 unsigned long partial_crc32 (char*,unsigned long) ; 
 unsigned long partial_crc32_one (char,unsigned long) ; 
 char** symbol_type_name ; 
 struct symbol* visited_symbols ; 
 struct string_list* xmalloc (int) ; 
 void* xstrdup (char*) ; 

__attribute__((used)) static unsigned long expand_and_crc_sym(struct symbol *sym, unsigned long crc)
{
	struct string_list *list = sym->defn;
	struct string_list **e, **b;
	struct string_list *tmp, **tmp2;
	int elem = 1;

	if (!list)
		return crc;

	tmp = list;
	while ((tmp = tmp->next) != NULL)
		elem++;

	b = alloca(elem * sizeof(*e));
	e = b + elem;
	tmp2 = e - 1;

	*(tmp2--) = list;
	while ((list = list->next) != NULL)
		*(tmp2--) = list;

	while (b != e) {
		struct string_list *cur;
		struct symbol *subsym;

		cur = *(b++);
		switch (cur->tag) {
		case SYM_NORMAL:
			if (flag_dump_defs)
				fprintf(debugfile, "%s ", cur->string);
			crc = partial_crc32(cur->string, crc);
			crc = partial_crc32_one(' ', crc);
			break;

		case SYM_TYPEDEF:
			subsym = find_symbol(cur->string, cur->tag);
			/* FIXME: Bad reference files can segfault here. */
			if (subsym->expansion_trail) {
				if (flag_dump_defs)
					fprintf(debugfile, "%s ", cur->string);
				crc = partial_crc32(cur->string, crc);
				crc = partial_crc32_one(' ', crc);
			} else {
				subsym->expansion_trail = expansion_trail;
				expansion_trail = subsym;
				crc = expand_and_crc_sym(subsym, crc);
			}
			break;

		case SYM_STRUCT:
		case SYM_UNION:
		case SYM_ENUM:
			subsym = find_symbol(cur->string, cur->tag);
			if (!subsym) {
				struct string_list *n, *t = NULL;

				error_with_pos("expand undefined %s %s",
					       symbol_type_name[cur->tag],
					       cur->string);

				n = xmalloc(sizeof(*n));
				n->string = xstrdup(symbol_type_name[cur->tag]);
				n->tag = SYM_NORMAL;
				n->next = t;
				t = n;

				n = xmalloc(sizeof(*n));
				n->string = xstrdup(cur->string);
				n->tag = SYM_NORMAL;
				n->next = t;
				t = n;

				n = xmalloc(sizeof(*n));
				n->string = xstrdup("{");
				n->tag = SYM_NORMAL;
				n->next = t;
				t = n;

				n = xmalloc(sizeof(*n));
				n->string = xstrdup("UNKNOWN");
				n->tag = SYM_NORMAL;
				n->next = t;
				t = n;

				n = xmalloc(sizeof(*n));
				n->string = xstrdup("}");
				n->tag = SYM_NORMAL;
				n->next = t;
				t = n;

				subsym =
				    add_symbol(cur->string, cur->tag, n, 0);
			}
			if (subsym->expansion_trail) {
				if (flag_dump_defs) {
					fprintf(debugfile, "%s %s ",
						symbol_type_name[cur->tag],
						cur->string);
				}

				crc = partial_crc32(symbol_type_name[cur->tag],
						    crc);
				crc = partial_crc32_one(' ', crc);
				crc = partial_crc32(cur->string, crc);
				crc = partial_crc32_one(' ', crc);
			} else {
				subsym->expansion_trail = expansion_trail;
				expansion_trail = subsym;
				crc = expand_and_crc_sym(subsym, crc);
			}
			break;
		}
	}

	{
		static struct symbol **end = &visited_symbols;

		if (!sym->visited) {
			*end = sym;
			end = &sym->visited;
			sym->visited = (struct symbol *)-1L;
		}
	}

	return crc;
}