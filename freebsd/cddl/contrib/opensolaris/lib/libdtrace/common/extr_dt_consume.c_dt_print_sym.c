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
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_3__ {char* dts_object; char* dts_name; } ;
typedef  TYPE_1__ dtrace_syminfo_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  scalar_t__ caddr_t ;
typedef  int /*<<< orphan*/  c ;
typedef  int /*<<< orphan*/  GElf_Sym ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int PATH_MAX ; 
 scalar_t__ dt_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char*) ; 
 scalar_t__ dtrace_lookup_by_addr (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,...) ; 

__attribute__((used)) static int
dt_print_sym(dtrace_hdl_t *dtp, FILE *fp, const char *format, caddr_t addr)
{
	/* LINTED - alignment */
	uint64_t pc = *((uint64_t *)addr);
	dtrace_syminfo_t dts;
	GElf_Sym sym;
	char c[PATH_MAX * 2];

	if (format == NULL)
		format = "  %-50s";

	if (dtrace_lookup_by_addr(dtp, pc, &sym, &dts) == 0) {
		(void) snprintf(c, sizeof (c), "%s`%s",
		    dts.dts_object, dts.dts_name);
	} else {
		/*
		 * We'll repeat the lookup, but this time we'll specify a
		 * NULL GElf_Sym -- indicating that we're only interested in
		 * the containing module.
		 */
		if (dtrace_lookup_by_addr(dtp, pc, NULL, &dts) == 0) {
			(void) snprintf(c, sizeof (c), "%s`0x%llx",
			    dts.dts_object, (u_longlong_t)pc);
		} else {
			(void) snprintf(c, sizeof (c), "0x%llx",
			    (u_longlong_t)pc);
		}
	}

	if (dt_printf(dtp, fp, format, c) < 0)
		return (-1);

	return (0);
}