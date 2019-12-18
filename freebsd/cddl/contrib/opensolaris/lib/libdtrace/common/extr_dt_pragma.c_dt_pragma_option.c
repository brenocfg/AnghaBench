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
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_4__ {scalar_t__ dn_kind; int /*<<< orphan*/  dn_string; int /*<<< orphan*/ * dn_list; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_5__ {int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 scalar_t__ DT_NODE_IDENT ; 
 int /*<<< orphan*/  D_PRAGMA_MALFORM ; 
 int /*<<< orphan*/  D_PRAGMA_OPTSET ; 
 char* alloca (scalar_t__) ; 
 int /*<<< orphan*/  dtrace_errmsg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dtrace_errno (int /*<<< orphan*/ *) ; 
 int dtrace_setopt (int /*<<< orphan*/ *,char*,char*) ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strcpy (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const*,...) ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static void
dt_pragma_option(const char *prname, dt_node_t *dnp)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	char *opt, *val;

	if (dnp == NULL || dnp->dn_kind != DT_NODE_IDENT) {
		xyerror(D_PRAGMA_MALFORM,
		    "malformed #pragma %s <option>=<val>\n", prname);
	}

	if (dnp->dn_list != NULL) {
		xyerror(D_PRAGMA_MALFORM,
		    "superfluous arguments specified for #pragma %s\n", prname);
	}

	opt = alloca(strlen(dnp->dn_string) + 1);
	(void) strcpy(opt, dnp->dn_string);

	if ((val = strchr(opt, '=')) != NULL)
		*val++ = '\0';

	if (dtrace_setopt(dtp, opt, val) == -1) {
		if (val == NULL) {
			xyerror(D_PRAGMA_OPTSET,
			    "failed to set option '%s': %s\n", opt,
			    dtrace_errmsg(dtp, dtrace_errno(dtp)));
		} else {
			xyerror(D_PRAGMA_OPTSET,
			    "failed to set option '%s' to '%s': %s\n",
			    opt, val, dtrace_errmsg(dtp, dtrace_errno(dtp)));
		}
	}
}