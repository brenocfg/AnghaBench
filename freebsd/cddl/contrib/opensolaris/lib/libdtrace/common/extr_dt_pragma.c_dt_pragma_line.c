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
struct TYPE_4__ {scalar_t__ dn_kind; int dn_value; int /*<<< orphan*/ * dn_string; struct TYPE_4__* dn_list; } ;
typedef  TYPE_1__ dt_node_t ;
struct TYPE_5__ {scalar_t__ pcb_idepth; int /*<<< orphan*/ * pcb_filetag; } ;

/* Variables and functions */
 scalar_t__ DT_NODE_INT ; 
 scalar_t__ DT_NODE_STRING ; 
 int /*<<< orphan*/  D_PRAGMA_MALFORM ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  xyerror (int /*<<< orphan*/ ,char*,char const*) ; 
 int yylineno ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static void
dt_pragma_line(const char *prname, dt_node_t *dnp)
{
	dt_node_t *fnp = dnp ? dnp->dn_list : NULL;
	dt_node_t *inp = fnp ? fnp->dn_list : NULL;

	if ((dnp == NULL || dnp->dn_kind != DT_NODE_INT) ||
	    (fnp != NULL && fnp->dn_kind != DT_NODE_STRING) ||
	    (inp != NULL && inp->dn_kind != DT_NODE_INT)) {
		xyerror(D_PRAGMA_MALFORM, "malformed #%s "
		    "<line> [ [\"file\"] state ]\n", prname);
	}

	/*
	 * If a file is specified, free any old pcb_filetag and swap fnp's
	 * dn_string into pcb_filetag as the new filename for error messages.
	 */
	if (fnp != NULL) {
		if (yypcb->pcb_filetag != NULL)
			free(yypcb->pcb_filetag);

		/*
		 * This is not pretty, but is a necessary evil until we either
		 * write "dpp" or get a useful standalone cpp from DevPro.  If
		 * the filename begins with /dev/fd, we know it's the master
		 * input file (see dt_preproc() in dt_cc.c), so just clear the
		 * dt_filetag pointer so error messages refer to the main file.
		 */
		if (strncmp(fnp->dn_string, "/dev/fd/", 8) != 0) {
			yypcb->pcb_filetag = fnp->dn_string;
			fnp->dn_string = NULL;
		} else
			yypcb->pcb_filetag = NULL;
	}

	if (inp != NULL) {
		if (inp->dn_value == 1)
			yypcb->pcb_idepth++;
		else if (inp->dn_value == 2 && yypcb->pcb_idepth != 0)
			yypcb->pcb_idepth--;
	}

	yylineno = dnp->dn_value;
}