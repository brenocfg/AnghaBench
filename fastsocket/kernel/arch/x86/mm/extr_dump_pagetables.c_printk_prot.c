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
typedef  int pgprotval_t ;
typedef  int /*<<< orphan*/  pgprot_t ;

/* Variables and functions */
 int _PAGE_GLOBAL ; 
 int _PAGE_NX ; 
 int _PAGE_PAT ; 
 int _PAGE_PCD ; 
 int _PAGE_PSE ; 
 int _PAGE_PWT ; 
 int _PAGE_RW ; 
 int _PAGE_USER ; 
 int pgprot_val (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,...) ; 

__attribute__((used)) static void printk_prot(struct seq_file *m, pgprot_t prot, int level)
{
	pgprotval_t pr = pgprot_val(prot);
	static const char * const level_name[] =
		{ "cr3", "pgd", "pud", "pmd", "pte" };

	if (!pgprot_val(prot)) {
		/* Not present */
		seq_printf(m, "                          ");
	} else {
		if (pr & _PAGE_USER)
			seq_printf(m, "USR ");
		else
			seq_printf(m, "    ");
		if (pr & _PAGE_RW)
			seq_printf(m, "RW ");
		else
			seq_printf(m, "ro ");
		if (pr & _PAGE_PWT)
			seq_printf(m, "PWT ");
		else
			seq_printf(m, "    ");
		if (pr & _PAGE_PCD)
			seq_printf(m, "PCD ");
		else
			seq_printf(m, "    ");

		/* Bit 9 has a different meaning on level 3 vs 4 */
		if (level <= 3) {
			if (pr & _PAGE_PSE)
				seq_printf(m, "PSE ");
			else
				seq_printf(m, "    ");
		} else {
			if (pr & _PAGE_PAT)
				seq_printf(m, "pat ");
			else
				seq_printf(m, "    ");
		}
		if (pr & _PAGE_GLOBAL)
			seq_printf(m, "GLB ");
		else
			seq_printf(m, "    ");
		if (pr & _PAGE_NX)
			seq_printf(m, "NX ");
		else
			seq_printf(m, "x  ");
	}
	seq_printf(m, "%s\n", level_name[level]);
}