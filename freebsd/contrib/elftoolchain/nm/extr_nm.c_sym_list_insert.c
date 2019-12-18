#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sym_head {int dummy; } ;
struct sym_entry {TYPE_3__* sym; struct sym_entry* name; } ;
struct TYPE_6__ {int /*<<< orphan*/  st_value; } ;
struct TYPE_5__ {scalar_t__ st_shndx; int /*<<< orphan*/  st_size; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ SHN_COMMON ; 
 int /*<<< orphan*/  STAILQ_INSERT_TAIL (struct sym_head*,struct sym_entry*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct sym_entry*) ; 
 void* malloc (int) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_1__ const*,int) ; 
 struct sym_entry* strdup (char const*) ; 
 int /*<<< orphan*/  sym_entries ; 
 int /*<<< orphan*/  warn (char*) ; 

__attribute__((used)) static int
sym_list_insert(struct sym_head *headp, const char *name, const GElf_Sym *sym)
{
	struct sym_entry *e;

	if (headp == NULL || name == NULL || sym == NULL)
		return (0);
	if ((e = malloc(sizeof(struct sym_entry))) == NULL) {
		warn("malloc");
		return (0);
	}
	if ((e->name = strdup(name)) == NULL) {
		warn("strdup");
		free(e);
		return (0);
	}
	if ((e->sym = malloc(sizeof(GElf_Sym))) == NULL) {
		warn("malloc");
		free(e->name);
		free(e);
		return (0);
	}

	memcpy(e->sym, sym, sizeof(GElf_Sym));

	/* Display size instead of value for common symbol. */
	if (sym->st_shndx == SHN_COMMON)
		e->sym->st_value = sym->st_size;

	STAILQ_INSERT_TAIL(headp, e, sym_entries);

	return (1);
}