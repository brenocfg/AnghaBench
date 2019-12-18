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
typedef  int uint_t ;
typedef  int /*<<< orphan*/  dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 int DIF_INSTR_VAR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dt_dis_scope (char const*) ; 
 char* dt_dis_varname (int /*<<< orphan*/  const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static void
dt_dis_ldv(const dtrace_difo_t *dp, const char *name, dif_instr_t in, FILE *fp)
{
	uint_t var = DIF_INSTR_VAR(in);
	const char *vname;

	(void) fprintf(fp, "%-4s DT_VAR(%u), %%r%u",
	    name, var, DIF_INSTR_RD(in));

	if ((vname = dt_dis_varname(dp, var, dt_dis_scope(name))) != NULL)
		(void) fprintf(fp, "\t\t! DT_VAR(%u) = \"%s\"", var, vname);
}