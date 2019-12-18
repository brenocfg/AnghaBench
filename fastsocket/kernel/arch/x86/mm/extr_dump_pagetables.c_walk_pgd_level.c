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
struct seq_file {int dummy; } ;
struct pg_state {void* current_address; } ;
typedef  int /*<<< orphan*/  st ;
typedef  int pgprotval_t ;
typedef  int /*<<< orphan*/  pgd_t ;

/* Variables and functions */
 int PGD_LEVEL_MULT ; 
 int PTE_FLAGS_MASK ; 
 int PTRS_PER_PGD ; 
 int /*<<< orphan*/  __pgprot (int) ; 
 int /*<<< orphan*/  init_level4_pgt ; 
 int /*<<< orphan*/  memset (struct pg_state*,int /*<<< orphan*/ ,int) ; 
 void* normalize_addr (int) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pgd_large (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_none (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pgd_present (int /*<<< orphan*/ ) ; 
 int pgd_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * swapper_pg_dir ; 
 int /*<<< orphan*/  walk_pud_level (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void walk_pgd_level(struct seq_file *m)
{
#ifdef CONFIG_X86_64
	pgd_t *start = (pgd_t *) &init_level4_pgt;
#else
	pgd_t *start = swapper_pg_dir;
#endif
	int i;
	struct pg_state st;

	memset(&st, 0, sizeof(st));

	for (i = 0; i < PTRS_PER_PGD; i++) {
		st.current_address = normalize_addr(i * PGD_LEVEL_MULT);
		if (!pgd_none(*start)) {
			pgprotval_t prot = pgd_val(*start) & PTE_FLAGS_MASK;

			if (pgd_large(*start) || !pgd_present(*start))
				note_page(m, &st, __pgprot(prot), 1);
			else
				walk_pud_level(m, &st, *start,
					       i * PGD_LEVEL_MULT);
		} else
			note_page(m, &st, __pgprot(0), 1);

		start++;
	}

	/* Flush out the last page */
	st.current_address = normalize_addr(PTRS_PER_PGD*PGD_LEVEL_MULT);
	note_page(m, &st, __pgprot(0), 0);
}