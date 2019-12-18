#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct firedtv {int subunit; scalar_t__ type; int avc_data_length; int /*<<< orphan*/  avc_mutex; scalar_t__ avc_data; } ;
struct avc_command_frame {int subunit; int* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_CTYPE_CONTROL ; 
 int /*<<< orphan*/  AVC_OPCODE_DSIT ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 scalar_t__ FIREDTV_DVB_T ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int avc_tuner_get_ts(struct firedtv *fdtv)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	int ret, sl;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_DSIT;

	sl = fdtv->type == FIREDTV_DVB_T ? 0x0c : 0x11;

	c->operand[0] = 0;	/* source plug */
	c->operand[1] = 0xd2;	/* subfunction replace */
	c->operand[2] = 0xff;	/* status */
	c->operand[3] = 0x20;	/* system id = DVB */
	c->operand[4] = 0x00;	/* antenna number */
	c->operand[5] = 0x0; 	/* system_specific_search_flags */
	c->operand[6] = sl;	/* system_specific_multiplex selection_length */
	/*
	 * operand[7]: valid_flags[0]
	 * operand[8]: valid_flags[1]
	 * operand[7 + sl]: nr_of_dsit_sel_specs (always 0)
	 */
	clear_operands(c, 7, 24);

	fdtv->avc_data_length = fdtv->type == FIREDTV_DVB_T ? 24 : 28;
	ret = avc_write(fdtv);

	/* FIXME: check response code? */

	mutex_unlock(&fdtv->avc_mutex);

	if (ret == 0)
		msleep(250);

	return ret;
}