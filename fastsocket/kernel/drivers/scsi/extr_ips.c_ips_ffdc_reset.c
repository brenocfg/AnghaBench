#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int reset_type; int /*<<< orphan*/  reset_count; int /*<<< orphan*/  command_id; void* op_code; } ;
struct TYPE_15__ {TYPE_1__ ffdc; } ;
struct TYPE_16__ {TYPE_2__ cmd; void** cdb; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ ips_scb_t ;
struct TYPE_17__ {int max_cmds; int /*<<< orphan*/  last_ffdc; int /*<<< orphan*/  reset_count; TYPE_3__* scbs; } ;
typedef  TYPE_4__ ips_ha_t ;

/* Variables and functions */
 void* IPS_CMD_FFDC ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_fix_ffdc_time (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ips_send_wait (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
ips_ffdc_reset(ips_ha_t * ha, int intr)
{
	ips_scb_t *scb;

	METHOD_TRACE("ips_ffdc_reset", 1);

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->timeout = ips_cmd_timeout;
	scb->cdb[0] = IPS_CMD_FFDC;
	scb->cmd.ffdc.op_code = IPS_CMD_FFDC;
	scb->cmd.ffdc.command_id = IPS_COMMAND_ID(ha, scb);
	scb->cmd.ffdc.reset_count = ha->reset_count;
	scb->cmd.ffdc.reset_type = 0x80;

	/* convert time to what the card wants */
	ips_fix_ffdc_time(ha, scb, ha->last_ffdc);

	/* issue command */
	ips_send_wait(ha, scb, ips_cmd_timeout, intr);
}