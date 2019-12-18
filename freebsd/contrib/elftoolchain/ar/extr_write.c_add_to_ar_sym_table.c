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
struct bsdar {char* s_so; int s_so_cap; int s_cnt; char* s_sn; int s_sn_cap; size_t s_sn_sz; char rela_off; } ;

/* Variables and functions */
 void* _INIT_SYMNAME_CAP ; 
 void* _INIT_SYMOFF_CAP ; 
 int /*<<< orphan*/  bsdar_errc (struct bsdar*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 void* malloc (void*) ; 
 void* realloc (char*,int) ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

__attribute__((used)) static void
add_to_ar_sym_table(struct bsdar *bsdar, const char *name)
{

	if (bsdar->s_so == NULL) {
		if ((bsdar->s_so = malloc(_INIT_SYMOFF_CAP)) ==
		    NULL)
			bsdar_errc(bsdar, errno, "malloc failed");
		bsdar->s_so_cap = _INIT_SYMOFF_CAP;
		bsdar->s_cnt = 0;
	}

	if (bsdar->s_sn == NULL) {
		if ((bsdar->s_sn = malloc(_INIT_SYMNAME_CAP)) == NULL)
			bsdar_errc(bsdar, errno, "malloc failed");
		bsdar->s_sn_cap = _INIT_SYMNAME_CAP;
		bsdar->s_sn_sz = 0;
	}

	if (bsdar->s_cnt * sizeof(uint32_t) >= bsdar->s_so_cap) {
		bsdar->s_so_cap *= 2;
		bsdar->s_so = realloc(bsdar->s_so, bsdar->s_so_cap);
		if (bsdar->s_so == NULL)
			bsdar_errc(bsdar, errno, "realloc failed");
	}
	bsdar->s_so[bsdar->s_cnt] = bsdar->rela_off;
	bsdar->s_cnt++;

	/*
	 * The space required for holding one symbol name in the 'sn'
	 * table includes: strlen(name) + (1 for '\n') + (possibly 1
	 * for padding).
	 */
	while (bsdar->s_sn_sz + strlen(name) + 2 > bsdar->s_sn_cap) {
		bsdar->s_sn_cap *= 2;
		bsdar->s_sn = realloc(bsdar->s_sn, bsdar->s_sn_cap);
		if (bsdar->s_sn == NULL)
			bsdar_errc(bsdar, errno, "realloc failed");
	}
	strncpy(&bsdar->s_sn[bsdar->s_sn_sz], name, strlen(name));
	bsdar->s_sn_sz += strlen(name);
	bsdar->s_sn[bsdar->s_sn_sz++] = '\0';
}