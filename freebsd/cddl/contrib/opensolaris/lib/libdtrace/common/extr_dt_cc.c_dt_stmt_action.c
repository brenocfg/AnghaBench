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
typedef  int /*<<< orphan*/  dtrace_stmtdesc_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
typedef  int /*<<< orphan*/  dtrace_actdesc_t ;
struct TYPE_2__ {int /*<<< orphan*/  pcb_jmpbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  EDT_NOMEM ; 
 int /*<<< orphan*/ * dtrace_stmt_action (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* yypcb ; 

__attribute__((used)) static dtrace_actdesc_t *
dt_stmt_action(dtrace_hdl_t *dtp, dtrace_stmtdesc_t *sdp)
{
	dtrace_actdesc_t *new;

	if ((new = dtrace_stmt_action(dtp, sdp)) == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	return (new);
}