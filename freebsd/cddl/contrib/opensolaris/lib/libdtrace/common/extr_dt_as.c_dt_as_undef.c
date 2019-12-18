#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
struct TYPE_4__ {int /*<<< orphan*/  dts_name; int /*<<< orphan*/  dts_object; } ;
typedef  TYPE_1__ dtrace_syminfo_t ;
struct TYPE_5__ {int di_flags; int /*<<< orphan*/  di_lineno; TYPE_1__* di_data; } ;
typedef  TYPE_2__ dt_ident_t ;

/* Variables and functions */
 int DT_IDFLG_PRIM ; 
 int DT_IDFLG_USER ; 
 int /*<<< orphan*/  D_ASRELO ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yylineno ; 

__attribute__((used)) static void
dt_as_undef(const dt_ident_t *idp, uint_t offset)
{
	const char *kind, *mark = (idp->di_flags & DT_IDFLG_USER) ? "``" : "`";
	const dtrace_syminfo_t *dts = idp->di_data;

	if (idp->di_flags & DT_IDFLG_USER)
		kind = "user";
	else if (idp->di_flags & DT_IDFLG_PRIM)
		kind = "primary kernel";
	else
		kind = "loadable kernel";

	yylineno = idp->di_lineno;

	xyerror(D_ASRELO, "relocation remains against %s symbol %s%s%s (offset "
	    "0x%x)\n", kind, dts->dts_object, mark, dts->dts_name, offset);
}