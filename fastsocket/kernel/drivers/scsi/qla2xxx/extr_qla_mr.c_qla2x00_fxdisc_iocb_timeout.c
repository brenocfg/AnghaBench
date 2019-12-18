#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  fxiocb_comp; } ;
struct TYPE_7__ {TYPE_2__ fxiocb; } ;
struct srb_iocb {TYPE_3__ u; } ;
struct TYPE_5__ {struct srb_iocb iocb_cmd; } ;
struct TYPE_8__ {TYPE_1__ u; } ;
typedef  TYPE_4__ srb_t ;

/* Variables and functions */
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
qla2x00_fxdisc_iocb_timeout(void *data)
{
	srb_t *sp = (srb_t *)data;
	struct srb_iocb *lio = &sp->u.iocb_cmd;

	complete(&lio->u.fxiocb.fxiocb_comp);
}