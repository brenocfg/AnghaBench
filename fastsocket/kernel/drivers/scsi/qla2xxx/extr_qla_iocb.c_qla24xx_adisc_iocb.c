#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct logio_entry_24xx {int /*<<< orphan*/  vp_index; void* nport_handle; void* control_flags; int /*<<< orphan*/  entry_type; } ;
struct TYPE_7__ {TYPE_2__* fcport; } ;
typedef  TYPE_3__ srb_t ;
struct TYPE_6__ {TYPE_1__* vha; int /*<<< orphan*/  loop_id; } ;
struct TYPE_5__ {int /*<<< orphan*/  vp_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  LCF_COMMAND_ADISC ; 
 int /*<<< orphan*/  LOGINOUT_PORT_IOCB_TYPE ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
qla24xx_adisc_iocb(srb_t *sp, struct logio_entry_24xx *logio)
{
	logio->entry_type = LOGINOUT_PORT_IOCB_TYPE;
	logio->control_flags = cpu_to_le16(LCF_COMMAND_ADISC);
	logio->nport_handle = cpu_to_le16(sp->fcport->loop_id);
	logio->vp_index = sp->fcport->vha->vp_idx;
}