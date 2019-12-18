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
typedef  scalar_t__ uint64_t ;
typedef  char* u_longlong_t ;
struct TYPE_3__ {char* dts_object; } ;
typedef  TYPE_1__ dtrace_syminfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ dtrace_lookup_by_addr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*) ; 

int
dt_print_mod(dtrace_hdl_t *dtp, FILE *fp, const char *format, caddr_t addr)
{
	/* LINTED - alignment */
	uint64_t pc = *((uint64_t *)addr);
	dtrace_syminfo_t dts;
	char c[PATH_MAX * 2];

	if (format == NULL)
		format = "  %-50s";

	if (dtrace_lookup_by_addr(dtp, pc, NULL, &dts) == 0) {
		(void) snprintf(c, sizeof (c), "%s", dts.dts_object);
	} else {
		(void) snprintf(c, sizeof (c), "0x%llx", (u_longlong_t)pc);
	}

	if (dt_printf(dtp, fp, format, c) < 0)
		return (-1);

	return (0);
}