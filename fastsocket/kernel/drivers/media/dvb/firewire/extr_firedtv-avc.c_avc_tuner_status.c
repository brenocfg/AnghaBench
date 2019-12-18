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
struct firedtv_tuner_status {int active_system; int searching; int moving; int no_rf; int input; int selected_antenna; int ber; int signal_strength; int raster_frequency; int rf_frequency; int man_dep_info_length; int front_end_error; int antenna_error; int front_end_power_status; int power_supply; int carrier_noise_ratio; int power_supply_voltage; int antenna_voltage; int firewire_bus_voltage; int ca_mmi; int ca_pmt_reply; int ca_date_time_request; int ca_application_info; int ca_module_present_status; int ca_dvb_flag; int ca_error_flag; int ca_initialization_status; } ;
struct firedtv {int subunit; int avc_data_length; int /*<<< orphan*/  avc_mutex; int /*<<< orphan*/  device; scalar_t__ avc_data; } ;
struct avc_response_frame {scalar_t__ response; int* operand; } ;
struct avc_command_frame {int subunit; int* operand; int /*<<< orphan*/  opcode; int /*<<< orphan*/  ctype; } ;

/* Variables and functions */
 int /*<<< orphan*/  AVC_CTYPE_CONTROL ; 
 int /*<<< orphan*/  AVC_OPCODE_READ_DESCRIPTOR ; 
 scalar_t__ AVC_RESPONSE_ACCEPTED ; 
 scalar_t__ AVC_RESPONSE_STABLE ; 
 int AVC_SUBUNIT_TYPE_TUNER ; 
 int DESCRIPTOR_TUNER_STATUS ; 
 int EINVAL ; 
 int SIZEOF_ANTENNA_INPUT_INFO ; 
 int avc_write (struct firedtv*) ; 
 int /*<<< orphan*/  clear_operands (struct avc_command_frame*,int,int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int avc_tuner_status(struct firedtv *fdtv, struct firedtv_tuner_status *stat)
{
	struct avc_command_frame *c = (void *)fdtv->avc_data;
	struct avc_response_frame *r = (void *)fdtv->avc_data;
	int length, ret;

	mutex_lock(&fdtv->avc_mutex);

	c->ctype   = AVC_CTYPE_CONTROL;
	c->subunit = AVC_SUBUNIT_TYPE_TUNER | fdtv->subunit;
	c->opcode  = AVC_OPCODE_READ_DESCRIPTOR;

	c->operand[0] = DESCRIPTOR_TUNER_STATUS;
	c->operand[1] = 0xff;	/* read_result_status */
	/*
	 * operand[2]: reserved
	 * operand[3]: SIZEOF_ANTENNA_INPUT_INFO >> 8
	 * operand[4]: SIZEOF_ANTENNA_INPUT_INFO & 0xff
	 */
	clear_operands(c, 2, 31);

	fdtv->avc_data_length = 12;
	ret = avc_write(fdtv);
	if (ret < 0)
		goto out;

	if (r->response != AVC_RESPONSE_STABLE &&
	    r->response != AVC_RESPONSE_ACCEPTED) {
		dev_err(fdtv->device, "cannot read tuner status\n");
		ret = -EINVAL;
		goto out;
	}

	length = r->operand[9];
	if (r->operand[1] != 0x10 || length != SIZEOF_ANTENNA_INPUT_INFO) {
		dev_err(fdtv->device, "got invalid tuner status\n");
		ret = -EINVAL;
		goto out;
	}

	stat->active_system		= r->operand[10];
	stat->searching			= r->operand[11] >> 7 & 1;
	stat->moving			= r->operand[11] >> 6 & 1;
	stat->no_rf			= r->operand[11] >> 5 & 1;
	stat->input			= r->operand[12] >> 7 & 1;
	stat->selected_antenna		= r->operand[12] & 0x7f;
	stat->ber			= r->operand[13] << 24 |
					  r->operand[14] << 16 |
					  r->operand[15] << 8 |
					  r->operand[16];
	stat->signal_strength		= r->operand[17];
	stat->raster_frequency		= r->operand[18] >> 6 & 2;
	stat->rf_frequency		= (r->operand[18] & 0x3f) << 16 |
					  r->operand[19] << 8 |
					  r->operand[20];
	stat->man_dep_info_length	= r->operand[21];
	stat->front_end_error		= r->operand[22] >> 4 & 1;
	stat->antenna_error		= r->operand[22] >> 3 & 1;
	stat->front_end_power_status	= r->operand[22] >> 1 & 1;
	stat->power_supply		= r->operand[22] & 1;
	stat->carrier_noise_ratio	= r->operand[23] << 8 |
					  r->operand[24];
	stat->power_supply_voltage	= r->operand[27];
	stat->antenna_voltage		= r->operand[28];
	stat->firewire_bus_voltage	= r->operand[29];
	stat->ca_mmi			= r->operand[30] & 1;
	stat->ca_pmt_reply		= r->operand[31] >> 7 & 1;
	stat->ca_date_time_request	= r->operand[31] >> 6 & 1;
	stat->ca_application_info	= r->operand[31] >> 5 & 1;
	stat->ca_module_present_status	= r->operand[31] >> 4 & 1;
	stat->ca_dvb_flag		= r->operand[31] >> 3 & 1;
	stat->ca_error_flag		= r->operand[31] >> 2 & 1;
	stat->ca_initialization_status	= r->operand[31] >> 1 & 1;
out:
	mutex_unlock(&fdtv->avc_mutex);

	return ret;
}