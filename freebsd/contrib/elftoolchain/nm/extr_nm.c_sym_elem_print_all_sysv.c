#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_5__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  (* size_print_fn ) (TYPE_1__ const*) ;int /*<<< orphan*/  (* value_print_fn ) (TYPE_1__ const*) ;} ;
struct TYPE_6__ {int st_info; scalar_t__ st_size; } ;
typedef  TYPE_1__ GElf_Sym ;

/* Variables and functions */
 scalar_t__ IS_UNDEF_SYM_TYPE (char) ; 
 int /*<<< orphan*/  PRINT_DEMANGLED_NAME (char*,char const*) ; 
#define  STT_FILE 134 
#define  STT_FUNC 133 
#define  STT_HIPROC 132 
#define  STT_LOPROC 131 
#define  STT_NOTYPE 130 
#define  STT_OBJECT 129 
#define  STT_SECTION 128 
 TYPE_5__ nm_opts ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__ const*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__ const*) ; 

__attribute__((used)) static void
sym_elem_print_all_sysv(char type, const char *sec, const GElf_Sym *sym,
    const char *name)
{

	if (sec == NULL || sym == NULL || name == NULL ||
	    nm_opts.value_print_fn == NULL)
		return;

	PRINT_DEMANGLED_NAME("%-20s|", name);
	if (IS_UNDEF_SYM_TYPE(type))
		printf("                ");
	else
		nm_opts.value_print_fn(sym);

	printf("|   %c  |", type);

	switch (sym->st_info & 0xf) {
	case STT_OBJECT:
		printf("%18s|", "OBJECT");
		break;

	case STT_FUNC:
		printf("%18s|", "FUNC");
		break;

	case STT_SECTION:
		printf("%18s|", "SECTION");
		break;

	case STT_FILE:
		printf("%18s|", "FILE");
		break;

	case STT_LOPROC:
		printf("%18s|", "LOPROC");
		break;

	case STT_HIPROC:
		printf("%18s|", "HIPROC");
		break;

	case STT_NOTYPE:
	default:
		printf("%18s|", "NOTYPE");
	}

	if (sym->st_size != 0)
		nm_opts.size_print_fn(sym);
	else
		printf("                ");

	printf("|     |%s", sec);
}