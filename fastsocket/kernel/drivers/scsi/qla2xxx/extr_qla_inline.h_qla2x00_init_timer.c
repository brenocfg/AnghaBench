#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_9__ ;
typedef  struct TYPE_17__   TYPE_7__ ;
typedef  struct TYPE_16__   TYPE_6__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  fxiocb_comp; } ;
struct TYPE_14__ {TYPE_3__ fxiocb; } ;
struct TYPE_18__ {unsigned long data; int /*<<< orphan*/  function; scalar_t__ expires; } ;
struct TYPE_15__ {TYPE_4__ u; TYPE_9__ timer; } ;
struct TYPE_16__ {TYPE_5__ iocb_cmd; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_6__ u; TYPE_2__* fcport; int /*<<< orphan*/  free; } ;
typedef  TYPE_7__ srb_t ;
struct TYPE_12__ {TYPE_1__* vha; } ;
struct TYPE_11__ {int /*<<< orphan*/  hw; } ;

/* Variables and functions */
 unsigned long HZ ; 
 scalar_t__ IS_QLAFX00 (int /*<<< orphan*/ ) ; 
 scalar_t__ SRB_FXIOCB_DCMD ; 
 int /*<<< orphan*/  add_timer (TYPE_9__*) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_timer (TYPE_9__*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  qla2x00_sp_free ; 
 int /*<<< orphan*/  qla2x00_sp_timeout ; 

__attribute__((used)) static inline void
qla2x00_init_timer(srb_t *sp, unsigned long tmo)
{
	init_timer(&sp->u.iocb_cmd.timer);
	sp->u.iocb_cmd.timer.expires = jiffies + tmo * HZ;
	sp->u.iocb_cmd.timer.data = (unsigned long)sp;
	sp->u.iocb_cmd.timer.function = qla2x00_sp_timeout;
	add_timer(&sp->u.iocb_cmd.timer);
	sp->free = qla2x00_sp_free;
	if ((IS_QLAFX00(sp->fcport->vha->hw)) &&
	    (sp->type == SRB_FXIOCB_DCMD))
		init_completion(&sp->u.iocb_cmd.u.fxiocb.fxiocb_comp);
}