#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  sg_addr; int /*<<< orphan*/  command_id; void* op_code; } ;
struct TYPE_15__ {TYPE_1__ basic_io; } ;
struct TYPE_16__ {int data_len; int basic_status; TYPE_2__ cmd; void** cdb; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_3__ ips_scb_t ;
struct TYPE_17__ {int max_cmds; int /*<<< orphan*/  ioctl_data; TYPE_5__* conf; int /*<<< orphan*/  ioctl_busaddr; TYPE_3__* scbs; } ;
typedef  TYPE_4__ ips_ha_t ;
struct TYPE_18__ {int* init_id; } ;
typedef  int /*<<< orphan*/  IPS_CONF ;

/* Variables and functions */
 int IPS_CMD_CMPLT_WERROR ; 
 void* IPS_CMD_READ_CONF ; 
 int /*<<< orphan*/  IPS_COMMAND_ID (TYPE_4__*,TYPE_3__*) ; 
 int IPS_FAILURE ; 
 int IPS_GSC_STATUS_MASK ; 
 int IPS_SUCCESS_IMM ; 
 int /*<<< orphan*/  METHOD_TRACE (char*,int) ; 
 int /*<<< orphan*/  ips_cmd_timeout ; 
 int /*<<< orphan*/  ips_init_scb (TYPE_4__*,TYPE_3__*) ; 
 int ips_send_wait (TYPE_4__*,TYPE_3__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (TYPE_5__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (TYPE_5__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
ips_read_config(ips_ha_t * ha, int intr)
{
	ips_scb_t *scb;
	int i;
	int ret;

	METHOD_TRACE("ips_read_config", 1);

	/* set defaults for initiator IDs */
	for (i = 0; i < 4; i++)
		ha->conf->init_id[i] = 7;

	scb = &ha->scbs[ha->max_cmds - 1];

	ips_init_scb(ha, scb);

	scb->timeout = ips_cmd_timeout;
	scb->cdb[0] = IPS_CMD_READ_CONF;

	scb->cmd.basic_io.op_code = IPS_CMD_READ_CONF;
	scb->cmd.basic_io.command_id = IPS_COMMAND_ID(ha, scb);
	scb->data_len = sizeof (*ha->conf);
	scb->cmd.basic_io.sg_addr = ha->ioctl_busaddr;

	/* send command */
	if (((ret =
	      ips_send_wait(ha, scb, ips_cmd_timeout, intr)) == IPS_FAILURE)
	    || (ret == IPS_SUCCESS_IMM)
	    || ((scb->basic_status & IPS_GSC_STATUS_MASK) > 1)) {

		memset(ha->conf, 0, sizeof (IPS_CONF));

		/* reset initiator IDs */
		for (i = 0; i < 4; i++)
			ha->conf->init_id[i] = 7;

		/* Allow Completed with Errors, so JCRM can access the Adapter to fix the problems */
		if ((scb->basic_status & IPS_GSC_STATUS_MASK) ==
		    IPS_CMD_CMPLT_WERROR)
			return (1);

		return (0);
	}

	memcpy(ha->conf, ha->ioctl_data, sizeof(*ha->conf));
	return (1);
}