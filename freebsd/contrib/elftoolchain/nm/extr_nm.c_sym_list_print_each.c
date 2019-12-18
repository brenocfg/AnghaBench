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
struct var_info_head {int dummy; } ;
struct sym_print_data {char* filename; char* objname; int sh_num; char** s_table; int /*<<< orphan*/  t_table; } ;
struct sym_entry {int /*<<< orphan*/ * name; TYPE_1__* sym; } ;
struct line_info_head {int dummy; } ;
struct func_info_head {int dummy; } ;
struct TYPE_6__ {scalar_t__ print_name; int debug_line; int /*<<< orphan*/  (* elem_print_fn ) (char,char const*,TYPE_1__*,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {int st_shndx; } ;

/* Variables and functions */
 scalar_t__ CHECK_SYM_PRINT_DATA (struct sym_print_data*) ; 
 int /*<<< orphan*/  IS_UNDEF_SYM_TYPE (char) ; 
 scalar_t__ PRINT_NAME_FULL ; 
#define  SHN_ABS 134 
#define  SHN_COMMON 133 
#define  SHN_HIOS 132 
#define  SHN_HIPROC 131 
#define  SHN_HIRESERVE 130 
#define  SHN_LOOS 129 
#define  SHN_LOPROC 128 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 char get_sym_type (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_3__ nm_opts ; 
 int /*<<< orphan*/  print_lineno (struct sym_entry*,struct func_info_head*,struct var_info_head*,struct line_info_head*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (char,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sym_elem_print_all_portable (char,char const*,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sym_list_print_each(struct sym_entry *ep, struct sym_print_data *p,
    struct func_info_head *func_info, struct var_info_head *var_info,
    struct line_info_head *line_info)
{
	const char *sec;
	char type;

	if (ep == NULL || CHECK_SYM_PRINT_DATA(p))
		return;

	assert(ep->name != NULL);
	assert(ep->sym != NULL);

	type = get_sym_type(ep->sym, p->t_table);

	if (nm_opts.print_name == PRINT_NAME_FULL) {
		printf("%s", p->filename);
		if (nm_opts.elem_print_fn == &sym_elem_print_all_portable) {
			if (p->objname != NULL)
				printf("[%s]", p->objname);
			printf(": ");
		} else {
			if (p->objname != NULL)
				printf(":%s", p->objname);
			printf(":");
		}
	}

	switch (ep->sym->st_shndx) {
	case SHN_LOPROC:
		/* LOPROC or LORESERVE */
		sec = "*LOPROC*";
		break;
	case SHN_HIPROC:
		sec = "*HIPROC*";
		break;
	case SHN_LOOS:
		sec = "*LOOS*";
		break;
	case SHN_HIOS:
		sec = "*HIOS*";
		break;
	case SHN_ABS:
		sec = "*ABS*";
		break;
	case SHN_COMMON:
		sec = "*COM*";
		break;
	case SHN_HIRESERVE:
		/* HIRESERVE or XINDEX */
		sec = "*HIRESERVE*";
		break;
	default:
		if (ep->sym->st_shndx > p->sh_num)
			return;
		sec = p->s_table[ep->sym->st_shndx];
		break;
	}

	nm_opts.elem_print_fn(type, sec, ep->sym, ep->name);

	if (nm_opts.debug_line == true && !IS_UNDEF_SYM_TYPE(type))
		print_lineno(ep, func_info, var_info, line_info);

	printf("\n");
}