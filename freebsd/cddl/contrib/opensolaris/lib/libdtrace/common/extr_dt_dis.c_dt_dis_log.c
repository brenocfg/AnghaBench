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
typedef  int /*<<< orphan*/  dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DIF_INSTR_R1 (int /*<<< orphan*/ ) ; 
 int DIF_INSTR_R2 (int /*<<< orphan*/ ) ; 
 int DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,int,int,int) ; 

__attribute__((used)) static void
dt_dis_log(const dtrace_difo_t *dp, const char *name, dif_instr_t in, FILE *fp)
{
	(void) fprintf(fp, "%-4s %%r%u, %%r%u, %%r%u", name,
	    DIF_INSTR_R1(in), DIF_INSTR_R2(in), DIF_INSTR_RD(in));
}