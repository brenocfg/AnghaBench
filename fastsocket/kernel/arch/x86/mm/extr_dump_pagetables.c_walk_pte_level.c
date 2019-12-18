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
struct pg_state {int /*<<< orphan*/  current_address; } ;
typedef  int /*<<< orphan*/  pte_t ;
typedef  int /*<<< orphan*/  pmd_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int PTE_LEVEL_MULT ; 
 int PTRS_PER_PTE ; 
 int /*<<< orphan*/  normalize_addr (unsigned long) ; 
 int /*<<< orphan*/  note_page (struct seq_file*,struct pg_state*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ pmd_page_vaddr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pte_pgprot (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void walk_pte_level(struct seq_file *m, struct pg_state *st, pmd_t addr,
							unsigned long P)
{
	int i;
	pte_t *start;

	start = (pte_t *) pmd_page_vaddr(addr);
	for (i = 0; i < PTRS_PER_PTE; i++) {
		pgprot_t prot = pte_pgprot(*start);

		st->current_address = normalize_addr(P + i * PTE_LEVEL_MULT);
		note_page(m, st, prot, 4);
		start++;
	}
}