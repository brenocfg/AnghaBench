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
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void asm_emit_endnode(void *e, const char *label)
{
	FILE *f = e;

	fprintf(f, "\t.long\tFDT_END_NODE\n");
	if (label) {
		fprintf(f, "\t.globl\t%s_end\n", label);
		fprintf(f, "%s_end:\n", label);
	}
}