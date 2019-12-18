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
typedef  int /*<<< orphan*/  uint32_t ;
struct elfcopy {char* s_so; int s_so_cap; int s_cnt; char* s_sn; int s_sn_cap; size_t s_sn_sz; char rela_off; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 void* _INIT_SYMNAME_CAP ; 
 void* _INIT_SYMOFF_CAP ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 void* malloc (void*) ; 
 void* realloc (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
add_to_ar_sym_table(struct elfcopy *ecp, const char *name)
{

	if (ecp->s_so == NULL) {
		if ((ecp->s_so = malloc(_INIT_SYMOFF_CAP)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
		ecp->s_so_cap = _INIT_SYMOFF_CAP;
		ecp->s_cnt = 0;
	}

	if (ecp->s_sn == NULL) {
		if ((ecp->s_sn = malloc(_INIT_SYMNAME_CAP)) == NULL)
			err(EXIT_FAILURE, "malloc failed");
		ecp->s_sn_cap = _INIT_SYMNAME_CAP;
		ecp->s_sn_sz = 0;
	}

	if (ecp->s_cnt * sizeof(uint32_t) >= ecp->s_so_cap) {
		ecp->s_so_cap *= 2;
		ecp->s_so = realloc(ecp->s_so, ecp->s_so_cap);
		if (ecp->s_so == NULL)
			err(EXIT_FAILURE, "realloc failed");
	}
	ecp->s_so[ecp->s_cnt] = ecp->rela_off;
	ecp->s_cnt++;

	/*
	 * The space required for holding one symbol name in sn table includes:
	 * strlen(name) + (1 for '\n') + (possibly 1 for padding).
	 */
	while (ecp->s_sn_sz + strlen(name) + 2 > ecp->s_sn_cap) {
		ecp->s_sn_cap *= 2;
		ecp->s_sn = realloc(ecp->s_sn, ecp->s_sn_cap);
		if (ecp->s_sn == NULL)
			err(EXIT_FAILURE, "realloc failed");
	}
	strncpy(&ecp->s_sn[ecp->s_sn_sz], name, strlen(name));
	ecp->s_sn_sz += strlen(name);
	ecp->s_sn[ecp->s_sn_sz++] = '\0';
}