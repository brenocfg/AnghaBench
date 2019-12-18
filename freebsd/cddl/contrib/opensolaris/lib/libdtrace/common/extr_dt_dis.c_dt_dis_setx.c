#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int uint_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_3__ {int dtdo_intlen; scalar_t__* dtdo_inttab; } ;
typedef  TYPE_1__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DIF_INSTR_INTEGER (int /*<<< orphan*/ ) ; 
 int DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static void
dt_dis_setx(const dtrace_difo_t *dp, const char *name, dif_instr_t in, FILE *fp)
{
	uint_t intptr = DIF_INSTR_INTEGER(in);

	(void) fprintf(fp, "%-4s DT_INTEGER[%u], %%r%u", name,
	    intptr, DIF_INSTR_RD(in));

	if (intptr < dp->dtdo_intlen) {
		(void) fprintf(fp, "\t\t! 0x%llx",
		    (u_longlong_t)dp->dtdo_inttab[intptr]);
	}
}