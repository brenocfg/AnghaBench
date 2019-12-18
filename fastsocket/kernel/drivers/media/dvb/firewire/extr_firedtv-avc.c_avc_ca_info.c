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
struct firedtv {int subunit; int avc_data_length; int /*<<< orphan*/  avc_mutex; scalar_t__ avc_data; } ;
struct avc_response_frame {char* operand; } ;
struct avc_command_frame {int subunit; scalar_t__* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_CTYPE_STATUS ; 
 int /*<<< orphan*/  AVC_OPCODE_VENDOR ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int EN50221_TAG_CA_INFO ; 
 int /*<<< orphan*/  LAST_OPERAND ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_0 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_1 ; 
 scalar_t__ SFE_VENDOR_DE_COMPANYID_2 ; 
 scalar_t__ SFE_VENDOR_OPCODE_CA2HOST ; 
 scalar_t__ SFE_VENDOR_TAG_CA_APPLICATION_INFO ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int /*<<< orphan*/ ) ; 
 int* fake_ca_system_ids ; 
 int get_ca_object_pos (struct avc_response_frame*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int num_fake_ca_system_ids ; 

int avc_ca_info(struct firedtv *fdtv, char *app_info, unsigned int *len)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int i, pos, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_STATUS;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_VENDOR;

	c->operand[0] = SFE_VENDOR_DE_COMPANYID_0;
	c->operand[1] = SFE_VENDOR_DE_COMPANYID_1;
	c->operand[2] = SFE_VENDOR_DE_COMPANYID_2;
	c->operand[3] = SFE_VENDOR_OPCODE_CA2HOST;
	c->operand[4] = 0; /* slot */
	c->operand[5] = SFE_VENDOR_TAG_CA_APPLICATION_INFO; /* ca tag */
	clear_operands(c, 6, LAST_OPERAND);

	fdtv->avc_data_length = 12;
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	/* FIXME: check response code and validate response data */

	pos = get_ca_object_pos(r);
	app_info[0] = (EN50221_TAG_CA_INFO >> 16) & 0xff;
	app_info[1] = (EN50221_TAG_CA_INFO >>  8) & 0xff;
	app_info[2] = (EN50221_TAG_CA_INFO >>  0) & 0xff;
	if (num_fake_ca_system_ids == 0) {
		app_info[3] = 2;
		app_info[4] = r->operand[pos + 0];
		app_info[5] = r->operand[pos + 1];
	} else {
		app_info[3] = num_fake_ca_system_ids * 2;
		for (i = 0; i < num_fake_ca_system_ids; i++) {
			app_info[4 + i * 2] =
				(fake_ca_system_ids[i] >> 8) & 0xff;
			app_info[5 + i * 2] = fake_ca_system_ids[i] & 0xff;
		}
	}
	*len = app_info[3] + 4;
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}