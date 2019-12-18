#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  scalar_t__ ctf_id_t ;
typedef  int /*<<< orphan*/  ctf_file_t ;
struct TYPE_2__ {int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/ * DT_DYN_CTFP (int /*<<< orphan*/ *) ; 
 scalar_t__ DT_DYN_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DT_FPTR_CTFP (int /*<<< orphan*/ *) ; 
 scalar_t__ DT_FPTR_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * DT_FUNC_CTFP (int /*<<< orphan*/ *) ; 
 scalar_t__ DT_FUNC_TYPE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ctf_type_name (int /*<<< orphan*/ *,scalar_t__,char*,size_t) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*) ; 
 TYPE_1__* yypcb ; 

const char *
dt_type_name(ctf_file_t *ctfp, ctf_id_t type, char *buf, size_t len)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;

	if (ctfp == DT_FPTR_CTFP(dtp) && type == DT_FPTR_TYPE(dtp))
		(void) snprintf(buf, len, "function pointer");
	else if (ctfp == DT_FUNC_CTFP(dtp) && type == DT_FUNC_TYPE(dtp))
		(void) snprintf(buf, len, "function");
	else if (ctfp == DT_DYN_CTFP(dtp) && type == DT_DYN_TYPE(dtp))
		(void) snprintf(buf, len, "dynamic variable");
	else if (ctfp == NULL)
		(void) snprintf(buf, len, "<none>");
	else if (ctf_type_name(ctfp, type, buf, len) == NULL)
		(void) snprintf(buf, len, "unknown");

	return (buf);
}