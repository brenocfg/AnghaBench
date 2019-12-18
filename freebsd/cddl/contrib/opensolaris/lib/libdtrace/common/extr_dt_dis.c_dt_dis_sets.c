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
struct TYPE_3__ {int dtdo_strlen; char* dtdo_strtab; } ;
typedef  TYPE_1__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int DIF_INSTR_RD (int /*<<< orphan*/ ) ; 
 int DIF_INSTR_STRING (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char const*,...) ; 

__attribute__((used)) static void
dt_dis_sets(const dtrace_difo_t *dp, const char *name, dif_instr_t in, FILE *fp)
{
	uint_t strptr = DIF_INSTR_STRING(in);

	(void) fprintf(fp, "%-4s DT_STRING[%u], %%r%u", name,
	    strptr, DIF_INSTR_RD(in));

	if (strptr < dp->dtdo_strlen)
		(void) fprintf(fp, "\t\t! \"%s\"", dp->dtdo_strtab + strptr);
}