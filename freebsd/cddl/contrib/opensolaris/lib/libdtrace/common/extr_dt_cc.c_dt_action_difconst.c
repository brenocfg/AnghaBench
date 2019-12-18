#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dtrace_hdl_t ;
struct TYPE_7__ {int dtdo_len; int dtdo_intlen; int /*<<< orphan*/  dtdo_rtype; int /*<<< orphan*/ * dtdo_inttab; int /*<<< orphan*/ * dtdo_buf; } ;
typedef  TYPE_1__ dtrace_difo_t ;
typedef  int /*<<< orphan*/  dtrace_actkind_t ;
struct TYPE_8__ {int /*<<< orphan*/  dtad_kind; TYPE_1__* dtad_difo; } ;
typedef  TYPE_2__ dtrace_actdesc_t ;
typedef  int /*<<< orphan*/  dif_instr_t ;
struct TYPE_9__ {int /*<<< orphan*/  pcb_jmpbuf; int /*<<< orphan*/ * pcb_hdl; } ;

/* Variables and functions */
 int /*<<< orphan*/  DIF_INSTR_RET (int) ; 
 int /*<<< orphan*/  DIF_INSTR_SETX (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  EDT_NOMEM ; 
 void* dt_alloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dt_difo_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dt_int_rtype ; 
 TYPE_1__* dt_zalloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  longjmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* yypcb ; 

__attribute__((used)) static void
dt_action_difconst(dtrace_actdesc_t *ap, uint_t id, dtrace_actkind_t kind)
{
	dtrace_hdl_t *dtp = yypcb->pcb_hdl;
	dtrace_difo_t *dp = dt_zalloc(dtp, sizeof (dtrace_difo_t));

	if (dp == NULL)
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);

	dp->dtdo_buf = dt_alloc(dtp, sizeof (dif_instr_t) * 2);
	dp->dtdo_inttab = dt_alloc(dtp, sizeof (uint64_t));

	if (dp->dtdo_buf == NULL || dp->dtdo_inttab == NULL) {
		dt_difo_free(dtp, dp);
		longjmp(yypcb->pcb_jmpbuf, EDT_NOMEM);
	}

	dp->dtdo_buf[0] = DIF_INSTR_SETX(0, 1); /* setx	DIF_INTEGER[0], %r1 */
	dp->dtdo_buf[1] = DIF_INSTR_RET(1);	/* ret	%r1 */
	dp->dtdo_len = 2;
	dp->dtdo_inttab[0] = id;
	dp->dtdo_intlen = 1;
	dp->dtdo_rtype = dt_int_rtype;

	ap->dtad_difo = dp;
	ap->dtad_kind = kind;
}