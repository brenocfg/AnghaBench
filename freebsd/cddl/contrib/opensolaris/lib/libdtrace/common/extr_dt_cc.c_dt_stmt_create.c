#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* dtsd_stmtattr; void* dtsd_descattr; } ;
typedef  TYPE_1__ dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_ecbdesc_t ;
typedef  void* dtrace_attribute_t ;
struct TYPE_6__ {TYPE_1__* pcb_stmt; int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* dtrace_stmt_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* yypcb ; 

__attribute__((used)) static dtrace_stmtdesc_t *
dt_stmt_create(dtrace_hdl_t *dtp, dtrace_ecbdesc_t *edp,
    dtrace_attribute_t descattr, dtrace_attribute_t stmtattr)
{
	dtrace_stmtdesc_t *sdp = dtrace_stmt_create(dtp, edp);

	if (sdp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	assert(yypcb->pcb_stmt == NULL);
	yypcb->pcb_stmt = sdp;

	sdp->dtsd_descattr = descattr;
	sdp->dtsd_stmtattr = stmtattr;

	return (sdp);
}